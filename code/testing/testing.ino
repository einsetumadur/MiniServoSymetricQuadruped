#include<Servo.h>
#include"potard.h"
#include"leg.h"

int button1pin = 2;
int button2pin = 4;
int button3pin = 7;
int servo1pin = 3;
int servo2pin = 5;
int servo3pin = 6;

Potard pot1 (A1);
Potard pot2 (A0);

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
}

void loop(){
  myleg.setTarget(pot1.getAngle(),pot2.getAngle(),5);
  myleg.write();
}
