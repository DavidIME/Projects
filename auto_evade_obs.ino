//Código de robot evade obstaculos y control por Bluetooth. 
//Este código es el control de motores y la comunicación por medio Bluetooth con la aplicación de celular
//Posee un modo automatico con lo que se sirve para evadir obstaculos con un sensor HC-SR04
//Y un modo manual donde se controla su movimiento por medio de la aplicación de celular.
//Motores A
int motorPin1 = 11;
int motorPin2 = 10;
//Motores B
int motorPin3 = 6;
int motorPin4 = 5;
//velocidad 
int vel = 255;            //velocidad de los motores a 255 (max)
int estado = 'c';         //inicia detenido
//variables del sensor ultrasonico 
int pecho = 2;            //define el pin 2 como pecho 
int ptrig = 3;            //define el pin 3 como ptrig
int duracion, distancia;  //variables necesarias para el calculo de distancia

void setup() {
   Serial.begin(9600);          //Inicia puerto serial para comunicación bluetooth
   pinMode(motorPin1, OUTPUT);
   pinMode(motorPin2, OUTPUT);
   pinMode(motorPin3, OUTPUT);
   pinMode(motorPin4, OUTPUT);
   pinMode(pecho,      INPUT);  //define el pin 2 como entrada (pecho)
   pinMode(ptrig,     OUTPUT);  //define el pin 3 como salida  (ptrig)
   pinMode(13,        OUTPUT);  //define el led del arduino como alarma visual
}


void loop() {
  if(Serial.available()>0)
  {
    estado = Serial.read();     //el bluetooth y almacena el estado  
  }

  if(estado == 'A')             //auto hacia enfrente
  {
   analogWrite(motorPin1, vel);
   analogWrite(motorPin2,   0);
   analogWrite(motorPin3, vel);
   analogWrite(motorPin4,   0);
  }

  if(estado == 'B')           //auto hacia la izquierda
  {
   analogWrite(motorPin1,   0);
   analogWrite(motorPin2, vel);
   analogWrite(motorPin3, vel);
   analogWrite(motorPin4,   0); 
  }

  if(estado == 'C')           //auto detenido 
  {
   analogWrite(motorPin1, 0);
   analogWrite(motorPin2, 0);
   analogWrite(motorPin3, 0);
   analogWrite(motorPin4, 0);  
  }

  if(estado == 'D')           //auto hacia la derecha
  {
   analogWrite(motorPin1, vel);
   analogWrite(motorPin2,   0);
   analogWrite(motorPin3,   0);
   analogWrite(motorPin4, vel);
  }

  if(estado == 'E')             //auto hacia atras
  {
   analogWrite(motorPin1,   0);
   analogWrite(motorPin2, vel);
   analogWrite(motorPin3,   0);
   analogWrite(motorPin4, vel);
  }

  if(estado == 'F')             //función para sensar distancia
  {
    digitalWrite(ptrig, HIGH);  //genera el pulso del trigger por 10us
    delay(0.01);
    digitalWrite(ptrig,  LOW);

    duracion = pulseIn(pecho, HIGH);    //lee el tiempo del echo
    distancia = (duracion/2)/29;        //calcula la distancia en cm
    delay(10);

    if(distancia <= 15 && distancia >= 2) //si la distancia es menor a 15 cm 
    {
      digitalWrite(13, HIGH);             //enciende LED de alarma
      //para los motores por 500 milisegundos
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0); 
      delay(800);
      //reversa por 500 milisegundos
      analogWrite(motorPin1,   0);
      analogWrite(motorPin2, vel);
      analogWrite(motorPin3,   0);
      analogWrite(motorPin4, vel);
      delay(900);
      //para los motores por 400 milisegundos
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 0);
      analogWrite(motorPin3, 0);
      analogWrite(motorPin4, 0); 
      delay(500);
      //giramos a la izquierda 1200 milisegundos
      analogWrite(motorPin1,   0);
      analogWrite(motorPin2, vel);
      analogWrite(motorPin3, vel);
      analogWrite(motorPin4,   0); 
      delay(1200);
      //APAGAMOS EL LED
      digitalWrite(13, LOW);
    }
    else                            //nos desplazamos hacia enfrente si no hay obstaculos
    {
     analogWrite(motorPin1, vel);
     analogWrite(motorPin2,   0);
     analogWrite(motorPin3, vel);
     analogWrite(motorPin4,   0);
    }
  }
  if(estado == 'G'){
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
    }
}
