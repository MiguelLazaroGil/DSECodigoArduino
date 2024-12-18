#include "Cronometro.h"

Cronometro::Cronometro() {
  estadoActual=parado;
}
void Cronometro::loop(long int seconds, bool pantallaActual, bool configurar, bool confirmar) {
  if (confirmar && pantallaActual) {
    //pararse
    if (estadoActual != parado) {
      estadoActual = parado;
    }else{
      marcaTiempo = (seconds - tiempo);
      estadoActual=base;
    }
  }
  if (configurar && pantallaActual) {
    //resetear todo
    marcaTiempo = seconds;
    estadoActual = base;
  }
  if (estadoActual != parado) {

    tiempo = seconds - marcaTiempo;
  }

}