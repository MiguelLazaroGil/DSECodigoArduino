//#include "Pantalla.h"
#include "hora.h"
#include "temporizador.h"
#include "Cronometro.h"
#define NUM_PANTALLAS 3
enum EstadosPantallas {
  Hora,
  Temporizador,
  Cronometro
};
Hora hora;
Temporizador temporizador;
Cronometro cronometro;

Pantalla* pantallas[NUM_PANTALLAS];
EstadosPantallas pantallaActual;

//Entradas
int botonCambioPantallas=13;
int botonConfig=12;
int botonConfirmar=11;
//Salidas
//int solenoide[]

void setup() {
  // put your setup code here, to run once:

  pantallaActual = Hora;
  pantallas[0] = &hora;
  pantallas[1] = &temporizador;
  pantallas[2] = &cronometro;
}

void display(long int tiempo) {

}
void SiguientePantalla() {
  int temp = pantallaActual;
  temp = (temp + 1) % NUM_PANTALLAS;
  pantallaActual = (EstadosPantallas)temp;
}
void loop() {
  // put your main code here, to run repeatedly:

  {  //cambiar de pantallas
    if (digitalRead(botonCambioPantallas) == HIGH) {
      SiguientePantalla();
    }
  }
  {  //Actualizar Todo
    bool configurar = digitalRead(botonConfig) == HIGH;
    bool confirmar = digitalRead(botonConfirmar) == HIGH;

    //Dos opciones de codigo:
    //Primera:
    for (int i = 0; i < NUM_PANTALLAS; i++) {
      pantallas[i]->loop( (i == (int)pantallaActual), configurar, configurar);
    }
    //Segunda:
    hora.loop(pantallaActual, configurar, confirmar);
    temporizador.loop(pantallaActual, configurar, confirmar);
    cronometro.loop(pantallaActual, configurar, confirmar);
    //Fin actualizar todo
  }
  {  //Display pantalla actual

    //Dos opciones de cogido:
      //Primera:
    switch (pantallaActual) {
      case Hora:
        display(hora.GetTiempo());
        break;
      case Temporizador:
        display(temporizador.GetTiempo());
        break;
      case Cronometro:
        display(cronometro.GetTiempo());
        break;
    }

      //Segunda:
      display(pantallas[pantallaActual]->GetTiempo());
  }
}
