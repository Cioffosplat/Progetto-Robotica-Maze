#include "Motori.h"

// ALL of the commentated methods inside of the class are used to connect
// the enable pins and regulate the motor's speed and rpm

Motori::Motori(int d1, int d2, int d3, int d4, /*int motored_a,int motored_b, int defaultSpeed*/)
{
    this->d1=d1;
    this->d2=d2;
    //this->motored_b=motored_b;
    this->d3=d3;
    this->d4=d4;
    //this->motored_a=motored_a;
    //this->defaultSpeed = defaultSpeed;

    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);
    //pinMode(motored_a, OUTPUT);
    //pinMode(motored_b, OUTPUT);

}

/*int Motori::chooseSpeed(int speed)
{
    return speed < 0 ? defaultSpeed : speed;
}*/

void Motori::avanti(/*int speed*/)
{
    //int velocita = chooseSpeed(speed);

    //analogWrite(motored_a, velocita);
    //analogWrite(motored_b, velocita);
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);

}
    
void Motori::indietro(/*int speed*/)
{
    //int velocita = chooseSpeed(speed);

    //analogWrite(motored_a, velocita);
    //analogWrite(motored_b, velocita);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);

}
    
void Motori::destra(/*int speed*/)
{
    //int velocita = chooseSpeed(speed);

    //analogWrite(motored_a, velocita);
    //analogWrite(motored_b, velocita);
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);

}
    
    
void Motori::sinistra(/*int speed*/)
{
    int velocita = chooseSpeed(speed);

    //analogWrite(motored_a, velocita);
    //analogWrite(motored_b, velocita);
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);

}
 
void Motori::fermo()
{
    //analogWrite(motored_a, 0);
    //analogWrite(motored_b, 0);
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
}
