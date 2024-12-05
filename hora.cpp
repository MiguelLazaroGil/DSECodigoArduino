#include "hora.h"

Hora::Hora() {
}

void Hora::loop(int lag, bool pantallaActual, bool configurar, bool confirmar ) {
   switch(estadoActual){
    case base:
        SumarHora(lag);
    break;
 
    case hora:
    break;
    case min:
    break;

   }
}
void SumarHora(int lag){

  tiempo+=lag;
  if(tiempo> MILISEGUNDOS_DIA){
    tiempo-=MILISEGUNDOS_DIA;
  }
}
