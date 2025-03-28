#ifndef ARISTA_H
#define ARISTA_H

class Arista {
private:
  /* Las aristas unen pares de vertices */
  int v1, v2;
public:
/*Constructor por defecto*/
Arista();

/*Constructor con parametros*/
Arista(int v1, int v2);

/*Destructor*/
~Arista();

/*Metodos de acceso*/
int getV1();
int getV2();

/*Metodos de modificacion*/
void setV1(int v1);
void setV2(int v2);
};

#endif
