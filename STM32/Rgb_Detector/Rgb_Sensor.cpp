@Author Filippo Schierato AKA Papaya

#include "Rgb_Sensor.h"

#define S0_PIN 8
#define S1_PIN 7
#define S2_PIN 6
#define S3_PIN 5
#define OUT_PIN 4

int Rgb_Sensor::process_red_value() {
    digitalWrite(S2_PIN, LOW);
    digitalWrite(S3_PIN, LOW);
    int pulse_length = pulseIn(OUT_PIN, LOW);
    return pulse_length;
}

int Rgb_Sensor::process_blue_value() {
    digitalWrite(S2_PIN, LOW);
    digitalWrite(S3_PIN, HIGH);
    int pulse_length = pulseIn(OUT_PIN, LOW);
    return pulse_length;
}

int Rgb_Sensor::process_green_value() {
    digitalWrite(S2_PIN, HIGH);
    digitalWrite(S3_PIN, HIGH);
    int pulse_length = pulseIn(OUT_PIN, LOW);
    return pulse_length;
}

//Code to include in the final project, definition
//of the pins of the sensor itself
/*void setup(){
    pinMode(S0_PIN, OUTPUT);
    pinMode(S1_PIN, OUTPUT);
    pinMode(S2_PIN, OUTPUT);
    pinMode(S3_PIN, OUTPUT);
    pinMode(OUT_PIN, INPUT);
    // Set Pulse Width scaling to 20%
    digitalWrite(S0_PIN, HIGH);
    digitalWrite(S1_PIN, LOW);
    // Enable Serial Port for Debugging
    Serial.begin(38400);
}*/
int Rgb_Sensor::r = process_red_value();
int Rgb_Sensor::g = process_green_value();
int Rgb_Sensor::b = process_blue_value();

bool Rgb_Sensor::isBlue() {
    if (r >= 0 || r <= 25 && g >= 0 || g <= 25 && b >= 230 || b <= 255) {
        return true;
        Serial.print("It's Blue");
    } else {
        return false;
        Serial.print("It's not Blue");
    }
}

bool Rgb_Sensor::isBlack() {
    if (r >= 0 || r <= 25 && g >= 0 || g <= 25 && b >= 0 || b <= 25) {
        return true;
        Serial.print("It's Blue");
    } else {
        return false;
        Serial.print("It's not Blue");
    }
}

