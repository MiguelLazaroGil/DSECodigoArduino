//#include "Pantalla.h"
#include <TimerOne.h>
#include "hora.h"
#include "temporizador.h"
#include "Cronometro.h"
#define NUM_PANTALLAS 3
enum EstadosPantallas {
  PHora,
  PTemporizador,
  PCronometro
};
Hora hora;
Temporizador temporizador;
Cronometro cronometro;

Pantalla* pantallas[NUM_PANTALLAS];
EstadosPantallas pantallaActual;

//Entradas
int boton = A4;
//Salidas
int solenoide[16]= {13,12,11,10,9,8,7,6,5,4,3,2,A0,A1,A2,A3};

long int seconds;
long int ultimoSegundoPulsado;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(boton, INPUT);
  seconds = 0;
  ultimoSegundoPulsado=0;
  pantallaActual = PHora;
  pantallas[0] = &hora;
  pantallas[1] = &temporizador;
  pantallas[2] = &cronometro;
  //Esto hace que haya una interrupcion
  Timer1.initialize(1000000);  
  Timer1.attachInterrupt(updateTime);
}

void updateTime() {
  seconds++;
}

void display(long int tiempo) {
  //Aritmetica modular y tal para cada numero
  int hora = tiempo / 3600;
  int minuto = (tiempo % 3600) / 60;
  if (pantallaActual == PHora) {
    hora = hora % 24;
  } else {
    hora = hora % 60;
  }
  int primerNum = hora / 10;
  int segunNum = hora % 10;
  int tercerNum = minuto / 10;
  int cuartoNum = minuto % 10;
  displayNum(primerNum, 0);
  displayNum(segunNum, 1);
  displayNum(tercerNum, 2);
  displayNum(cuartoNum, 3);

  Serial.print("\nHora: ");
  Serial.print(primerNum);
  Serial.print(segunNum);

  Serial.print("\nMin: ");
  Serial.print(tercerNum);
  Serial.println(cuartoNum);
  
}
void displayNum(int num, int pos) {
  //////////////////
  ////PIN1///PIN2///
  //////////////////
  ////PIN3///PIN4///
  //////////////////
  int pin1 = solenoide[0 + pos * 4];
  int pin2 = solenoide[1 + pos * 4];
  int pin3 = solenoide[2 + pos * 4];
  int pin4 = solenoide[3 + pos * 4];
  switch (num) {
    case 9:

      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      break;
    case 8:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);
      break;
    case 7:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);
      break;
    case 6:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      break;
    case 5:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      break;
    case 4:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      break;
    case 3:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      break;
    case 2:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      break;
    case 1:

      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      break;
    case 0:
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);
      break;
  }
}
int botonPulsado(float voltaje) {
  if(ultimoSegundoPulsado==seconds){return -1;}
  // Pulsador 1
  if (voltaje >= 1.00 && voltaje < 2.5) {
    ultimoSegundoPulsado=seconds;
    Serial.print("Boton 1 pulsado");
    return 1;
  }
  // Pulsador 2
  else if (voltaje >= 2.5 && voltaje < 3.75) {
    ultimoSegundoPulsado=seconds;
    Serial.print("Boton 2 pulsado");
    return 2;
  }
  // Pulsador 3
  else if (voltaje >= 3.75 && voltaje <= 5) {
    ultimoSegundoPulsado=seconds;
    Serial.print("Boton 3 pulsado");
    return 3;
  } 
    return -1;
}

void SiguientePantalla() {
  int temp = pantallaActual;
  temp = (temp + 1) % NUM_PANTALLAS;
  pantallaActual = (EstadosPantallas)temp;
  Serial.print("Estamos en la pantallaa: ");
  Serial.println(pantallaActual);
}
void loop() {
  // put your main code here, to run repeatedly:
  // Leer el pin analógico
  int valorA4 = analogRead(boton);
  // Convertir a voltios el valor analógico
  float voltaje = valorA4 * (5.0 / 1023.0);
  // Mostramos los voltios en el monitor serie
  Serial.println(voltaje);
  int numBoton = botonPulsado(voltaje);
  bool configurar = (numBoton == 3);
  bool confirmar = (numBoton == 2);
  bool cambiar = (numBoton == 1);

  //cambiar de pantallas
  if (cambiar) {
    SiguientePantalla();
  }

  for (int i = 0; i < NUM_PANTALLAS; i++) {
    pantallas[i]->loop(seconds, (i == (int)pantallaActual), configurar, confirmar);
  }


  //Display pantalla actual
  display(pantallas[pantallaActual]->GetTiempo());
  Serial.println(seconds);
  delay(50);
}
