#ifndef MALLA_H
#define MALLA_H

#include <list>
#include <string>
#include "Vertice.h"
#include "Arista.h"
#include "Cara.h"

using namespace std;

class Malla {
private:
  string mesh_name;
  int n;
  list<Vertice> vertices;
  list<Arista> aristas;
  list<Cara> caras;
  list<Malla> objetos;

public:
  Malla();
  Malla(string mesh_name, int n);
  ~Malla();

  /* Métodos de acceso */
  string getMesh_Name() const;
  int getN() const; 
  list<Vertice> getVertices()const; 
  list<Arista> getAristas() const;
  list<Cara> getCaras() const;
  list<Malla> getObjetos() const;

  /* Métodos de modificación */
  void setMesh_Name(string mesh_name);
  void setN(int n);
  void setVertices(const list<Vertice> vertices);
  void setAristas(const list<Arista> aristas);
  void setCaras(const list<Cara> caras);
  void setObjetos(const list<Malla> objetos) ;
  

  /* Operaciones */
  void agregarCara(const Cara& cara);
  void agregarVertice(const Vertice& vertice);
  void agregarObjeto(const Malla nuevaMalla);
  bool cargar(const string& nombreArchivo);
  int contarAristas() const;
  void listado();
  void envolvente(string nombreObjeto);
  void envolventeGlobal();
  void descargar(string nombreObjeto);
  void guardar(string nombreObjeto, string nombreArchivo);
};

#endif
