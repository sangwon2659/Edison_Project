#include <Servo.h>
#include <Stepper.h>

//초음파센서
int trigPin= ;
int echoPin= ;

//LED 센서

//적외선 센서
int LW= ;
int LL= ;
int RL= ;
int RW= ;

//DC모터
int DCspeed=100;
int N1= ;//왼쪽
int N2= ;
int ENA= ;
int N3= ;//오른쪽
int N4= ;
int ENB= ;

//서보모터
int servospeed= ;
Servo liftservo;

//스텝모터
const int stepsPerRevolution = 200; // 모터의 1회전당 스텝 수에 맞게 조정 1024=90도

// initialize the stepper library on pins 8 through 11:
// IN1, IN2, IN3, IN4 가 아두이노 D8, D9, D10, D11에 순서대로 연결되어 있다면
Stepper grabStepper(stepsPerRevolution, 11,9,10,8); // Note 8 & 11 swapped
Stepper bodyStepper(stepsPerRevolution, 11,9,10,8); // Note 8 & 11 swapped

void setup() {
 Serial.begin(9600);
 //초음파 센서
 pinMode(trigPin,OUTPUT);
 pinMode(echoPin,INPUT);
 //DC모터 모터드라이브
 pinMode(IN1,OUTPUT);
 pinMode(IN2,OUTPUT);
 pinMode(IN3,OUTPUT);
 pinMode(IN4,OUTPUT);
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);  
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
 //servo
 liftservo.attach();
 //팔스텝모터
 // set the speed at 60 rpm:
 myStepper.setSpeed(60);
}

void loop() {
  long duration, distance;
  //초음파 거리측정
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin, HIGH);
  distance=duration/29/2;
  //distance(cm)
  //알고리즘 시작
  if(distance>5){
    linetracing();    
  }
}

//DC모터 함수
void linetracing(){
  //전진
  if(!digitalRead(LL) && !digitalRead(RL)){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENA,speed);
    analogWrite(ENB,speed);
  }
  //좌보정
  else if(digitalRead(LL) && !digitalRead(RL)){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENB,speed-20);
  }
  //우보정
  else if(!digitalRead(LL) && digitalRead(RL)){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    analogWrite(ENA,speed-20);
  }
}

void stopping(){
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,LOW);  
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,LOW);
}

void uturn(){
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);  
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 analogWrite(ENA,speed);
 analogWrite(ENB,speed);
 delay();
 }

void turnleft(){ 
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);  
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 analogWrite(ENA,speed);
 analogWrite(ENB,speed);
 delay();
}

//서보모터구동
void lifting(){
  // Run Motor
  mspeed = 1300; //set position variable
  amotor.writeMicroseconds(mspeed); // tell servo to move as indicated by variable 'mspeed'
  delay(5000); //time for the servo to move
  //Stop Motor
  mspeed = 1500; //set position variable
  amotor.writeMicroseconds(mspeed); // tell servo to move as indicated by variable 'mspeed'
  delay(2500); //time for the servo to move
}

void goback(){
  // Run Motor
  mspeed =3000; //set position variable
  amotor.writeMicroseconds(mspeed); // tell servo to move as indicated by variable 'mspeed'
  delay(5000); //time for the servo to move
  //Stop Motor
  mspeed = 1500; //set position variable
  amotor.writeMicroseconds(mspeed); // tell servo to move as indicated by variable 'mspeed'
  delay(2500); //time for the servo to move
}

//스텝모터 구동
void Grabbing(){
  for(int x=1;x<12;x++){
    grabStepper.step(stepsPerRevolution);
  }
}

void releasing(){
  for(int x=1;x<12;x++){
    grabStepper.step(-stepsPerRevolution);
  }
}

void bodyTL(){

}

void bodyTR(){

}
