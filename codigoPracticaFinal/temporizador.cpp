#include "Temporizador.h"

Temporizador::Temporizador() {

}

void Temporizador::loop(long int seconds, bool pantallaActual, bool configurar, bool confirmar ) {
   if (configurar) {
    tiempo = 0;
    marcaTiempo = seconds;
    estadoActual = min;
    return;
  }
  switch (estadoActual) {
    case base:
      tiempo = seconds - marcaTiempo;
      break;


    case min:
    
      if ((seconds - marcaTiempo) > 1) {
        marcaTiempo = seconds;
        tiempo += 60;
      }
      if (confirmar) {
        estadoActual = sec;
        marcaTiempo = seconds;
      }
    case sec:
       if ((seconds - marcaTiempo) > 1) {
        marcaTiempo = seconds;
        tiempo += 1;
      }
      if (confirmar) {
        estadoActual = base;
        marcaTiempo = seconds-tiempo;
       // tiempo= seconds -marcaTiempo;
      }
      break;
  }
}