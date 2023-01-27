#include "LaserSensor.h"

LaserSensor::LaserSensor(int pin, int lox_address, Adafruit_VL53L0X *lox)
{
    this->pin = pin;
    this->lox_address = lox_address;
    this->lox = lox;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);

    init();
}

LaserSensor::~LaserSensor()
{
    delete lox;
}

int LaserSensor::getValue()
{
    return lox->readRange();
}

bool LaserSensor::isFree(int maxValue)
{
    return getValue() > maxValue;
}
/*bool LaserSensor::isFreeDavanti(int maxValue)
{
    return getValue() > maxValue +50;
}*/
void LaserSensor::init()
{
    laserLow();
    laserHigh();

    if (!lox->begin(lox_address))
    {
        Serial.print(F("Failed to boot "));
        Serial.print(pin);
        Serial.println(F(" VL53L0X"));
        while (1)
            ;
    }

    delay(10);
}

void LaserSensor::laserLow()
{
    digitalWrite(pin, LOW);
}

void LaserSensor::laserHigh()
{
    digitalWrite(pin, HIGH);
} 
