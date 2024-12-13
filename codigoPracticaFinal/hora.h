#pragma once
#include "Pantalla.h"
class Hora : public Pantalla
{

  public :
   Hora();
   void loop(int lag, bool pantallaActual, bool configurar,bool confirmar);

};