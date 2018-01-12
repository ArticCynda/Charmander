#include <Arduino.h>

#define MosEnable (2)
#define BatADC    (A0)

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
