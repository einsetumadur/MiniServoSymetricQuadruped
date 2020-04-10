#include<Servo.h>
#include"leg.h"

int button1pin = 2;
int button2pin = 4;
int button3pin = 7;
int servo1pin = 3;
int servo2pin = 5;
int servo3pin = 6;

enum state {up,down};
int etat = up;

Servo hip,knee,hanche;

Leg myleg(hip,knee);

void setup(){
  Serial.begin(9600);
  pinMode(button1pin,INPUT); 
  pinMode(button2pin,INPUT); 
  pinMode(button3pin,INPUT); 
  hip.attach(servo1pin);
  knee.attach(servo2pin);
  hanche.attach(servo3pin);
  myleg.reset();
}

void loop() {
  if(digitalRead(button1pin)){
    Serial.println("button pressed");
    switch(etat){
      case down:
        Serial.println("etat : down");
        etat=up;
        myleg.setXY(80,80,8);
        break;
      case up:
        Serial.println("etat : up");
        etat=down;
        myleg.setXY(100,100,8);
        break;
    }
    if(digitalRead(button1pin)) delay(200);
  }
  //myleg.write();
}
