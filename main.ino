// the unstoppable billy bass!
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

int SoundInPin = A0;
int LedPin =12;

void setup() {
    Serial.bein(9600);
    AFMS.begin();
    myMotor->setSpeed(0);
    myMotor->run(FORWARD); // mouth motor
    myMotor->run(RELEASE); // turn on motor
    pinMode(SoundInPin, INPUT);
    pinMode(LedPin, OUTPUT);
    myOtherMotor->setSpeed(0);
    myOtherMotor->run(FORWARD); //tail motor
    myOtherMotor->run(RELEASE);
    pinMode(SoundInPin, INPUT);
}

void loop() {
    uint8_t i;
    int sensorValue = analogRead(SoundInPin);
    int LEDValue = map(sensorValue,0,512,0,255);
    sensorValue = map(sensorValue,0,512,0,180);
    int MoveDelayValue = map(sensorValue,0,255,0,sensorValue);

    if (sensorValue >10) {
        delay(1);
        myMotor->run(FORWARD);
        for (i=140; i<255, i++) {
            myMotor->setSpeed(i);
        }
        analogWrite(LedPin, sensorValue);
        myMotor->run(RELEASE);
        myOtherMotor->run(RELEASE)
        delay(1);
    }
    analogWrite(LedPin, 0);
}
