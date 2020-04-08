#include<Servo.h>
#include"leg.h"

Servo hip;
Servo knee;

enum state {left,down,right,up};

const int kneepin = 3;
const int hippin = 6;
const int buttonpin = 2;
bool pressed=0;
state etat = up;
Leg myleg(hip,knee);


void setup() {
  Serial.begin(9600);
  knee.attach(kneepin);
  hip.attach(hippin);
  pinMode(buttonpin,INPUT);
  myleg.reset();
}

void loop() {
  pressed= digitalRead(buttonpin);
  if(pressed){
    Serial.println("button pressed");
    switch(etat){
      case left:
        Serial.println("etat : left");
        etat=down;
        myleg.setTarget(45,0,5);
        break;
      case down:
        Serial.println("etat : down");
        etat=right;
        myleg.setTarget(5,90,5);
        break;
      case right:
        Serial.println("etat : right");
        etat=up;
        myleg.setTarget(180,0,5);
        break;
      case up:
        Serial.println("etat : up");
        etat=left;
        myleg.setTarget(20,160,5);
        break;
    }
    if(pressed) delay(200);
  }
  myleg.write();
}
