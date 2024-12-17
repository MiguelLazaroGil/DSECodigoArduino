#pragma once
#include "Pantalla.h"
class Hora : public Pantalla
{

  public :
   Hora();
   void loop(long int seconds, bool pantallaActual, bool configurar,bool confirmar);

};