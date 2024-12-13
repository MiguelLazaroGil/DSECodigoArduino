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
    //Aritmetica modular y tal para cada numero
}
int botonPulsado(float voltaje){
// Pulsador 1
  if(voltaje >= 1.25 && voltaje <2.5)
  {
    return 1;
  }
  // Pulsador 2
  else if(voltaje >= 2.5 && voltaje <3.75)
  {
    return 2;
  }
  // Pulsador 3
  else if(voltaje >= 3.75 && voltaje <=5)
  {
    return 3;
  }else{
    return -1;
  }
}

void SiguientePantalla() {
  int temp = pantallaActual;
  temp = (temp + 1) % NUM_PANTALLAS;
  pantallaActual = (EstadosPantallas)temp;
}
void loop() {
  // put your main code here, to run repeatedly:
    // Leer el pin analógico
  int valorA4 = analogRead(pinEntrada);
  // Convertir a voltios el valor analógico
  float voltaje = valorA4 * (5.0/1023.0);
  // Mostramos los voltios en el monitor serie
  Serial.println(voltaje);
  int numBoton=botonPulsado(voltaje);
    bool configurar = (botonPulsado==2);
    bool confirmar = (botonPulsado==1);
    bool cambiar = (botonPulsado==0);

  {  //cambiar de pantallas
    if (cambiar) {
      SiguientePantalla();
    }
  }
  { 

    //Dos opciones de codigo:
    //Primera:
    for (int i = 0; i < NUM_PANTALLAS; i++) {
      pantallas[i]->loop( (i == (int)pantallaActual), configurar, configurar);
    }
    //Segunda:
    hora.loop(pantallaActual==0, configurar, confirmar);
    temporizador.loop(pantallaActual==1, configurar, confirmar);
    cronometro.loop(pantallaActual==2, configurar, confirmar);
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
