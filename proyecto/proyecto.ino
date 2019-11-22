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
//
int pin_ir1=10;
int pin_ir2=11;
float cte;
int ir1;
int ir2;
int fl_i1;
int fl_i2;
int giros;
int medida_length;
float medida1;
char medida2[6];
String sg;
String sm;
String medida_string;
//
int flag_analog;
//Termometro
int t;
String termo2;
char analog_buffer[4];
//luxometro
int lux;
String lux2;
//
unsigned int analog_length;
//FPG
int pin_ppm=8;
int var_ppm;
int flag_ppm;
long ppm1;
int rebote_ppm;
int overflow_ppm;
float ppm2;
String string_ppm;
char ppm[6];
unsigned int ppm_length;
//
int cuenta_segundos;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //
  pinMode(pin_ppm,INPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(pin_ir1,INPUT);
  pinMode(pin_ir2,INPUT);
  pinMode(motor1,OUTPUT);
  //pinMode(motor2,OUTPUT);
  //pinMode(s1,OUTPUT);
  //pinMode(s2,OUTPUT);
  //
  cont_m=0;
  valor_velocidad=20;
  //digitalWrite(s1,HIGH);
  //
  fl_i1=0;
  fl_i2=0;
  giros=0;
  sg=String(giros);
  medida1=0;
  medida_length=6;
  medida_string="";
  cte=3.5; //3.5 cm
  //
  flag_ppm=0;
  ppm1=ppm2=0;
  rebote_ppm=0;
  overflow_ppm=30000;
  cuenta_segundos=0;
  ppm_length=6;
  string_ppm="000.00";
  //flag_analog
  flag_analog=0;
  //
  termo2="0000";
  //
  lux2="0000";
  //
  analog_length=4;
  
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
  //digitalWrite(motor1,pwm1);
  s_pwm=String(pwm1);
  //
  ir1=digitalRead(pin_ir1);
  ir2=digitalRead(pin_ir2);
  if(ir2==HIGH){
    if(fl_i2!=1){
      fl_i2=1;
      fl_i1=2;
      sm=String(1);
    }
  }else{
    if(fl_i2==1){
      medida1=(((float)giros)*cte);
      giros=0;
      dtostrf(medida1,medida_length-3,2,medida2);
      medida_string=medida2;
      sg=String(giros);
      fl_i1=0;
      fl_i2=0;
      sm=String(0);
    }
  }
  if(ir1==HIGH){
    if(fl_i1==2){
      fl_i1=1;
    }
  }else{
    if(fl_i1==1){
      giros++;
      sg=String(giros);
      fl_i1=2;
    }
  }
  //
  if(flag_analog==0){
    flag_analog=1;
    t=analogRead(A1);
    termo2=String(t);
    if(t<0){
      termo2="-001";
    }else if(t>=0 && t<=9){
      termo2="000"+termo2;
    }else if(t>=10 && t<=99){
      termo2="00"+termo2;
    }else if(t>=100 && t<=999){
      termo2="0"+termo2;
    }else if(t>=1000 && t<=9999){
      termo2=""+termo2;
    }
  }else{
    flag_analog=0;
    lux=analogRead(A2);
    lux2=String(lux);
    if(lux<0){
      lux2="-001";
    }else if(lux>=0 && lux<=9){
      lux2="000"+lux2;
    }else if(lux>=10 && lux<=99){
      lux2="00"+lux2;
    }else if(lux>=100 && lux<=999){
      lux2="0"+lux2;
    }else if(lux>=1000 && lux<=9999){
      lux2=""+lux2;
    }
  }
  var_ppm=digitalRead(pin_ppm);
  if(var_ppm==HIGH){
    if(flag_ppm!=2){
      //Desbordamiento
      if((millis()-ppm1)<60000){
        ppm1=((long)(millis())-ppm1);
        if(ppm1<=0){
          ppm2=-1;
        }else{
          ppm2=((float)(1000)/((float)ppm1));
          ppm2*=60;
        }
        //Reinicio del conteo
        ppm1=millis();
      }else{
        ppm1=millis();
        ppm2=-1;
      }
      dtostrf(ppm2,ppm_length-3,2,ppm);
      string_ppm=ppm;
      if(ppm2<0){
        string_ppm="-00001";
      }else if(ppm2>=0 && ppm2<=9){
        string_ppm=ppm;
        string_ppm="00"+string_ppm;
      }else if(ppm2>=10 && ppm2<=99){
        string_ppm=ppm;
        string_ppm="0"+string_ppm;
      }else if(ppm2>=100 && ppm2<=999){
        string_ppm=ppm;
      }
      
      flag_ppm=2;
    }
  }else{
    if(flag_ppm==2){
      flag_ppm=1;
    }
    
  }
  if(flag_ppm==1){
    flag_ppm=0;
  }
  Serial.print(termo2+" ");
  Serial.print(lux2+" ");
  Serial.print(string_ppm+" ");
  Serial.print(medida_string);
  Serial.print(" "+sg);
  Serial.print(" "+sm);
  Serial.print(" "+s_pwm);
  Serial.println("");
}
