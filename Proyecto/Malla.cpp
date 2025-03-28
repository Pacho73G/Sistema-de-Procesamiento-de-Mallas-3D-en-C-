#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include "Vertice.h"
#include "Arista.h"
#include "Cara.h"
#include "Malla.h"

using namespace std;

/*Constructor por defecto*/
Malla::Malla(){}

/*Constructor con parametros*/
Malla::Malla(string mesh_name, int n):mesh_name(mesh_name),n(n){}

/*Destructor*/
Malla::~Malla(){}

/*Metodos de acceso*/  
string Malla::getMesh_Name() const{
  return mesh_name;
}

int Malla::getN() const{
  return n;
}

list<Vertice> Malla::getVertices()const { 
  return vertices;
}

list<Arista> Malla::getAristas() const{ 
  return aristas;
}

list<Cara> Malla::getCaras() const{ 
  return caras;
}

list<Malla> Malla::getObjetos() const{
  return objetos;
}

/*Metodos de modificacion*/
void Malla::setMesh_Name(string mesh_name){
  this->mesh_name=mesh_name;
}

void Malla::setN(int n){
  this->n=n;
}

void Malla::setVertices(list<Vertice> vertices){ // Cambiado de vector a list
  this->vertices=vertices;
}

void Malla::setAristas(list<Arista> aristas){ // Cambiado de vector a list
  this->aristas=aristas;
}

void Malla::setCaras(list<Cara> caras){ // Cambiado de vector a list
  this->caras=caras;
}

void Malla::setObjetos(list<Malla> objetos){ // Cambiado de vector a list
  this->objetos=objetos;
}

/********* Implementacion funciones *********/

void Malla::agregarVertice(const Vertice& vertice) {
    vertices.push_back(vertice);
}

void Malla::agregarObjeto(Malla nuevaMalla) {
    objetos.push_back(nuevaMalla);
}

void Malla::agregarCara(const Cara& cara) {
    caras.push_back(cara);
}

/*Funcion para cargar un archivo*/
bool Malla::cargar(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "El archivo " << nombreArchivo << " no existe o es ilegible" << endl;
        return false;
    }

    string nombreObjeto;
    int n;

    while (archivo >> nombreObjeto >> n) {
        if (nombreObjeto.empty() || n <= 0) {
            cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D válido" << endl;
            archivo.close();
            return false;
        }

        Malla nuevoObjeto(nombreObjeto, n);

        // Leer vértices
        list<Vertice> verticesObjeto;
        for (int i = 0; i < n; i++) {
            float xi, yi, zi;
            archivo >> xi >> yi >> zi;
            if (archivo.fail()) {
                cout << "El archivo " << nombreArchivo << " no contiene un objeto 3D valido." << endl;
                archivo.close();
                return false;
            }
            verticesObjeto.push_back(Vertice(xi, yi, zi));
        }
        nuevoObjeto.setVertices(verticesObjeto);

        // Leer caras
        while (true) {
            int numIndices;
            archivo >> numIndices;

            if (numIndices == -1) {
                break;
            }

            list<int> indices;
            for (int i = 0; i < numIndices; ++i) {
                int indice;
                archivo >> indice;
                indices.push_back(indice);
            }

            Cara cara(indices);
            nuevoObjeto.agregarCara(cara);
        }

        agregarObjeto(nuevoObjeto);
    }

    archivo.close();
    return true;
}



void Malla::descargar(string nombreObjeto) {
    // Iterador para la lista de objetos
    auto it = objetos.begin();
    bool encontrado = false;

    // Buscar el objeto en la lista de objetos
    while (it != objetos.end()) {
        if (it->getMesh_Name() == nombreObjeto) {
            it = objetos.erase(it);  // Eliminar el objeto y actualizar el iterador
            encontrado = true;
            cout << "El objeto " << nombreObjeto << " ha sido eliminado de la memoria de trabajo." << endl;
            break;
        } else {
            ++it;
        }
    }

    if (!encontrado) {
        cout << "(Objeto no existe) El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
    }
}

/*Funcion que se utiliza para el listado*/
int Malla::contarAristas() const {
    list<pair<int, int>> aristasUnicas;  // Para almacenar aristas únicas

    for (const Cara& cara : caras) {
        const list<int>& vertices = cara.getVertices();
        int anterior = -1;  // Variable para el vértice anterior

        // Iterar sobre los vértices de la cara
        for (int vertice : vertices) {
            if (anterior != -1) {
                // Crear un par de la arista
                int v1 = min(anterior, vertice);
                int v2 = max(anterior, vertice);
                pair<int, int> arista = make_pair(v1, v2);

                // Comprobar si la arista ya existe en aristasUnicas
                bool existe = false;
                for (const auto& a : aristasUnicas) {
                    if (a == arista) {
                        existe = true;
                        break;
                    }
                }

                // Si no existe, agregar la arista única
                if (!existe) {
                    aristasUnicas.push_back(arista);
                }
            }
            anterior = vertice;  // Actualizar el anterior
        }

        // Cerrar el ciclo para caras con más de 2 vértices
        if (vertices.size() > 2) {
            int v1 = min(anterior, vertices.front());
            int v2 = max(anterior, vertices.front());
            pair<int, int> arista = make_pair(v1, v2);

            // Comprobar si la arista ya existe en aristasUnicas
            bool existe = false;
            for (const auto& a : aristasUnicas) {
                if (a == arista) {
                    existe = true;
                    break;
                }
            }

            // Si no existe, agregar la arista única
            if (!existe) {
                aristasUnicas.push_back(arista);
            }
        }
    }

    // El tamaño de aristasUnicas será el total de aristas únicas
    return aristasUnicas.size();
}


