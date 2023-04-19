//
// Created by Giulio on 13/04/2023.
//

#include "Finecorsa.h"

#define CORSA_FL PB8
#define CORSA_FR PB9
#define CORSA_BL PB4
#define CORSA_BR PA2

void setupCorsa(){
  pinMode(CORSA_FL, INPUT);
  pinMode(CORSA_FR, INPUT);
  pinMode(CORSA_BL, INPUT);
  pinMode(CORSA_BR, INPUT);
}

bool frontClick(){
  if(digitalRead(CORSA_FL) == HIGH && digitalRead(CORSA_FR) == HIGH){
    return true;
  }else{
    return false;
  }
}

bool backClick(){
  if(digitalRead(CORSA_BL) == HIGH && digitalRead(CORSA_BR) == HIGH){
    return true;
  }else{
    return false;
  }
}
