#include "Motori.h"

Motori::Motori(int d1, int d2, int d3, int d4)
{
    this->d1=d1;
    this->d2=d2;
    this->d3=d3;
    this->d4=d4;

    pinMode(d1, OUTPUT);
    pinMode(d2, OUTPUT);
    pinMode(d3, OUTPUT);
    pinMode(d4, OUTPUT);

}


void Motori::avanti()
{
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);
}
    
void Motori::indietro()
{
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);
}
    
void Motori::destra()
{
    digitalWrite(d1, LOW);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, LOW);

}
    
    
void Motori::sinistra()
{

    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, HIGH);

}
 
void Motori::fermo()
{
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
}
