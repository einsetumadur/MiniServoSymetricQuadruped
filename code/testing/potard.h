class Potard{ 
  public:
    Potard(int pin);
    float getAngle();
  private:
    int ppin;
    int value;
    float angle; 
};

Potard::Potard(int pin){
  pinMode(pin,INPUT);
  ppin = pin;
  value = analogRead(ppin);
  angle = map(value,0,1020,0,180);
}

float Potard::getAngle(){
  value = analogRead(ppin);
  angle = map(value,0,1020,0,180);
  return angle;
}
