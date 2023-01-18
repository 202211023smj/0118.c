#include <NewPing.h>
#define L_InPin_1  2  //���ʸ��� ��1
#define L_InPin_2  3  //���ʸ��� ��2
#define R_InPin_1  7  //�����ʸ��� ��1
#define R_InPin_2  4  //�����ʸ��� ��2
#define L_en  5 //���ʸ��� �ӵ� ���� ��
#define R_en  6 //�����ʸ��� �ӵ� ���� ��
#define F_Sonar  8  //����� ������ ���� ���� ��
#define R_Sonar  10 //������ ������ ���� ���� ��
#define L_Sonar  11 //���� ������ ���� ���� ��

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

void motor_mob(int speed_l,int dir_l, int speed_r, int dir_r)   // motor_control�� ������ �̸����� motor_power�� �ٲ���
{
  if(dir_l ==1) // ����
   {
     digitalWrite(MOB_L_InPin1, HIGH);
     digitalWrite(MOB_L_InPin2, LOW);
     analogWrite(MOB_L_en, speed_l);  
   }
   else if( dir_l == -1)//����
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
   if(dir_r ==1) // ����
   {
     digitalWrite(MOB_R_InPin1, HIGH);
     digitalWrite(MOB_R_InPin2, LOW);
     analogWrite(MOB_R_en, speed_r);  
   }
   else if( dir_r == -1)//����
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
   Serial.begin(9600); //9600 �ӵ��� ����� ���� �Ѵ�.
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
  read_line_sensor(); // (int speed_l,int dir_l, int speed_r, int dir_r) ==> ����
  sensor = read_line_sensor();
  if(sensor < 0){
    motor_mob(-sum * 100,-1,0,0); //1�� �־����� ������ �ؼ� -�� �ٲ���
  }
  else if(sensor > 0){
    motor_mob(0,0,sum * 200,-1);
  }
  else{
     motor_mob(100,-1,100,-1);
  }
}