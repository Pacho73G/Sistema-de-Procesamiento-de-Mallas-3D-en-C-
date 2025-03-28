#ifndef VERTICE_H
#define VERTICE_H

class Vertice {
private:
  /*Coordenadas*/
  float xi,yi,zi;
  

public:
  /*Constructor por defecto*/
  Vertice();

  /*Constructor con parametros*/
  Vertice(float xi, float yi, float zi);

  /*Destructor*/
  ~Vertice();

  /*Metodos de acceso*/
  float getXi() const;
  float getYi() const;
  float getZi() const;

  /*Metodos de modificacion*/
  void setXi(float xi);
  void setYi(float yi);
  void setZi(float zi);

  bool operator==(const Vertice& otro) const {
      return (xi == otro.xi) && (yi == otro.yi) && (zi == otro.zi);
  }
};

#endif
