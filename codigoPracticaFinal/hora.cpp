#include "hora.h"

Hora::Hora() {
}

void Hora::loop(long int seconds, bool pantallaActual, bool configurar, bool confirmar) {
  if (configurar) {
    tiempo = 0;
    marcaTiempo = seconds;
    estadoActual = hora;
    return;
  }
  switch (estadoActual) {
    case base:
      tiempo = seconds - marcaTiempo;
      break;

    case hora:
      if ((seconds - marcaTiempo) > 1) {
        marcaTiempo = seconds;
        tiempo += 3600;
      }
      if (confirmar) {
        estadoActual = min;
        marcaTiempo = seconds;
      }
      break;
    case min:
      if ((seconds - marcaTiempo) > 1) {
        marcaTiempo = seconds;
        tiempo += 60;
      }
      if (confirmar) {
        estadoActual = base;
        marcaTiempo = seconds-tiempo;
       // tiempo= seconds -marcaTiempo;
      }
      break;
  }
}
