

#include <TwoMotors.h>
#include <DC_motor_controller.h>
#include <Wire.h>
#include <VL53L0X.h>


DC_motor_controller motorR;   // "mot" é o nome que usaremos a partir de agora
DC_motor_controller motorL;              //para nos referirmos ao motor físico.
TwoMotors both(&motorR, &motorL);
VL53L0X sensorF;

int kp = 1.8; // 1.8 1.5 0.06
int ki = 1.5  ;
int kd = 0.06;
int sd = 14;
int se = 15;
int sdl;
int sel;
int trig = 16;
int echo = 17;
int distanceT;
int tempo;
int distanceF;
int vel1 = 350;
int vel2 = 255;
int contador = 0;
int obstacledistance = 13; //18
int contadorStart = 0;
int botao = 12;
bool estadobotao;
int contadorbotao = 0;
unsigned long millisTarefa1 = millis();
unsigned long millisTarefa2 = millis();
int basespeed = 250;
int ratio = 0.685;
int lado = 0;
int var = 0;
int var2 = 0;


void setup() {
  Serial.begin(9600);
  Wire.begin();
  SetMotors();
  SetVL();

  pinMode(sd, INPUT);
  pinMode(se, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(botao, INPUT_PULLUP);
  Aiwnnmeubutao();
  Thebackstart();

  Serial.println("Passei");

}
void loop() {
  //Serial.println(millis());
  //leiturarobo();
    //Serial.println(distanceF);
    Serial.println(sel);
    //Serial.println(sdl);
  
  lerlinha();
  lerVL();
  distanceTU();
  Acelerar();
escolherlado();
  
  Atacar(20);
  fugircentro();
  ajustelinha();
  
}