/*Funcion para listar los objetos cargados*/
void Malla::listado() {
    cout << endl;

    // Verifica si hay objetos cargados
    if (objetos.empty()) {
        cout << "No hay objetos cargados en memoria" << endl;
        return;
    }

    // Itera sobre la lista de objetos y muestra su información
    for (const auto& obj : objetos) {
        cout << endl;

        // Usa los getters para acceder a los atributos privados
        cout << "Nombre del objeto: " << obj.getMesh_Name() << endl;
        cout << "Cantidad de vertices: " << obj.getN() << endl;
        cout << "Cantidad de aristas: " << obj.contarAristas() << endl; 
        cout << "Cantidad de caras: " << obj.getCaras().size() << endl; 
        cout << "------------------------------------ " << endl;
    }
}

/*Funcion para crear un envolvente*/
void Malla::envolvente(string nombreObjeto) {
  cout << endl;
    
    if(objetos.empty()){
        cout<<"No hay objetos cargados en memoria"<<endl;
        return;
    }

  // Verificar si el objeto está cargado
    Malla* objetoEncontrado = nullptr;
    for (auto& obj : objetos) {
        if (obj.getMesh_Name() == nombreObjeto) {
            objetoEncontrado = &obj;
            break;
        }
    }

    if (!objetoEncontrado) {
        cout << "El objeto " << nombreObjeto << " no ha sido cargado en memoria." << endl;
        return;
    }
    const list<Vertice>& verticesObjeto = objetoEncontrado->getVertices();
  // Inicializar los puntos mins y max con valores extremos
    auto it = verticesObjeto.begin();  // Usamos un iterador para acceder al primer elemento
    Vertice pmin = *it;
    Vertice pmax = *it;

  // Recorrer los vértices para encontrar los extremos
  for (auto vertice : verticesObjeto) {
      pmin.setXi(min(pmin.getXi(), vertice.getXi()));
      pmin.setYi(min(pmin.getYi(), vertice.getYi()));
      pmin.setZi(min(pmin.getZi(), vertice.getZi()));

      pmax.setXi(max(pmax.getXi(), vertice.getXi()));
      pmax.setYi(max(pmax.getYi(), vertice.getYi()));
      pmax.setZi(max(pmax.getZi(), vertice.getZi()));
  }

  // Crear los vértices de la caja envolvente
    list<Vertice> envolventeVertices = { // Cambiado a list
          Vertice(pmin.getXi(), pmin.getYi(), pmin.getZi()),
          Vertice(pmax.getXi(), pmin.getYi(), pmin.getZi()),
          Vertice(pmax.getXi(), pmax.getYi(), pmin.getZi()),
          Vertice(pmin.getXi(), pmax.getYi(), pmin.getZi()),
          Vertice(pmin.getXi(), pmin.getYi(), pmax.getZi()),
          Vertice(pmax.getXi(), pmin.getYi(), pmax.getZi()),
          Vertice(pmax.getXi(), pmax.getYi(), pmax.getZi()),
          Vertice(pmin.getXi(), pmax.getYi(), pmax.getZi())
      };

  // Crear el nombre del nuevo objeto (envolvente)
  string nombreEnvolvente = "env_" + nombreObjeto;
  Malla nuevaMalla(nombreEnvolvente, envolventeVertices.size());
  nuevaMalla.setVertices(envolventeVertices);
  agregarObjeto(nuevaMalla);

  cout << "La caja envolvente del objeto " << nombreObjeto << " ha sido generada con el nombre " << nombreEnvolvente << endl;
  cout << "Se ha agregado a los objetos en memoria." << endl;
}

