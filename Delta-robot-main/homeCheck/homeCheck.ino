const int stepPin1 = 54;
const int dirPin1 = 55;
const int enablePin1 = 38;

const int stepPin2 = 60;
const int dirPin2 = 61;
const int enablePin2 = 56;

const int stepPin3 = 46;
const int dirPin3 = 48;
const int enablePin3 = 62;

#define LimitSwitch1 3 
#define LimitSwitch2 14 
#define LimitSwitch3 18 


void setup() {
  Serial.begin(9600); 
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(LimitSwitch1,INPUT_PULLUP);
  pinMode(LimitSwitch2,INPUT_PULLUP);
  pinMode(LimitSwitch3,INPUT_PULLUP);


  pinMode(enablePin1, OUTPUT);
  digitalWrite(enablePin1, LOW);
  pinMode(enablePin2, OUTPUT);
  digitalWrite(enablePin2, LOW);
  pinMode(enablePin3, OUTPUT);  
  digitalWrite(enablePin3, LOW);


            digitalWrite(dirPin1, LOW);
        digitalWrite(dirPin2, LOW);
        digitalWrite(dirPin3, LOW);
 goHome();
      delay(5000);
            digitalWrite(dirPin1, HIGH);
        digitalWrite(dirPin2, HIGH);
        digitalWrite(dirPin3, HIGH);
        
  for(int i=0;i<50;i++){

    //mtr 1
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(1000);  
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(1000);
    //mtr 2
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(1000);  
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(1000);
    //mtr 3
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(1000);  
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(1000);
  }

      digitalWrite(enablePin1, HIGH);
      digitalWrite(enablePin2, HIGH);
      digitalWrite(enablePin3, HIGH);
  
}

void loop(){
  Serial.println(digitalRead(LimitSwitch1));
    Serial.println(digitalRead(LimitSwitch2));
  Serial.println(digitalRead(LimitSwitch3));

}
int dly=1000;
void goHome(){
  while(digitalRead(LimitSwitch1) == HIGH || digitalRead(LimitSwitch2) == HIGH || digitalRead(LimitSwitch3) == HIGH)
  {
    if(digitalRead(LimitSwitch1) == HIGH){ 
        digitalWrite(stepPin1, HIGH);
    delayMicroseconds(dly);
        digitalWrite(stepPin1, LOW);
    delayMicroseconds(dly);

         }
    if(digitalRead(LimitSwitch2) == HIGH){ 
        digitalWrite(stepPin2, HIGH);
    delayMicroseconds(dly);
        digitalWrite(stepPin2, LOW);
             delayMicroseconds(dly);

}
     if(digitalRead(LimitSwitch3) == HIGH){
        digitalWrite(stepPin3, HIGH);
    delayMicroseconds(dly);
        digitalWrite(stepPin3, LOW);
         delayMicroseconds(dly);

    }
         
    }
    

}
