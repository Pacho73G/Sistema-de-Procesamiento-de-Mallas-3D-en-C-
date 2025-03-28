#include "KdTree.h"
#include "Malla.h"
#include <cmath>
#include <limits>
#include <algorithm>
#include <iostream>


KdNode::KdNode(const Vertice& v) : punto(v), izquierda(nullptr), derecha(nullptr) {}

KdTree::KdTree() : raiz(nullptr), dimension(3) {}

KdTree::~KdTree() {
    destruirArbol(raiz);
}

void KdTree::destruirArbol(KdNode* nodo) {
    if (nodo != nullptr) {
        destruirArbol(nodo->izquierda);
        destruirArbol(nodo->derecha);
        delete nodo;
    }
}

void KdTree::insertar(const Vertice& punto) {
    raiz = insertarRec(raiz, punto, 0);
}

KdNode* KdTree::insertarRec(KdNode* nodo, const Vertice& punto, int profundidad) {
    if (nodo == nullptr) {
        return new KdNode(punto);
    }

    int eje = profundidad % dimension;

    if (eje == 0) {
        if (punto.getXi() < nodo->punto.getXi()) {
            nodo->izquierda = insertarRec(nodo->izquierda, punto, profundidad + 1);
        } else {
            nodo->derecha = insertarRec(nodo->derecha, punto, profundidad + 1);
        }
    } else if (eje == 1) {
        if (punto.getYi() < nodo->punto.getYi()) {
            nodo->izquierda = insertarRec(nodo->izquierda, punto, profundidad + 1);
        } else {
            nodo->derecha = insertarRec(nodo->derecha, punto, profundidad + 1);
        }
    } else {
        if (punto.getZi() < nodo->punto.getZi()) {
            nodo->izquierda = insertarRec(nodo->izquierda, punto, profundidad + 1);
        } else {
            nodo->derecha = insertarRec(nodo->derecha, punto, profundidad + 1);
        }
    }

    return nodo;
}

Vertice KdTree::buscarMasCercano(const Vertice& objetivo) {
    if (raiz == nullptr) {
        return Vertice(); 
    }

    float mejorDist = std::numeric_limits<float>::max();
    KdNode* mejorNodo = buscarMasCercanoRec(raiz, objetivo, 0, raiz, mejorDist);
    return mejorNodo->punto;
}

KdNode* KdTree::buscarMasCercanoRec(KdNode* nodo, const Vertice& objetivo, int profundidad, KdNode* mejor, float& mejorDist) {
    if (nodo == nullptr) {
        return mejor;
    }

    float distActual = distanciaEuclidiana(nodo->punto, objetivo);
    if (distActual < mejorDist) {
        mejorDist = distActual;
        mejor = nodo;
    }

    int eje = profundidad % dimension;
    KdNode* siguienteRama;
    KdNode* otraRama;

    if (eje == 0) {
        if (objetivo.getXi() < nodo->punto.getXi()) {
            siguienteRama = nodo->izquierda;
            otraRama = nodo->derecha;
        } else {
            siguienteRama = nodo->derecha;
            otraRama = nodo->izquierda;
        }
    } else if (eje == 1) {
        if (objetivo.getYi() < nodo->punto.getYi()) {
            siguienteRama = nodo->izquierda;
            otraRama = nodo->derecha;
        } else {
            siguienteRama = nodo->derecha;
            otraRama = nodo->izquierda;
        }
    } else {
        if (objetivo.getZi() < nodo->punto.getZi()) {
            siguienteRama = nodo->izquierda;
            otraRama = nodo->derecha;
        } else {
            siguienteRama = nodo->derecha;
            otraRama = nodo->izquierda;
        }
    }

    mejor = buscarMasCercanoRec(siguienteRama, objetivo, profundidad + 1, mejor, mejorDist);

    float distEje;
    if (eje == 0) {
        distEje = std::abs(objetivo.getXi() - nodo->punto.getXi());
    } else if (eje == 1) {
        distEje = std::abs(objetivo.getYi() - nodo->punto.getYi());
    } else {
        distEje = std::abs(objetivo.getZi() - nodo->punto.getZi());
    }

    if (distEje < mejorDist) {
        mejor = buscarMasCercanoRec(otraRama, objetivo, profundidad + 1, mejor, mejorDist);
    }

    return mejor;
}

