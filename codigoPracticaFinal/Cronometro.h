#pragma once
#include "Pantalla.h"
class Cronometro: public Pantalla{

  public :
   Cronometro();
   void loop(int lag, bool pantallaActual, bool configurar,bool confirmar);

};