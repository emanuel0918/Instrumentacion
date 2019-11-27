#include<stdlib.h> //Double to String Float
//
int cont_m;
//int s1=3;
//int s2=4;
int motor1=5;
//int motor2=6;
int valor_pwm;
int pwm1;
String s_pwm;
int valor_velocidad;
float paros;
int paros2;
int cuenta_segundos;
String pwm_string;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //
  pinMode(A0,INPUT);
  pinMode(motor1,OUTPUT);
  //
  cont_m=0;
  valor_velocidad=20;
  pwm_string="0";
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(1);
  //
  valor_pwm=analogRead(A0);
  //valor_v1=(((float)valor_velocidad)*1.1);
  //valor_v2=((int)valor_v1)+1;
  //valor_v2=255;
  pwm1=map(valor_pwm,0,1023,0,valor_velocidad);
  paros= (((float)(valor_velocidad))/((float)(pwm1)));
  paros2=(int)paros;
  pwm_string=String(pwm1);
  if(cont_m>=valor_velocidad){
    cont_m=0;
  }else{
    if(cont_m%paros2==0){
      digitalWrite(motor1,HIGH);
    }else{
      digitalWrite(motor1,LOW);
    }
    cont_m++;
  }
  Serial.println(pwm_string);
}
