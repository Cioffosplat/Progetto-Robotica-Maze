#include "Motori.h"

Motori::Motori(int d1, int d2, int motored_b, int d3, int d4, int motored_a, int s1, int s2, int motores_a,int motores_b,int s3,int s4,int defaultSpeed)
{
    this->d1=d1;
    this->d2=d2;
    this->motored_b=motored_b;
    this->d3=d3;
    this->d4=d4;
    this->motored_a=motored_a;
    this->s1=s1;
    this->s2=s2;
    this->motores_a=motores_a;
    this->motores_b=motores_b;
    this->s3=s3;
    this->s4=s4;
    this->defaultSpeed = defaultSpeed;

    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);
    pinMode(motored_a, OUTPUT);
    pinMode(motored_b, OUTPUT);

    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(s4, OUTPUT);
    pinMode(motores_a, OUTPUT);
    pinMode(motores_b, OUTPUT);

}

int Motori::chooseSpeed(int speed)
{
    return speed < 0 ? defaultSpeed : speed;
}

void Motori::avanti(int speed)
{
    int velocita = chooseSpeed(speed);

    analogWrite(motored_a, velocita);
    analogWrite(motored_b, velocita);
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);

    analogWrite(motores_a, velocita);
    analogWrite(motores_b, velocita);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    digitalWrite(s4, LOW);
}
    
void Motori::indietro(int speed)
{
    int velocita = chooseSpeed(speed);

    analogWrite(motored_a, velocita);
    analogWrite(motored_b, velocita);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);

    analogWrite(motores_a, velocita);
    analogWrite(motores_b, velocita);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    digitalWrite(s3, LOW);
    digitalWrite(s4, HIGH); 
}
    
void Motori::destra(int speed)
{
    int velocita = chooseSpeed(speed);

    analogWrite(motored_a, velocita);
    analogWrite(motored_b, velocita);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);

    analogWrite(motores_a, velocita);
    analogWrite(motores_b, velocita);
    digitalWrite(s1, HIGH);
    digitalWrite(s2, LOW);
    digitalWrite(s3, HIGH);
    digitalWrite(s4, LOW);
}
    
    
void Motori::sinistra(int speed)
{
    int velocita = chooseSpeed(speed);

    analogWrite(motored_a, velocita);
    analogWrite(motored_b, velocita);
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);

    analogWrite(motores_a, velocita);
    analogWrite(motores_b, velocita);
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    digitalWrite(s3, LOW);
    digitalWrite(s4, HIGH);
}
 
void Motori::fermo()
{
    analogWrite(motored_a, 0);
    analogWrite(motored_b, 0);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
    analogWrite(motores_a, 0);
    analogWrite(motores_b, 0);
    digitalWrite(s1, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    digitalWrite(s4, LOW);
}
