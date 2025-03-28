#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Sistema.h"

using namespace std;

/********* Firma funciones del sistema *********/

/*Funciones de interaccion con el sistema*/
void mostrarAyuda();
bool esComandoValido(string comando);

int main() {
    /*Variables*/
    string comando, input;
    string nombreArchivo, nombreObjeto;
    string px, py, pz,i1, i2;
    Sistema sistema;

    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tBienvenido al programa" << endl;
    cout << "\t\t\t\t\t\t\tManipulaciones sencillas sobre archivos que" << endl;
    cout << "\t\t\t\t\t\trepresentan objetos 3D a partir de mallas poligonales" << endl;
    mostrarAyuda();

    while (true) {

        /********
        Entrega 0: Indicador de linea del comando
        ********/
        cout << "$ ";
        getline(cin, input);

        /*Recibe la entrada para el comando*/
        stringstream ss(input);
        ss >> comando;

        /********
        Entrega 1: Organizacion de la informacion
        ********/

        if (comando == "cargar") {
            ss >> nombreArchivo;
            cout << endl;
            bool exitoCargar = sistema.cargarMalla(nombreArchivo);

            if (exitoCargar) {
                cout << "El archivo fue cargado exitosamente" << endl;
            } else {
                cout << "No se pudo cargar el archivo" << endl;
            }

            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "listado") {
            sistema.listarObjetos();
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "envolvente") {
            ss >> nombreObjeto;
            sistema.generarEnvolvente(nombreObjeto);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "envolvente_global") {
            sistema.generarEnvolventeGlobal();
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "descargar") {
            ss >> nombreObjeto;
            cout << endl;
            sistema.descargarObjeto(nombreObjeto);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "guardar") {
            ss >> nombreObjeto;
            ss >> nombreArchivo;
            cout << endl;
            sistema.guardarObjeto(nombreObjeto, nombreArchivo);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        /********
        Entrega 2: Vertices más cercanos
        ********/

        if (comando == "v_cercano") {
            ss >> px >> py >> pz >> nombreObjeto;
            sistema.verticeCercano(stof(px), stof(py), stof(pz), nombreObjeto);
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "v_cercano_global") {
            ss >> px >> py >> pz;
            sistema.verticeCercanoGlobal(stof(px), stof(py), stof(pz));
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "v_cercanos_caja") {
            ss >> nombreObjeto;
            cout << endl;
            sistema.verticesCercanosCaja(nombreObjeto);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        /*********
        Entrega 3: Ruta corta
        **********/
        if(comando=="ruta_corta"){
            ss >> i1 >> i2 >> nombreObjeto;
            sistema.rutaCorta(stof(i1), stof(i2), nombreObjeto);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }
        if(comando=="ruta_corta_centro"){
            ss >> i1 >> nombreObjeto;
            sistema.rutaCortaCentro(stof(i1), nombreObjeto);
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
        }

        if (comando == "salir") {
            cout << "Saliendo del programa..." << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << endl;
            break;
        }

        if (comando == "ayuda") {
            mostrarAyuda();
        }

        /*Verifica si el comando ingresado es valido o no*/
        if (!esComandoValido(comando)) {
            cout << "El comando ingresado no es valido " << endl;
            cout << "Ingrese 'ayuda' para ver la lista de los comandos " << endl;
            cout << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            continue;
        }
    }
}

/*Funcion para mostrar la ayuda*/
void mostrarAyuda() {
    cout << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Comandos disponibles:" << endl;
    cout << "\tcargar nombre_archivo                    - Cargar un archivo de malla" << endl;
    cout << "\tlistado                                  - Listar objetos en memoria" << endl;
    cout << "\tenvolvente nombre_objeto                 - Generar caja envolvente de un objeto" << endl;
    cout << "\tenvolvente_global                        - Generar caja envolvente de todos los objetos" << endl;
    cout << "\tdescargar nombre_objeto                  - Eliminar un objeto de la memoria" << endl;
    cout << "\tguardar nombre_objeto nombre_archivo     - Guardar un objeto en un archivo" << endl;
    cout << "\tv_cercano px py pz nombre_objeto         - Indica el vertice mas cercano de un objeto" << endl;
    cout << "\tv_cercano_global px py pz                - Indica el vertice mas cercano de todos los objetos" << endl;
    cout << "\tv_cercanos_caja nombre_objeto            - Indica los vertices mas cercanos a las esquinas de la caja" << endl;
    cout << "\truta_corta i1 i2 nombre_objeto           - Indica la ruta mas cercana que conecta dos vertices" << endl;
    cout << "\truta_corta_centro i1 nombre_objeto       - Indica la ruta mas corta que conecta el vertive i1 con el centro" << endl;
    cout << "\tsalir                                    - Terminar la ejecución del programa" << endl;
    cout << "------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
}

/*Funcion para verificar si el comando ingresado es valido*/
bool esComandoValido(string comando) {
    return comando == "cargar" || comando == "listado" || comando == "envolvente" ||
           comando == "envolvente_global" || comando == "descargar" || comando == "guardar" ||
           comando == "ayuda" || comando == "salir" || comando == "v_cercano" || comando == "v_cercanos_caja";
}
