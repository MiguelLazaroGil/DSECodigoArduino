#pragma once
#include "Pantalla.h"
class Temporizador: public Pantalla{

  public :
   Temporizador();
   void loop(int lag, bool pantallaActual, bool configurar,bool confirmar);

};