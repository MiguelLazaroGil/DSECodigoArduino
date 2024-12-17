#pragma once
#include "Pantalla.h"
class Cronometro: public Pantalla{

  public :
   Cronometro();
   void loop(long int seconds, bool pantallaActual, bool configurar,bool confirmar);
  long int GetTiempo() {
    return tiempo*60; //Para que salgan segundos  minutos
  }
};