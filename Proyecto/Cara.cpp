#include "Cara.h"

/*Constructor por defecto*/
Cara::Cara() {}

/*Constructor con parametros*/
Cara::Cara(list<int> ij_k) : ij_k(ij_k) {}

/*Destructor*/
Cara::~Cara() {}

/*Metodos de acceso*/
const list<int> Cara::getVertices() const{
  return ij_k;
}

/*Metodos de modificacion*/
void Cara::setVertices(list<int> ij_k) {
  this->ij_k = ij_k;
}


