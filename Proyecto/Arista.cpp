#include "Arista.h"

/*Constructor por defecto*/
Arista::Arista():v1(0),v2(0){}

/*Constructor con parametros*/
Arista::Arista(int v1, int v2):v1(v1),v2(v2){}

/*Destructor*/
Arista::~Arista(){}

/*Metodos de acceso*/
int Arista::getV1(){
  return v1;
}
int Arista::getV2(){
  return v2;
}

/*Metodos de modificacion*/
void Arista::setV1(int v1){
  this->v1=v1;
}
void Arista::setV2(int v2){
  this->v2=v2;
}
