#ifndef GRAFO_H
#define GRAFO_H

#include <list>
#include <string>
#include <utility>     // Para pair
#include <iterator>    // Para advance
#include <cmath>
#include <sstream>
#include <map>
#include <set>
#include <limits>
#include <iostream>
#include <algorithm> // Necesario para std::min_element
#include <vector>    // Para usar std::vector, si es necesario
#include "Vertice.h"
#include "Malla.h"

template <class T>
class Grafo {
private:
    // Estructura que representa un vértice dentro del grafo
    struct NodoV {
        Vertice info;        // Información asociada al vertice
        bool marcado;  // Indica si el vértice está marcado o no
        int id;        // Identificador para el vertice

        // Constructor con parámetros
        NodoV(T i, int identificador) : info(i), marcado(false), id(identificador) {}
    };

    // Estructura que representa un arco entre dos vertices
    struct Arco {
        int origen;    // ID del vertice de origen
        int destino;   // ID del vertice de destino
        int costo;     // Costo  del arco si estan conectados

        // Constructor con parámetros
        Arco(int o, int d, int c) : origen(o), destino(d), costo(c) {}
    };

    // Lista de vértices del grafo
    std::list<NodoV> vertices;
    // Lista de arcos
    std::list<Arco> arcos;
    // Contador de vertices
    int numVertices;
    // Contador para generar IDs únicos
    static int nextId;

public:
    // Constructor del grafo sin parámetros
    Grafo() = default;


void InsVertice(T info) {
    vertices.push_back(NodoV(info, nextId++));
    numVertices++;
}
void InsArco(int origen, int destino, int costo) {
    // Verificar si el arco ya existe
    for(auto it = arcos.begin(); it != arcos.end(); ++it) {
        if(it->origen == origen && it->destino == destino) {
            it->costo = costo; // Actualizar costo si existe
            return;
        }
    }
    // Si no existe, crear nuevo arco
    arcos.push_back(Arco(origen, destino, costo));
}
void ElimArco(int origen, int destino) {
    arcos.remove_if([origen, destino](const Arco& arco) {
        return arco.origen == origen && arco.destino == destino;
    });
}

void ElimVertice(int id) {
    // Eliminar el vértice
    vertices.remove_if([id](const NodoV& v) { return v.id == id; });
    // Eliminar arcos relacionados con el vértice
    arcos.remove_if([id](const Arco& arco) {
        return arco.origen == id || arco.destino == id;
    });
    // Actualizar IDs de vértices y arcos
    for(auto& vertice : vertices) {
        if(vertice.id > id) vertice.id--;
    }
    for(auto& arco : arcos) {
        if(arco.origen > id) arco.origen--;
        if(arco.destino > id) arco.destino--;
    }
    numVertices--;
}
void MarcarVertice(int id) {
    for(auto& v : vertices) {
        if(v.id == id) {
            v.marcado = true;
            return;
        }
    }
}

void DesmarcarVertice(int id) {
    for(auto& v : vertices) {
        if(v.id == id) {
            v.marcado = false;
            return;
        }
    }
}

void DesmarcarGrafo() {
    for(auto& v : vertices) {
        v.marcado = false;
    }
}

bool MarcadoVertice(int id) {
    for(const auto& v : vertices) {
        if(v.id == id) return v.marcado;
    }
    return false;
}

bool MarcadoGrafo() {
    for(const auto& v : vertices) {
        if(!v.marcado) return false;
    }
    return true;
}

T InfoVertice(int id) {
    for(const auto& v : vertices) {
        if(v.id == id) return v.info;
    }
    throw std::runtime_error("Vertice no encontrado");
}

int idVertice(T info) {
    for(const auto& v : vertices) {
        if(v.info == info) return v.id;
    }
    return -1;
}

int OrdenGrafo() const {
    return numVertices;
}

int CostoArco(int origen, int destino) {
    for(const auto& arco : arcos) {
        if(arco.origen == origen && arco.destino == destino) {
            return arco.costo;
        }
    }
    throw std::runtime_error("Arco no encontrado");
}

std::list<int> sucesores(int id) {
    std::list<int> suc;
    for(const auto& arco : arcos) {
        if(arco.origen == id) {
            suc.push_back(arco.destino);
        }
    }
    return suc;
}
std::list<T> getvertices() {
    std::list<T> result;
    for(const auto& v : vertices) {
        result.push_back(v.info);
    }
    return result;
}
    

