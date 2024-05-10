#include <DeltaKinematics.h>

DeltaKinematics DK(100,300,80,30);

const int arraySize = 3;
int coordinates[arraySize]={0,0,0};
float stepRatio = 1.4; // nurmber of steps required to turn 1 degree.
float angle1=0, angle2=0, angle3=0;
float currAngle1=0, currAngle2=0, currAngle3=0;
float maxAngle = 90;
int dirOne;
char mtr;
int dly=50;

// mtr 1
const int stepPin1 = 54;
const int dirPin1 = 55;
const int enablePin1 = 38;

//mtr 2
const int stepPin2 = 60;
const int dirPin2 = 61;
const int enablePin2 = 56;

// mtr 3
const int stepPin3 = 46;
const int dirPin3 = 48;
const int enablePin3 = 62;

#define LimitSwitch1 3
#define LimitSwitch2 14
#define LimitSwitch3 18

#define injectionPin 11

int stepCount = 0;

//////////////////////////////////////////////////////////////////// void setup ///////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  Serial.println("Intialising...");
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(injectionPin, OUTPUT);
  pinMode(LimitSwitch1,INPUT_PULLUP);
  pinMode(LimitSwitch2,INPUT_PULLUP);
  pinMode(LimitSwitch3,INPUT_PULLUP);

  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  pinMode(enablePin3, OUTPUT);
  digitalWrite(enablePin1, LOW);
  digitalWrite(enablePin2, LOW);
  digitalWrite(enablePin3, LOW);
  digitalWrite(injectionPin, LOW);  
}

//////////////////////////////////////////////////////////////////// void loop ///////////////////////////////////////////////////////////

void loop() {
  if (currAngle1 == angle1 || currAngle1 == angle2 || currAngle1 == angle3) {
    if(getInput()){
      goHome();
      getAngle();
    }
    delay(10);
  }else if(angle1==angle1 && angle2==angle2 && angle3==angle3){
//    checkAngleLimit(angle1, angle2, angle3);
    Serial.println("moving motor...");
    digitalWrite(enablePin1, LOW);
    digitalWrite(enablePin2, LOW);
    digitalWrite(enablePin3, LOW);
    moveMotor(angle1, angle2, angle3);
    digitalWrite(injectionPin, HIGH);
    delay(5000);
    digitalWrite(injectionPin, LOW);
    
    goHome();

    angle1=0;
    angle2=0;
    angle3=0;
       
  }else{
    angle1=currAngle1;
    angle2=currAngle2;
    angle3=currAngle3;
  }

}

//////////////////////////////////////////////////////////////////// get input ///////////////////////////////////////////////////////////

bool getInput() {
  if (Serial.available() >= 6 * sizeof(int)) {
    for (int i = 0; i < 3; ++i) {
      coordinates[i] = Serial.parseInt();
    }
    Serial.print("Received Numbers: ");
    for (int i = 0; i < arraySize; ++i) {
      Serial.print(coordinates[i]);
      Serial.print(" ");
    }
    Serial.println();
    Serial.flush();
    return 1;
  }else return 0;
}

//////////////////////////////////////////////////////////////////// get angle ///////////////////////////////////////////////////////////

float getAngle() {
  
  DK.inverse(coordinates[0],coordinates[1],coordinates[2]);

  Serial.println(String(DK.x)+","+String(DK.y)+","+String(DK.z));
  Serial.println(String(DK.a)+","+String(DK.b)+","+String(DK.c));
  Serial.println();
  angle1 = DK.a;
  angle2 = DK.b;
  angle3 = DK.c;
}

//////////////////////////////////////////////////////////////////// go home ///////////////////////////////////////////////////////////

void goHome() {
  digitalWrite(dirPin1, LOW);
  digitalWrite(dirPin2, LOW);
  digitalWrite(dirPin3, LOW);
  while (digitalRead(LimitSwitch1) == HIGH || digitalRead(LimitSwitch2) || HIGH && digitalRead(LimitSwitch3) == HIGH)
  {
    Serial.print("X: ");
    Serial.println(digitalRead(LimitSwitch1));
    Serial.print("Y: ");
    Serial.println(digitalRead(LimitSwitch2));
    Serial.print("Z: ");
    Serial.println(digitalRead(LimitSwitch3));
    if (digitalRead(LimitSwitch1) == HIGH) {      
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(dly);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(dly);
    }
    if (digitalRead(LimitSwitch2) == HIGH) {      
      digitalWrite(stepPin2, HIGH);
      delay(1);
      digitalWrite(stepPin2, LOW);
      delay(1);
    }
    if (digitalRead(LimitSwitch3) == HIGH) {      
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(dly);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(dly);
    }
  }
  
  delay(1000);
  
  digitalWrite(dirPin1, HIGH);
  digitalWrite(dirPin2, HIGH);
  digitalWrite(dirPin3, HIGH);
        
  for(int i=0;i<50;i++){

    //mtr 1
    if(i<80){
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(dly);  
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(dly);
    }
    //mtr 2
    if(i<72){
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(dly);  
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(dly);
    }
    //mtr 3
    if(i<200){
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(dly);  
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(dly);
    }
  }
  currAngle1 = 0;
  currAngle2 = 0;
  currAngle3 = 0;
  Serial.println("Delta ready!!!");
}

//////////////////////////////////////////////////////////////////// get steps  ///////////////////////////////////////////////////////////

float getSteps(char mtr, float angle) {
  int dirPin;
  float currAngle;
  if(mtr == 'A') {
    currAngle = currAngle1;
    dirPin = dirPin1;
  }
  if(mtr == 'B') {
    currAngle = currAngle2;
    dirPin = dirPin2;
  }
  if(mtr == 'C') {
    currAngle = currAngle3;
    dirPin = dirPin3;
  }
    
  angle = angle - currAngle;
  if (angle < 0){
    angle = angle * -1;
    digitalWrite(dirPin,LOW);    
  }else digitalWrite(dirPin,HIGH);
  
  int steps = angle * stepRatio;
  return steps*4;
}

//////////////////////////////////////////////////////////////////// move motor ///////////////////////////////////////////////////////////

void moveMotor(float angle1, float angle2, float angle3) {
  int currStep1 = 0;
  int currStep2 = 0;
  int currStep3 = 0;

  int step1 = getSteps('A', angle1);
  int step2 = getSteps('B', angle2);
  int step3 = getSteps('C', angle3);

  Serial.println("steps: ");

  Serial.println(step1);
  Serial.println(step2);
  Serial.println(step3);
  
  while (true) {
    if (currStep1 == step1 && currStep2 == step2 && currStep3 == step3) {
      currAngle1 = angle1;
      currAngle2 = angle2;
      currAngle3 = angle3;
      Serial.println("curr angles: ");
      Serial.println(currAngle1);
      Serial.println(currAngle2);
      Serial.println(currAngle3);
      break;
    }
    Serial.println("curr steps: ");
    Serial.println(currStep1);
    Serial.println(currStep2);
    Serial.println(currStep3);

    //mtr 1
    if(currStep1 < step1){
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(dly);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(dly);
      currStep1++;
    }
    //mtr 2
    if(currStep2 < step2){
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(dly);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(dly);
      currStep2++;
    }
    //mtr 3
    if(currStep3 < step3){
      digitalWrite(stepPin3, HIGH);
      delayMicroseconds(dly);
      digitalWrite(stepPin3, LOW);
      delayMicroseconds(dly);
      currStep3++;
    }
  }
}