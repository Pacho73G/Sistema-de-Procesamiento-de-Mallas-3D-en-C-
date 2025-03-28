#ifndef KDTREE_H
#define KDTREE_H

#include "Vertice.h"
#include "Malla.h"
#include <list>
#include <iostream>

class KdNode {
public:
    Vertice punto;
    KdNode* izquierda;
    KdNode* derecha;

    KdNode(const Vertice& v);
};

class KdTree {
private:
    KdNode* raiz;
    int dimension;

    KdNode* insertarRec(KdNode* nodo, const Vertice& punto, int profundidad);
    KdNode* buscarMasCercanoRec(KdNode* nodo, const Vertice& objetivo, int profundidad, KdNode* mejor, float& mejorDist);
    
    void destruirArbol(KdNode* nodo);

public:
    KdTree();
    ~KdTree();
    float distanciaEuclidiana(const Vertice& a, const Vertice& b);
    void insertar(const Vertice& punto);
    Vertice buscarMasCercano(const Vertice& objetivo);
    void construirDesdeList(const std::list<Vertice>& vertices);
    void vCercanoNombre(float px, float py, float pz, const std::string& nombreObjeto, const std::list<Malla>& mallas);
    void vCercano(float px, float py, float pz, const std::list<Malla>& mallas);
void v_cercanos_caja(const string& nombreObjeto, const std::list<Malla>& mallas);
};

#endif // KDTREE_H