#include <Arduino.h>
#include <TimerOne.h>
#include <math.h>

#define MosEnable (2)
#define BatADC    (A0)

#define t_ON_ms   1000
#define t_OFF_ms  5000
#define UVLO_voltage  2.8

volatile const uint32_t t_ON_us = t_ON_ms * (uint32_t)1000;
volatile const uint32_t t_OFF_us = t_OFF_ms * (uint32_t)1000;

//volatile bool Mos_State = false;
void switch_Mos_On(void);
void switch_Mos_Off(void);
float read_voltage(uint8_t);
void observe_idle(uint8_t);

void setup() {
    // put your setup code here, to run once:

    pinMode(MosEnable, OUTPUT);
    pinMode(BatADC, INPUT);

    Serial.begin(115200);

    // turn MOSFET on and start timer
    switch_Mos_On();

}

void loop() {
    // put your main code here, to run repeatedly:
    float cel_voltage = read_voltage(BatADC);
    Serial.print("1,");
    Serial.print(String(micros(), DEC) + ",");

    if (cel_voltage < 0.1) // no cel installed
    {
      Timer1.stop();
      digitalWrite(MosEnable, LOW);
      Serial.println("-1");
      observe_idle(BatADC);
    } else if (cel_voltage < UVLO_voltage) // under voltage lock-out reached
    {
      Timer1.stop();
      digitalWrite(MosEnable, LOW);
      Serial.println("-2");
      Serial.println("Under voltage lock-out reached");
      observe_idle(BatADC);
    } else
    {
      Serial.println(cel_voltage, 2);
    }
    //cel_voltage = round(cel_voltage * 100)/100.0;



}

// read voltage from a pin, 5V reference, 10 bit ADC resolution
float read_voltage(uint8_t pin)
{
  return analogRead(pin) * 5.0 / 1024;
}

// observe a pin and wait until a new battery is placed
void observe_idle(uint8_t pin)
{
  // wait until cel is replaced
  while (read_voltage(pin) < 4.1);
  // restart timer
  switch_Mos_On();
}

// turn on MOSFET and start timer with ON time delay
void switch_Mos_On()
{
  digitalWrite(MosEnable, HIGH);
  Timer1.initialize(t_ON_us);
  Timer1.attachInterrupt(switch_Mos_Off);
}

// turn off MOSFET and start timer with OFF time delay
void switch_Mos_Off()
{
  digitalWrite(MosEnable, LOW);
  Timer1.initialize(t_OFF_us);
  Timer1.attachInterrupt(switch_Mos_On);
}
