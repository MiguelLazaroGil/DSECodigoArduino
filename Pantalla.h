#pragma once
#define MILISEGUNDOS_DIA 86.400.000
#define MILISEGUNDOS_HORA 3.600.000
class Pantalla {
  enum Estados {
    base, //Para cuando no se este editando nada
    hora, //Para cuando se este editando esto
    min, //Para cuando se este editando esto
    segundo //Para cuando se este editando esto
  };
protected:
  Estados estadoActual;
  long int tiempo;

public:
  
  Pantalla() {
    estadoActual = base;
    tiempo = 0;
  };
  //virtual void loop(bool , bool ,bool ) = 0;
  virtual void loop(int lag, bool pantallaActual, bool configurar,bool confirmar) = 0;
  long int GetTiempo() {
    return tiempo;
  }
};