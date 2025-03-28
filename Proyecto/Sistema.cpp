#include "Sistema.h"
#include <iostream>

bool Sistema::cargarMalla(const std::string& nombreArchivo) {
    return malla.cargar(nombreArchivo);
}

void Sistema::listarObjetos() {
    malla.listado();
}

void Sistema::generarEnvolvente(const std::string& nombreObjeto) {
    malla.envolvente(nombreObjeto);
}

void Sistema::generarEnvolventeGlobal() {
    malla.envolventeGlobal();
}

void Sistema::descargarObjeto(const std::string& nombreObjeto) {
    malla.descargar(nombreObjeto);
}

void Sistema::guardarObjeto(const std::string& nombreObjeto, const std::string& nombreArchivo) {
    malla.guardar(nombreObjeto, nombreArchivo);
}

void Sistema::verticeCercano(float px, float py, float pz, const std::string& nombreObjeto) {
    kdTree.vCercanoNombre(px, py, pz, nombreObjeto, malla.getObjetos());
}

void Sistema::verticeCercanoGlobal(float px, float py, float pz) {
    kdTree.vCercano(px, py, pz, malla.getObjetos());
}

void Sistema::verticesCercanosCaja(const std::string& nombreObjeto) {
    kdTree.v_cercanos_caja(nombreObjeto, malla.getObjetos());
}

void Sistema::rutaCorta(int idInicio, int idDestino, const std::string& nombreObjeto) {
    grafo.ruta_corta(idInicio, idDestino, nombreObjeto, malla.getObjetos());
}

void Sistema::rutaCortaCentro(int idInicio, const std::string& nombreObjeto) {
    grafo.ruta_corta_centro(idInicio, nombreObjeto,malla.getObjetos());
}