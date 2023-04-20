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
    if (process_red_value() >= 60 && process_red_value() <= 90 && process_green_value() >= 75 && process_green_value() <= 110 && process_blue_value() >= 50 && process_blue_value() <= 70) {
        return true;
    } else {
        return false;
    }
}

bool isBlack() {
    if (process_red_value() >= 80 && process_green_value() >= 110 && process_blue_value() >= 84 && process_blue_value() <= 105) {
        return true;
    } else {
        return false;
    }
}
