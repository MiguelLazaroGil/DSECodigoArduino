#pragma once
#define MILISEGUNDOS_DIA 86.400.000
#define MILISEGUNDOS_HORA 3.600.000
class Pantalla {
 
protected:
 enum Estados {
    base, //Para cuando no se este editando nada
    parado,
    hora, //Para cuando se este editando esto
    min, //Para cuando se este editando esto
    sec //Para cuando se este editando esto
  };
  Estados estadoActual;
  long int marcaTiempo;
  long int tiempo; //Tiempo a mostrar

public:
  
  Pantalla() {
    estadoActual = base;
    tiempo = 0;
  };
  //virtual void loop(bool , bool ,bool ) = 0;
  virtual void loop(long int seconds, bool pantallaActual, bool configurar,bool confirmar) = 0;
  virtual long int GetTiempo() {
    return tiempo;
  }
};