float KdTree::distanciaEuclidiana(const Vertice& a, const Vertice& b) {
    float dx = a.getXi() - b.getXi();
    float dy = a.getYi() - b.getYi();
    float dz = a.getZi() - b.getZi();
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

void KdTree::construirDesdeList(const std::list<Vertice>& vertices) {
    // Destruir el árbol existente si lo hay
    destruirArbol(raiz);
    raiz = nullptr;

    // Construir el nuevo árbol
    for (const auto& vertice : vertices) {
        insertar(vertice);
    }
}

void KdTree::vCercanoNombre(float px, float py, float pz, const std::string& nombreObjeto, const std::list<Malla>& mallas) {
    
    auto it = std::find_if(mallas.begin(), mallas.end(), [&](const Malla& malla) {
        return malla.getMesh_Name() == nombreObjeto;
    });

    if (it == mallas.end()) {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria" << std::endl;
        return;
    }
    
    const Malla& mallaEncontrada = *it;
    construirDesdeList(mallaEncontrada.getVertices());//construyo el arbol con los vertices de la malla*********

    Vertice objetivo(px, py, pz);
    Vertice verticeCercano = buscarMasCercano(objetivo);
    float distancia = distanciaEuclidiana(objetivo, verticeCercano);

    std::cout << "El vertice mas cercano al punto (" << px << ", " << py << ", " << pz << ") es: "
              << verticeCercano.getXi() << ", " << verticeCercano.getYi() << ", " << verticeCercano.getZi()
              << " y tiene una distancia de " << distancia << std::endl;
}

void KdTree::vCercano(float px, float py, float pz, const std::list<Malla>& mallas) {
    if (mallas.empty()) {
        std::cout << "Ningun objeto ha sido cargado en memoria" << std::endl;
        return;
    }

    Vertice objetivo(px, py, pz);
    Vertice verticeMasCercano;
    std::string nombreObjetoMasCercano;
    float distanciaMasCercana = std::numeric_limits<float>::max();
    int indiceVerticeMasCercano = -1;

    for (const auto& malla : mallas) {
        const auto& vertices = malla.getVertices();
        construirDesdeList(vertices);   //Construyo el arbol con los vertices de la malla*******

        Vertice verticeCercano = buscarMasCercano(objetivo);
        float distanciaActual = distanciaEuclidiana(objetivo, verticeCercano);

        auto it = std::find(vertices.begin(), vertices.end(), verticeCercano);
        int indiceActual = std::distance(vertices.begin(), it);

        if (distanciaActual < distanciaMasCercana) {
            distanciaMasCercana = distanciaActual;
            verticeMasCercano = verticeCercano;
            nombreObjetoMasCercano = malla.getMesh_Name();
            indiceVerticeMasCercano = indiceActual;
        }
    }

    std::cout << "El vertice " << indiceVerticeMasCercano << " ("
              << verticeMasCercano.getXi() << ", " << verticeMasCercano.getYi() << ", " << verticeMasCercano.getZi() 
              << ") del objeto " << nombreObjetoMasCercano
              << " es el más cercano al punto (" << px << ", " << py << ", " << pz 
              << "), a una distancia de " << distanciaMasCercana << std::endl;
}

void KdTree::v_cercanos_caja(const string& nombreObjeto, const std::list<Malla>& mallas) {

    // Aqui ya no necesitas crear la instancia Malla vacía
    bool encontrado = false;
    Malla mallaEncontrada;

    // Recorrer la lista de mallas proporcionada como argumento
    for(const Malla& obj : mallas) {
        if(obj.getMesh_Name() == nombreObjeto) {
            mallaEncontrada = obj;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        std::cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria" << std::endl;
        return;
    }

    // Obtener los vertices de la malla encontrada
    list<Vertice> vertices = mallaEncontrada.getVertices();
    if (vertices.empty()) {
        std::cout << "El objeto " << nombreObjeto << " no tiene vertices" << std::endl;
        return;
    }

    construirDesdeList(vertices); //Construccion de arbol con los vertices de la malla*********

    // Inicializar pmin y pmax con el primer vertice
    auto it = vertices.begin();
    Vertice pmin = *it;
    Vertice pmax = *it;
    ++it;

    for(; it != vertices.end(); ++it) {
        if(it->getXi() < pmin.getXi()) pmin.setXi(it->getXi());
        if(it->getYi() < pmin.getYi()) pmin.setYi(it->getYi());
        if(it->getZi() < pmin.getZi()) pmin.setZi(it->getZi());
        if(it->getXi() > pmax.getXi()) pmax.setXi(it->getXi());
        if(it->getYi() > pmax.getYi()) pmax.setYi(it->getYi());
        if(it->getZi() > pmax.getZi()) pmax.setZi(it->getZi());
    }

    // Crear los vertices de la caja envolvente
    list<Vertice> esquinasCaja;
    esquinasCaja.push_back(Vertice(pmin.getXi(), pmin.getYi(), pmin.getZi())); // esquina 1
    esquinasCaja.push_back(Vertice(pmax.getXi(), pmin.getYi(), pmin.getZi())); // esquina 2
    esquinasCaja.push_back(Vertice(pmax.getXi(), pmax.getYi(), pmin.getZi())); // esquina 3
    esquinasCaja.push_back(Vertice(pmin.getXi(), pmax.getYi(), pmin.getZi())); // esquina 4
    esquinasCaja.push_back(Vertice(pmin.getXi(), pmin.getYi(), pmax.getZi())); // esquina 5
    esquinasCaja.push_back(Vertice(pmax.getXi(), pmin.getYi(), pmax.getZi())); // esquina 6
    esquinasCaja.push_back(Vertice(pmax.getXi(), pmax.getYi(), pmax.getZi())); // esquina 7
    esquinasCaja.push_back(Vertice(pmin.getXi(), pmax.getYi(), pmax.getZi())); // esquina 8

    std::cout << "\nLos vertices del objeto " << nombreObjeto 
              << " mas cercanos a las esquinas de su caja envolvente son:\n";
    std::cout << "Esquina\tVertice\tDistancia\n";

    // Para cada esquina de la caja, encontrar el vértice mas cercano
    int esquinaNum = 1;
    for(const Vertice& esquina : esquinasCaja) {
        Vertice verticeCercano = buscarMasCercano(esquina);
        float distancia = distanciaEuclidiana(esquina, verticeCercano);

        // Encontrar el indice del vértice más cercano
        int indice = 0;
        auto verticeIt = vertices.begin();
        for(int i = 0; verticeIt != vertices.end(); ++verticeIt, ++i) {
            if(verticeIt->getXi() == verticeCercano.getXi() && 
               verticeIt->getYi() == verticeCercano.getYi() && 
               verticeIt->getZi() == verticeCercano.getZi()) {
                indice = i;
                break;
            }
        }

        std::cout << esquinaNum << " (" 
                  << esquina.getXi() << ", " 
                  << esquina.getYi() << ", " 
                  << esquina.getZi() << ") "
                  << indice << " ("
                  << verticeCercano.getXi() << ", "
                  << verticeCercano.getYi() << ", "
                  << verticeCercano.getZi() << ") "
                  << distancia << "\n";
        esquinaNum++;
    }
}
