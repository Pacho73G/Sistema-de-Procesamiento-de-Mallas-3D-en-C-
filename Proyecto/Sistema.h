#include "Malla.h"
#include "KdTree.h"
#include "Grafo.h"
#include <string>


class Sistema {
private:
    Malla malla;
    KdTree kdTree;
    Grafo<Vertice> grafo;

public:
    Sistema() = default;

    bool cargarMalla(const std::string& nombreArchivo);
    void listarObjetos();
    void generarEnvolvente(const std::string& nombreObjeto);
    void generarEnvolventeGlobal();
    void descargarObjeto(const std::string& nombreObjeto);
    void guardarObjeto(const std::string& nombreObjeto, const std::string& nombreArchivo);
    void verticeCercano(float px, float py, float pz, const std::string& nombreObjeto);
    void verticeCercanoGlobal(float px, float py, float pz);
    void verticesCercanosCaja(const std::string& nombreObjeto);
    void rutaCorta(int idInicio, int idDestino, const std::string& nombreObjeto);
    void rutaCortaCentro(int idInicio, const std::string& nombreObjeto);
};
