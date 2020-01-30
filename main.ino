/*
    Billy Bass in Motion
    Author: Michael Czigler
    Version: 1.0
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *mouth_motor = AFMS.getMotor(1);
Adafruit_DCMotor *tail_motor = AFMS.getMotor(2);

int SoundInPin = A0;
int LedPin =12;

void setup() {
    Serial.begin(9600);
    AFMS.begin();

    mouth_motor->setSpeed(0);
    mouth_motor->run(FORWARD);  // turn on motor
    mouth_motor->run(RELEASE);  // release motor

    tail_motor->setSpeed(0);
    tail_motor->run(FORWARD);   // turn on motor
    tail_motor->run(RELEASE);   // release motor

    pinMode(SoundInPin, INPUT); // set audio pin mode
    pinMode(LedPin, OUTPUT);    // set led pin mode
}

void loop() {
    uint8_t i;
    int sensorValue = analogRead(SoundInPin)*1.3;
//    Serial.println(sensorValue);
    int LEDValue = map(sensorValue,0,512,0,255);
    sensorValue = map(sensorValue,0,512,0,180);

    int MoveDelayValue = map(sensorValue,0,255,0,sensorValue);

//    if (sensorValue > 10) {
//        delay(1);
//        mouth_motor->run(FORWARD);
//        for (i=140; i<255; i++) {
//            mouth_motor->setSpeed(i);
//        }
//        analogWrite(LedPin, sensorValue);
//        mouth_motor->run(RELEASE);
//        tail_motor->run(RELEASE);
//        delay(1);
//    }
    
    if (sensorValue > 13) {
        delay(1);
        tail_motor->setSpeed(200);
        delay(1);
        tail_motor->run(FORWARD);
        //delay(2000);
        delay(1);
    }

    if (sensorValue > 12) {
        delay(1);
        mouth_motor->run(FORWARD);
        delay(1);
        for (i=140; i<255; i++) {
            mouth_motor->setSpeed(i);
        }
        analogWrite(LedPin, sensorValue);
        mouth_motor->run(RELEASE);
        tail_motor->run(RELEASE);
        delay(1);
    }

    analogWrite(LedPin, 0);
}
