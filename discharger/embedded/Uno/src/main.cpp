#include <Arduino.h>
#include <TimerOne.h>
#include <math.h>

#define MosEnable (2)
#define BatADC    (A0)

#define t_ON_ms   1000
#define t_OFF_ms  5000

volatile const uint32_t t_ON_us = t_ON_ms * (uint32_t)1000;
volatile const uint32_t t_OFF_us = t_OFF_ms * (uint32_t)1000;

//volatile bool Mos_State = false;
void switch_Mos_On(void);
void switch_Mos_Off(void);

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
    float cel_voltage = analogRead(BatADC) * 5.0 / 1024;

    if (cel_voltage < 2.8)
    {
      Timer1.stop();
      digitalWrite(MosEnable, LOW);
      Serial.println("Under voltage lockout reached. Test stopped.");
      while (1);
    }
    //cel_voltage = round(cel_voltage * 100)/100.0;
    Serial.print(String(micros(), DEC) + ",");
    Serial.println(cel_voltage, 2);

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
