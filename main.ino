/*
    Billy Bass in Motion
    Author: Michael Czigler
    Version: 1.0
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *mouth_motor = AFMS.getMotor(3);
Adafruit_DCMotor *tail_motor = AFMS.getMotor(4);

int SoundInPin = A0;

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
}

void loop() {
    uint8_t i;
    int sensorValue = analogRead(SoundInPin);
    //sensorValue = map(sensorValue,0,512,0,180);
    sensorValue = map(sensorValue,500,800,0,180);
    //Serial.println(sensorValue); // serial monitor, comment out
    if (sensorValue > 14) {
        delay(1);
        tail_motor->setSpeed(200);
        delay(1);
        tail_motor->run(FORWARD);
        delay(100);
    }

    if (sensorValue > 17) {
        delay(1);
        mouth_motor->run(FORWARD);
        delay(1);
        for (i=140; i<245; i++) {
            mouth_motor->setSpeed(i);
        }
 
        mouth_motor->run(RELEASE);
    }
    if (sensorValue > 14) {
        tail_motor->run(RELEASE);
        delay(1);
    }
    
}
