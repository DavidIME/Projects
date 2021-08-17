//Código para el control de un brazo robot pequeño de 4 grados de libertad
//El control se realiza por medio del uso de potenciometros 
#include <Servo.h> //libreria de los sevos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int pos1  = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;

int pot1 = A0; 
int pot2 = A1;
int pot3 = A3;
int pot4 = A4;

int valorPot1 = 0;
int valorPot2 = 0;
int valorPot3 = 0;
int valorPot4 = 0;

int botonAutomatico = 12; //se conecta al pin 7 rutina del primer boton
int estadoAutomatico = 0; //se guarda el estado del boton de rutina


void setup() {
  // declaramos los potenciometros y botones
  servo1.attach(2); //servo base
  pinMode(pot1, INPUT); //entrada del pot1 para la base
  servo2.attach(4);  //servo hombro
  pinMode(pot2, INPUT); //entrada control hombro
  servo3.attach(7); //servo brazo
  pinMode(pot3, INPUT); //entrada control brazo
  servo4.attach(8); //servo garra
  pinMode(pot4, INPUT); //entrada control garra
  pinMode(botonAutomatico, INPUT_PULLUP); //señal de boton como entrada digital.
  Serial.begin(9600);   
 

}

void loop() {
  
  //control del hombro
  valorPot2=analogRead(pot2);
  valorPot2 = map(valorPot2,0,1023,130,30);
  servo2.write(valorPot2);
  //control del brazo
  valorPot3 = analogRead(pot3);
  valorPot3 = map(valorPot3,0,1023,130,30);
  servo3.write(valorPot3);
  //control de la base
  valorPot1 = analogRead(pot1);
  valorPot1 = map(valorPot1,0,1023,10,170);
  servo1.write(valorPot1);
  //control de la garra
  valorPot4 = analogRead(pot4);
  valorPot4 = map(valorPot4,0,1023,150,10);
  servo4.write(valorPot4);

  delay(400); //para la estabilidad del brazo

}
