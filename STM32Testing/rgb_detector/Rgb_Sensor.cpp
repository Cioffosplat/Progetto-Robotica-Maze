#include "Rgb_Sensor.h"
#include <Arduino.h>
#include <Wire.h>

#define S0_PIN PA0
#define S1_PIN PA5
#define S2_PIN PA7
#define S3_PIN PB0
#define OUT_PIN PA6



void setupRGB(){
    pinMode(S0_PIN, OUTPUT);
    pinMode(S1_PIN, OUTPUT);
    pinMode(S2_PIN, OUTPUT);
    pinMode(S3_PIN, OUTPUT);
    pinMode(OUT_PIN, INPUT);
    // Set Pulse Width scaling to 20%
    digitalWrite(S0_PIN, HIGH);
    digitalWrite(S1_PIN, LOW);
    // Enable Serial Port for Debugging
    Serial.begin(9600);
}

int process_red_value() {
    digitalWrite(S2_PIN, LOW);
    digitalWrite(S3_PIN, LOW);
    int pulse_length = pulseIn(OUT_PIN, LOW);
    return pulse_length;
}

int process_blue_value() {
    digitalWrite(S2_PIN, LOW);
    digitalWrite(S3_PIN, HIGH);
    int pulse_length = pulseIn(OUT_PIN, LOW);
    return pulse_length;
}

int process_green_value() {
    digitalWrite(S2_PIN, HIGH);
    digitalWrite(S3_PIN, HIGH);
    int pulse_length = pulseIn(OUT_PIN, LOW);
    return pulse_length;
}


bool isBlue() {
    if (process_red_value() >= 185 && process_red_value() <= 210 && process_green_value() >= 140 && process_green_value() <= 170 && process_blue_value() >= 55 && process_blue_value() <= 80) {
        return true;
        Serial.print("It's Blue");
    } else {
        return false;
        Serial.print("It's not Blue");
    }
}

bool isBlack() {
    if (process_red_value() >= 210 && process_green_value() >= 210 && process_blue_value() >= 125 && process_blue_value() <= 150) {
        return true;
        Serial.print("It's Blue");
    } else {
        return false;
        Serial.print("It's not Blue");
    }
}