    void ruta_corta(int i1, int i2, const std::string& nombre_objeto, const std::list<Malla>& mallas) {
    // Buscar el objeto en la lista de mallas
    const Malla* objeto = nullptr;
    for (const auto& malla : mallas) {
        if (malla.getMesh_Name() == nombre_objeto) {
            objeto = &malla;
            break;
        }
    }

    // Verificar si el objeto existe
    if (!objeto) {
        std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
        return;
    }

    // Verificar si los índices son iguales
    if (i1 == i2) {
        std::cout << "(Índices iguales) Los indices de los vertices dados son iguales." << std::endl;
        return;
    }

    // Obtener la lista de vértices del objeto
    const std::list<Vertice>& vertices = objeto->getVertices();
    int numVertices = vertices.size();

    // Verificar si los índices están en rango
    if (i1 < 0 || i1 >= numVertices || i2 < 0 || i2 >= numVertices) {
        std::cout << " Algunos de los indices de vertices estan fuera de rango para el objeto " 
                  << nombre_objeto << "." << std::endl;
        return;
    }

    // Crear el grafo y agregar los vértices
    Grafo<Vertice> grafo;
    std::map<int, int> verticeToId; // Mapeo de índice original a ID en el grafo
    int idx = 0;
    for (const auto& vertice : vertices) {
        grafo.InsVertice(vertice);
        verticeToId[idx++] = grafo.idVertice(vertice);
    }

    // Agregar arcos entre todos los vértices con sus distancias
    idx = 0;
    for (auto it1 = vertices.begin(); it1 != vertices.end(); ++it1) {
        int idxInner = 0;
        for (auto it2 = vertices.begin(); it2 != vertices.end(); ++it2) {
            if (idx != idxInner) {
                float distancia = calcularDistanciaEuclidiana(*it1, *it2);
                grafo.InsArco(verticeToId[idx], verticeToId[idxInner], static_cast<int>(distancia * 1000)); // Convertir a entero multiplicando por 1000
            }
            idxInner++;
        }
        idx++;
    }

    // Implementar Dijkstra
    std::map<int, int> distancia;
    std::map<int, int> previo;
    std::set<int> noVisitados;

    // Inicializar
    for (const auto& v : grafo.getvertices()) {
        int id = grafo.idVertice(v);
        distancia[id] = std::numeric_limits<int>::max();
        noVisitados.insert(id);
    }

    distancia[verticeToId[i1]] = 0;

    // Algoritmo de Dijkstra
    while (!noVisitados.empty()) {
        // Encontrar el vértice con la menor distancia
        int u = *std::min_element(noVisitados.begin(), noVisitados.end(),
            [&distancia](int a, int b) { return distancia[a] < distancia[b]; });

        noVisitados.erase(u);

        // Si llegamos al destino, podemos terminar
        if (u == verticeToId[i2]) break;

        // Actualizar las distancias de los vecinos
        for (int v : grafo.sucesores(u)) {
            if (noVisitados.find(v) != noVisitados.end()) {
                int alt = distancia[u] + grafo.CostoArco(u, v);
                if (alt < distancia[v]) {
                    distancia[v] = alt;
                    previo[v] = u;
                }
            }
        }
    }

    // Reconstruir el camino
    std::list<int> camino;
    int actual = verticeToId[i2];
    while (actual != verticeToId[i1]) {
        camino.push_front(actual);
        if (previo.find(actual) == previo.end()) {
            std::cout << "No existe un camino entre los vertices dados." << std::endl;
            return;
        }
        actual = previo[actual];
    }
    camino.push_front(verticeToId[i1]);

    // Convertir IDs del grafo a índices originales y mostrar resultado
    std::cout << "La ruta más corta que conecta los vertices " << i1 
              << " y " << i2 << " del objeto " << nombre_objeto << " pasa por: ";

    bool first = true;
    for (int id : camino) {
        if (!first) std::cout << ",";
        // Encontrar el índice original
        for (const auto& pair : verticeToId) {
            if (pair.second == id) {
                std::cout << pair.first;
                break;
            }
        }
        first = false;
    }
    std::cout << "; con una longitud de " << distancia[verticeToId[i2]] / 1000.0 << "." << std::endl;
}


void ruta_corta_centro(int i1, const std::string& nombre_objeto, const std::list<Malla>& mallas) {
        // Buscar el objeto en la lista de mallas
        const Malla* objeto = nullptr;
        for (const auto& malla : mallas) {
            if (malla.getMesh_Name() == nombre_objeto) {
                objeto = &malla;
                break;
            }
        }
    
        // Verificar si el objeto existe
        if (!objeto) {
            std::cout << "El objeto " << nombre_objeto << " no ha sido cargado en memoria." << std::endl;
            return;
        }
    
        // Obtener la lista de vértices del objeto
        const std::list<Vertice>& vertices = objeto->getVertices();
        int numVertices = vertices.size();
    
        // Verificar si el índice está en rango
        if (i1 < 0 || i1 >= numVertices) {
            std::cout << "El indice de vertice esta fuera de rango para el objeto " 
                      << nombre_objeto << "." << std::endl;
            return;
        }
    
        // Calcular el centroide
        float sumX = 0, sumY = 0, sumZ = 0;
        for (const auto& vertice : vertices) {
            sumX += vertice.getXi();
            sumY += vertice.getYi();
            sumZ += vertice.getZi();
        }
        Vertice centro(sumX / numVertices, sumY / numVertices, sumZ / numVertices);
    
        // Crear el grafo y agregar los vértices
        Grafo<Vertice> grafo;
        std::map<int, int> verticeToId; // Mapeo de índice original a ID en el grafo
        int idx = 0;
        for (const auto& vertice : vertices) {
            grafo.InsVertice(vertice);
            verticeToId[idx++] = grafo.idVertice(vertice);
        }
        // Agregar el centro como último vértice
        grafo.InsVertice(centro);
        int centroId = grafo.idVertice(centro);
    
        // Agregar arcos entre todos los vértices con sus distancias
        idx = 0;
        for (auto it1 = vertices.begin(); it1 != vertices.end(); ++it1) {
            int idxInner = 0;
            for (auto it2 = vertices.begin(); it2 != vertices.end(); ++it2) {
                if (idx != idxInner) {
                    float distancia = calcularDistanciaEuclidiana(*it1, *it2);
                    grafo.InsArco(verticeToId[idx], verticeToId[idxInner], static_cast<int>(distancia * 1000));
                }
                idxInner++;
            }
            // Conectar con el centro
            float distanciaCentro = calcularDistanciaEuclidiana(*it1, centro);
            grafo.InsArco(verticeToId[idx], centroId, static_cast<int>(distanciaCentro * 1000));
            grafo.InsArco(centroId, verticeToId[idx], static_cast<int>(distanciaCentro * 1000));
            idx++;
        }
    
        // Implementar Dijkstra
        std::map<int, int> distancia;
        std::map<int, int> previo;
        std::set<int> noVisitados;
    
        // Inicializar
        for (const auto& v : grafo.getvertices()) {
            int id = grafo.idVertice(v);
            distancia[id] = std::numeric_limits<int>::max();
            noVisitados.insert(id);
        }
    
        distancia[verticeToId[i1]] = 0;
    
        // Algoritmo de Dijkstra
        while (!noVisitados.empty()) {
            // Encontrar el vértice con la menor distancia
            int u = *std::min_element(noVisitados.begin(), noVisitados.end(),
                [&distancia](int a, int b) { return distancia[a] < distancia[b]; });
    
            noVisitados.erase(u);
    
            // Si llegamos al centro, podemos terminar
            if (u == centroId) break;
    
            // Actualizar las distancias de los vecinos
            for (int v : grafo.sucesores(u)) {
                if (noVisitados.find(v) != noVisitados.end()) {
                    int alt = distancia[u] + grafo.CostoArco(u, v);
                    if (alt < distancia[v]) {
                        distancia[v] = alt;
                        previo[v] = u;
                    }
                }
            }
        }
    
        // Reconstruir el camino
        std::list<int> camino;
        int actual = centroId;
        while (actual != verticeToId[i1]) {
            camino.push_front(actual);
            if (previo.find(actual) == previo.end()) {
                std::cout << "No existe un camino entre el vertice y el centro." << std::endl;
                return;
            }
            actual = previo[actual];
        }
        camino.push_front(verticeToId[i1]);
    
        // Mostrar resultado
        std::cout << "La ruta más corta que conecta el vertice " << i1 
                  << " con el centro del objeto " << nombre_objeto << ", ubicado en ct (" 
                  << centro.getXi() << ", " << centro.getYi() << ", " << centro.getZi() 
                  << "), pasa por: ";
    
        bool first = true;
        for (int id : camino) {
            if (!first) std::cout << ",";
            if (id == centroId) {
                std::cout << "ct";
            } else {
                // Encontrar el índice original
                for (const auto& pair : verticeToId) {
                    if (pair.second == id) {
                        std::cout << pair.first;
                        break;
                    }
                }
            }
            first = false;
        }
        std::cout << "; con una longitud de " << distancia[centroId] / 1000.0 << "." << std::endl;
    }
        // Función auxiliar para calcular la distancia euclidiana entre dos vértices
    float calcularDistanciaEuclidiana(const Vertice& v1, const Vertice& v2) {
            float dx = v1.getXi() - v2.getXi();
            float dy = v1.getYi() - v2.getYi();
            float dz = v1.getZi() - v2.getZi();
            return sqrt(dx*dx + dy*dy + dz*dz);
    }
};

// Inicialización del contador de IDs estático
template <class T>
int Grafo<T>::nextId = 1;

#endif // GRAFO_H