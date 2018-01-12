#include <Arduino.h>
#include <TimerOne.h>

#define MosEnable (2)
#define BatADC    (A0)

#define t_ON_ms   1000
#define t_OFF_ms  5000

void setup() {
    // put your setup code here, to run once:

    pinMode(MosEnable, OUTPUT);
    pinMode(BatADC, INPUT);



}

void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(MosEnable, HIGH);
    delay(200);
    digitalWrite(MosEnable, LOW);
    delay(200);
}
