#include<Servo.h>

const float angleThreshold = 0.9;

class Leg {
  public:
    Leg(Servo hip,Servo Knee);
    void setTarget(int hipTarget, int kneeTarget ,int velocity);
    void write();
    bool reached();
    void reset();
  private :
    void update();
    Servo hipS;
    Servo kneeS;
    float hipAng,hipTar;
    float kneeAng,kneeTar;
    int velo;
    unsigned long int lastupdate;
};

Leg::Leg(Servo hip, Servo knee){
  hipS = hip;
  kneeS = knee;
  hipAng = 120;
  kneeAng = 0;
  hipTar = hipAng;
  kneeTar = kneeAng;
  velo = 360;
  hipS.write(hipAng);
  kneeS.write(kneeAng);
  lastupdate=millis();
}

void Leg::setTarget(int hipTarget, int kneeTarget ,int velocity){
  hipTar = hipTarget;
  kneeTar = kneeTarget;
  velo = velocity;
}

void Leg::write(){
  update();
  hipS.write(hipAng);
  kneeS.write(kneeAng);
  Serial.print("hip : ");
  Serial.print(hipAng);
  Serial.print(" -> ");
  Serial.print(hipTar);
  Serial.print("knee : ");
  Serial.print(kneeAng);
  Serial.print(" -> ");
  Serial.println(kneeTar);
}

void Leg::update(){
  if((millis()-lastupdate)>10 && not reached()){
    float hipdiff = hipTar - hipAng;
    float kneediff = kneeTar - kneeAng;
    //if(abs(hipTar-hipAng)<1) 
    hipAng += (hipdiff/velo);
    //if(abs(kneeTar-kneeAng)<1) 
    kneeAng += (kneediff/velo);
    lastupdate = millis();
  }
}

bool Leg::reached(){
  bool ret;
  if(abs(hipTar-hipAng)<1 && abs(kneeTar-kneeAng)<1) ret = true ;
  else ret = false;
  return ret;
}

void Leg::reset(){
  kneeS.write(90);
  hipS.write(90);
  Serial.println("Leg has been reset !");
  delay(1000);
};
