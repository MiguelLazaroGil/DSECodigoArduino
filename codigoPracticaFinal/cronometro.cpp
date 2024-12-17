#include "Cronometro.h"

Cronometro::Cronometro() {
}
void Cronometro::loop(long int seconds, bool pantallaActual, bool configurar, bool confirmar) {
  if (confirmar) {
    //pararse
    if (estadoActual != parado) {
      estadoActual = parado;
    }else{
      marcaTiempo += (seconds - tiempo);
      estadoActual=base;
    }
  }
  if (configurar) {
    //resetear todo
    marcaTiempo = seconds;
    estadoActual = base;
  }
  if (estadoActual != parado) {

    tiempo = seconds - marcaTiempo;
  }

}