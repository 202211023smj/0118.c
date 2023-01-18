#include <NewPing.h>
#define L_InPin_1  2  //왼쪽모터 핀1
#define L_InPin_2  3  //왼쪽모터 핀2
#define R_InPin_1  7  //오른쪽모터 핀1
#define R_InPin_2  4  //오른쪽모터 핀2
#define L_en  5 //왼쪽모터 속도 제어 핀
#define R_en  6 //오른쪽모터 속도 제어 핀
#define F_Sonar  8  //정면부 초음파 센서 연결 핀
#define R_Sonar  10 //오른쪽 초음파 센서 연결 핀
#define L_Sonar  11 //왼쪽 초음파 센서 연결 핀

double F_distance = 0;
double L_distance = 0;
double R_distance = 0;

int line_sensor[5] = {0,0,0,0,0};
int sensor =1;
int sum = 1;

int read_line_sensor()
{
  int i;
  sum = 0;
  for(i = 0; i < 5; i++)
  {
    line_sensor[i] = analogRead(A0 + i);
   if(i==0) if(  line_sensor[i] > 500) sum = sum - 5;       
   if(i==1) if(  line_sensor[i] > 500) sum = sum - 2;
   if(i==2) if(  line_sensor[i] > 500) sum = sum ;
   if(i==3) if(  line_sensor[i] > 500) sum = sum + 2; 
   if(i==4) if(  line_sensor[i] > 500) sum = sum + 5;
  }
  Serial.println(" ");
  return sum;           
}

void motor_mob(int speed_l,int dir_l, int speed_r, int dir_r)   // motor_control을 나만의 이름으로 motor_power로 바꿔줌
{
  if(dir_l ==1) // 전진
   {
     digitalWrite(MOB_L_InPin1, HIGH);
     digitalWrite(MOB_L_InPin2, LOW);
     analogWrite(MOB_L_en, speed_l);  
   }
   else if( dir_l == -1)//후진
   {  
     digitalWrite(MOB_L_InPin1, LOW);
     digitalWrite(MOB_L_InPin2, HIGH);
     analogWrite(MOB_L_en, speed_l); 
   }
   else
   {
     digitalWrite(MOB_L_InPin1, LOW);
     digitalWrite(MOB_L_InPin2, LOW);
     analogWrite(MOB_L_en, 0);
   } 
   if(dir_r ==1) // 전진
   {
     digitalWrite(MOB_R_InPin1, HIGH);
     digitalWrite(MOB_R_InPin2, LOW);
     analogWrite(MOB_R_en, speed_r);  
   }
   else if( dir_r == -1)//후진
   {  
     digitalWrite(MOB_R_InPin1, LOW);
     digitalWrite(MOB_R_InPin2, HIGH);
     analogWrite(MOB_R_en, speed_r); 
   }
   else
   {
     digitalWrite(MOB_R_InPin1, LOW);
     digitalWrite(MOB_R_InPin2, LOW);
     analogWrite(MOB_R_en, 0);
   }  
}
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); //9600 속도로 통신을 시작 한다.
  pinMode(MOB_R_InPin1, OUTPUT);
  pinMode(MOB_R_InPin2,OUTPUT);
  pinMode(MOB_R_en, OUTPUT);

  pinMode(MOB_L_InPin1, OUTPUT);
  pinMode(MOB_L_InPin2, OUTPUT);
  pinMode(MOB_L_en, OUTPUT);  
}

void loop() {
  // put your main code here, to run repeatedly:
  line_sensor[5];
  read_line_sensor(); // (int speed_l,int dir_l, int speed_r, int dir_r) ==> 순서
  sensor = read_line_sensor();
  if(sensor < 0){
    motor_mob(-sum * 100,-1,0,0); //1을 넣었지만 후진을 해서 -로 바꿔줌
  }
  else if(sensor > 0){
    motor_mob(0,0,sum * 200,-1);
  }
  else{
     motor_mob(100,-1,100,-1);
  }
}