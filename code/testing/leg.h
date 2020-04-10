#include<Servo.h>

const float angleThreshold = 0.9;

float getPhy(float x, float y);
float getTeta(float x, float phy);

class Leg {
  public:
    Leg(Servo hip,Servo Knee);
    void setTarget(int hipTarget, int kneeTarget ,int velocity);
    void setXY(float x ,float y ,int velocity);
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
    bool repo;
    unsigned long int lastReachedFlag;
};

Leg::Leg(Servo hip, Servo knee){
  hipS = hip;
  kneeS = knee;
  hipAng = 120;
  kneeAng = 0;
  hipTar = hipAng;
  kneeTar = kneeAng;
  velo = 360;
  repo = true;
  hipS.write(hipAng);
  kneeS.write(kneeAng);
  lastupdate=millis();
  lastReachedFlag = 0;
}

void Leg::setTarget(int hipTarget, int kneeTarget ,int velocity){
  hipTar = hipTarget;
  kneeTar = kneeTarget;
  velo = velocity;
  repo = false;
  lastReachedFlag = millis();
}

void Leg::setXY(float x ,float y ,int velocity){
  float phy = getPhy(x,y);
  float teta = getTeta(x,phy);
  setTarget(phy,teta,velocity);
}

void Leg::write(){
  update();
  hipS.write(hipAng);
  kneeS.write(kneeAng);
  if(not reached()){
    Serial.print("hip : ");
    Serial.print(hipAng);
    Serial.print(" -> ");
    Serial.print(hipTar);
    Serial.print(" knee : ");
    Serial.print(kneeAng);
    Serial.print(" -> ");
    Serial.println(kneeTar);
  }
  else if(not repo) {
    Serial.print("reached target position in ");
    Serial.print((millis()-lastReachedFlag)/1000);
    Serial.println(" sec !");
    repo = true;
  }
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
  hipS.write(75);
  Serial.println("Leg has been reset !");
  delay(1000);
  lastReachedFlag = millis();
};

float getTeta(float x, float phy){
  float teta = 2*asin(-x/2*65*cos(phy));
  if(isnan(teta)) teta = 0;   // test if teta is not a number (nan error)
  if(teta<0)  teta = 0;
  if(teta>180)teta = 180;
  Serial.print("knee_angle : ");
  Serial.println(teta);
  return asin(teta);
}

float getPhy(float x, float y){
  float phy = atan(y/x);
  if(phy<0)  phy = 0;
  if(phy>180)phy = 180;
  Serial.print("hip_angle : ");
  Serial.println(phy);
  return phy;
}
