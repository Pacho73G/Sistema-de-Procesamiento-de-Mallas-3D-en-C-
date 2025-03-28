#ifndef CARA_H
#define CARA_H


#include <list>
#include "Vertice.h"
using namespace std;

class Cara {
private:
  list<int> ij_k;

public:
  /*Constructor por defecto*/
  Cara();

  /*Constructor con parametros*/
  Cara (list<int> ij_k);

  /*Destructor*/
  ~Cara();

  /*Metodos de acceso*/
  const list<int> getVertices() const;

  /*Metodos de modificacion*/
  void setVertices(list<int> vertices);
  
void agregarVertice(int indice) {
  this->ij_k.push_back(indice);  
  }
};


#endif
