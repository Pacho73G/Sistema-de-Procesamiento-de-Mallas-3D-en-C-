#include "Vertice.h"

/*Constructor por defecto*/
Vertice::Vertice():xi(0),yi(0),zi(0){}

/*Constructor con parametros*/
Vertice::Vertice(float xi, float yi, float zi):xi(xi),yi(yi),zi(zi){}

/*Destructor*/
Vertice::~Vertice(){}

/*Metodos de acceso*/

float Vertice::getXi() const{
  return xi;
}
float Vertice::getYi() const{
  return yi;
}
float Vertice::getZi() const{
  return zi;
}

/*Metodos de modificacion*/
void Vertice::setXi(float xi){
  this->xi=xi;
}
void Vertice::setYi(float yi){
  this->yi=yi;
}
void Vertice::setZi(float zi){
  this->zi=zi;
}