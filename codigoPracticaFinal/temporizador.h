#pragma once
#include "Pantalla.h"
class Temporizador: public Pantalla{

  public :
   Temporizador();
   void loop(long int seconds, bool pantallaActual, bool configurar,bool confirmar);
    long int GetTiempo() {
      if(tiempo<0)tiempo=0;
    return tiempo*60; //Para que salgan segundos  minutos
  }
};