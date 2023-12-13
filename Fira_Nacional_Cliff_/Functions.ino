


void interruptR () {   // Função interrupt_motor
  motorR.isr();              // Chama o método isr(), que realiza a contagem do pulso
}
void interruptL () {   // Função interrupt_motor
  motorL.isr();              // Chama o método isr(), que realiza a contagem do pulso
}
void SetMotors() {
  motorR.hBridge(9, 10, 11);      // Pinos da ponte H
  motorR.setEncoderPin(2,  4); // Pinos do encoder
  motorR.setRR(21.3);    // Razão da caixa de redução é 30
  motorR.setPPR(11);
  motorR.setPIDconstants(kp, ki, kd);
  attachInterrupt(digitalPinToInterrupt(2), interruptR, FALLING);
  motorR.walk(0);

  motorL.hBridge(8, 7, 6);      // Pinos da ponte H
  motorL.setEncoderPin(3, 5); // Pinos do encoder
  motorL.setRR(21.3);    // Razão da caixa de redução é 30
  motorL.setPPR(11); // 11 pulsos que o encoder envia para cada volta dada em   // torno de seu eixo
  motorL.setPIDconstants(kp, ki, kd);
  motorL.invertDirection();
  attachInterrupt(digitalPinToInterrupt(3), interruptL, FALLING);
  motorL.walk(0);
  motorR.startCounting();
  motorL.startCounting();
  both.setGyreDegreesRatio(0.26, 90);
}


void distanceTU () {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  tempo = pulseIn(echo, HIGH);
  distanceT = tempo / 29.4 / 2;

}


void debug() {
  while (true) {
    both.stop();
  }
}
void Thebackstart() {
int pwm = 6;
int in1 = 7;
int in2 = 8;
int in3 = 9;
int in4 = 10;
int pwm2 = 11;


  while (contador == 0) {
    distanceTU();
    if (distanceT <= obstacledistance) {
      contador = 2;
      Serial.println("A distancia é menorrrrrrrr");
    }
    if (contador == 0) {
      while (distanceT >= obstacledistance) {
        Serial.println("A distancia é menor");
        distanceTU();
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwm, 59);
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
        analogWrite(pwm2, 59);
      }
      if (distanceT <= obstacledistance) {
        lado = 2;    
        contador = contador + 8;
      }
    }
  }
  if (contador == 2) {
    distanceTU();
    while (distanceT <= obstacledistance) {
      Serial.println("A distancia é maior");
      distanceTU();
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwm, 59);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(pwm2, 59);
    }
    if (distanceT >= obstacledistance) {
      
      lado = 1;
      contador = contador + 8;
    }
  }



}
// both.together(160,1,-160,-0.6); = 180°


void lerlinha() {
  sel = digitalRead(se);
  sdl = digitalRead(sd);
}

void lerVL () {
  distanceF = sensorF.readRangeContinuousMillimeters() * 0.1;
}
void SetVL() {
  sensorF.setTimeout(500);
  if (!sensorF.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensorF.startContinuous();
}
void Aiwnnmeubutao() {
  estadobotao = digitalRead(botao);
  digitalWrite(LED_BUILTIN, HIGH);
  while (contadorbotao == 0) {
    estadobotao = digitalRead(botao);
    if (estadobotao == 0) {
      delay(100);
      contadorbotao = contadorbotao + 1;

    }
  }
}
void Acelerar() {
int pwm = 6;
int in1 = 7;
int in2 = 8;
int in3 = 9;
int in4 = 10;
int pwm2 = 11;
 
  if (contadorStart == 0) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwm, 140);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
        analogWrite(pwm2, 250);
    Serial.println("oi");
    if (millis() - millisTarefa1 >= 150) { // 1000
      contadorStart = 1;
    }
  }
}

    
void Atacar(int valdist) {
  
  while (distanceF <= valdist) {
    lerVL();
    both.run(350); 
   
lerlinha();
ajustelinha();

   
    
    if (sdl == 0 && sel == 0) {
 both.together(-100, -0.25);
      both.turnDegree(100, 90);

  }

   
  
  }
}

void ajustelinha() {
  lerlinha();

  if (sel == 0) {
    motorL.walk(basespeed);
    motorR.walk(basespeed * ratio);

  }

  if (sdl == 0) {
    motorL.walk(basespeed * ratio);
    motorR.walk(basespeed);

  }
}

void fugircentro () {
  distanceTU();
  lerVL();
  lerlinha();

  if (sel == 0 && sdl == 0 && distanceT >= 15 && distanceF <= 20) {
    if (millis() - millisTarefa2 >= 4000) {
      both.together(-100, -0.25);
      both.turnDegree(-100, -90);
    }
  }


}
void leiturarobo(){
 // Serial.print("sel:");
 // Serial.print(sel);
  //Serial.println();
  
}
void escolherlado(){
  if(lado == 1){
    if(var == 0){
    both.turnDegree(150, 90);
    var = 1;
    }
  motorL.walk(vel1 * 0.54); //0.5
  motorR.walk(vel1 );
  }
  if(lado == 2){
    if(var2 == 0){
            both.turnDegree(-150,-138); 
            var2 = 1;
    }
      motorL.walk(vel1); //0.5
  motorR.walk(vel1 * 0.57 );
  }
}