/*Funcion para crear un envolvente global*/
void Malla::envolventeGlobal() {
    // Verificar si hay objetos en memoria
    if (objetos.empty()) {
        cout << "Ningun objeto ha sido cargado en memoria." << endl;
        return;
    }

    // Inicializar los puntos mins y max con el primer vértice del primer objeto
    auto primerObjeto = objetos.begin();
    if (primerObjeto->getVertices().empty()) {
        cout << "(Memoria vacía) Ningun objeto ha sido cargado en memoria." << endl;
        return;
    }

    Vertice pmin = primerObjeto->getVertices().front();
    Vertice pmax = primerObjeto->getVertices().front();

    // Recorrer todos los objetos y sus vértices
    for (const auto& objeto : objetos) {
        const list<Vertice>& verticesObjeto = objeto.getVertices();

        for (const auto& vertice : verticesObjeto) {
            // Actualizar mínimos
            pmin.setXi(min(pmin.getXi(), vertice.getXi()));
            pmin.setYi(min(pmin.getYi(), vertice.getYi()));
            pmin.setZi(min(pmin.getZi(), vertice.getZi()));

            // Actualizar máximos
            pmax.setXi(max(pmax.getXi(), vertice.getXi()));
            pmax.setYi(max(pmax.getYi(), vertice.getYi()));
            pmax.setZi(max(pmax.getZi(), vertice.getZi()));
        }
    }

    // Crear los vértices de la caja envolvente
    list<Vertice> envolventeVertices = {
        Vertice(pmin.getXi(), pmin.getYi(), pmin.getZi()),
        Vertice(pmax.getXi(), pmin.getYi(), pmin.getZi()),
        Vertice(pmax.getXi(), pmax.getYi(), pmin.getZi()),
        Vertice(pmin.getXi(), pmax.getYi(), pmin.getZi()),
        Vertice(pmin.getXi(), pmin.getYi(), pmax.getZi()),
        Vertice(pmax.getXi(), pmin.getYi(), pmax.getZi()),
        Vertice(pmax.getXi(), pmax.getYi(), pmax.getZi()),
        Vertice(pmin.getXi(), pmax.getYi(), pmax.getZi())
    };

    // Buscar si ya existe un env_global para actualizarlo
    for (auto& objeto : objetos) {
        if (objeto.getMesh_Name() == "env_global") {
            objeto.setVertices(envolventeVertices);
            cout << " La caja envolvente de los objetos en memoria se ha generado con el nombre env_global y se ha agregado a los objetos en memoria." << endl;
            return;
        }
    }

    // Si no existe, crear nuevo objeto envolvente
    string nombreEnvolvente = "env_global";
    Malla nuevaMalla(nombreEnvolvente, envolventeVertices.size());
    nuevaMalla.setVertices(envolventeVertices);
    agregarObjeto(nuevaMalla);


    cout << "La caja envolvente de todos los objetos en memoria se ha generado con el nombre " 
         << nombreEnvolvente << " y se ha agregado a los objetos en memoria." << endl;
}


/* Función para guardar un objeto */
void Malla::guardar(string nombreObjeto, string nombreArchivo) {
    // Verifica si el objeto principal esta cargado
    if (mesh_name == nombreObjeto) {
        ofstream archivo(nombreArchivo);
        if (!archivo) {
            cout << "Error al crear el archivo " << nombreArchivo << endl;
            return;
        }
        archivo << mesh_name << endl;
        archivo << vertices.size() << endl;

        // Escribe en el archivo las coordenadas de los vertices
        for (auto vertice : vertices) {
            archivo << vertice.getXi() << " " << vertice.getYi() << " " << vertice.getZi() << endl; 
        }

        // Escribe las caras del archivo
        for (auto cara : caras) {
            archivo << cara.getVertices().size();
            for (auto indice : cara.getVertices()) {
                archivo << " " << indice;
            }
            archivo << endl;
        }

        // Marca el final del archivo
        archivo << "-1" << endl;
        archivo.close();

        cout << "La información del objeto " << nombreObjeto << " ha sido guardada exitosamente en el archivo " << nombreArchivo << endl;
        return;
    }
    // Busca el objeto en la lista de objetos
    for (auto& objeto : objetos) {
        if (objeto.getMesh_Name() == nombreObjeto) {
            ofstream archivo(nombreArchivo);
            if (!archivo) {
                cout << "Error al crear el archivo " << nombreArchivo << endl;
                return;
            }
            archivo << objeto.getMesh_Name() << endl;
            archivo << objeto.getVertices().size() << endl;

            // Escribe en el archivo las coordenadas de los vertices
            for (auto vertice : objeto.getVertices()) {
                archivo << vertice.getXi() << " " << vertice.getYi() << " " << vertice.getZi() << endl; 
            }

            // Escribe las caras del archivo
            for (auto cara : objeto.getCaras()) {
                archivo << cara.getVertices().size();
                for (auto indice : cara.getVertices()) {
                    archivo << " " << indice;
                }
                archivo << endl;
            }

            // Marca el final del archivo
            archivo << "-1" << endl;
            archivo.close();

            cout << "La información del objeto " << nombreObjeto << " ha sido guardada exitosamente en el archivo " << nombreArchivo << endl;
            return;
        }
    }
    // Si el objeto no se encontró en ninguna parte
    cout << "El objeto " << nombreObjeto << " no está cargado en memoria" << endl;
}
