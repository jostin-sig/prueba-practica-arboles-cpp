#include <iostream>
#include <string>
#include <queue>
#include <iomanip>
#include <limits>
using namespace std;


//  ESTRUCTURA DEL NODO (Estudiante)

struct Estudiante {
    string cedula;
    string apellidos;
    string nombres;
    float  notaFinal;
    string carrera;
    int    nivel;
};

struct Nodo {
    Estudiante datos;
    Nodo* izquierda;
    Nodo* derecha;

    // Constructor
    Nodo(Estudiante e) : datos(e), izquierda(nullptr), derecha(nullptr) {}
};

//  CLASE ÁRBOL BINARIO DE BÚSQUEDA

class ArbolBST {
private:
    Nodo* raiz;


    // Insertar recursivamente (clave: cédula)
    Nodo* insertar(Nodo* nodo, Estudiante e) {
        if (nodo == nullptr)
            return new Nodo(e);

        if (e.cedula < nodo->datos.cedula)
            nodo->izquierda = insertar(nodo->izquierda, e);
        else if (e.cedula > nodo->datos.cedula)
            nodo->derecha = insertar(nodo->derecha, e);
        else
            cout << "   Ya existe un estudiante con cedula " << e.cedula << endl;

        return nodo;
    }

    // Buscar recursivamente
    Nodo* buscar(Nodo* nodo, const string& cedula) const {
        if (nodo == nullptr || nodo->datos.cedula == cedula)
            return nodo;

        if (cedula < nodo->datos.cedula)
            return buscar(nodo->izquierda, cedula);
        else
            return buscar(nodo->derecha, cedula);
    }

    // Encontrar el nodo con valor mínimo (usado en eliminación)
    Nodo* minNodo(Nodo* nodo) const {
        while (nodo->izquierda != nullptr)
            nodo = nodo->izquierda;
        return nodo;
    }

    // Eliminar recursivamente
    Nodo* eliminar(Nodo* nodo, const string& cedula) {
        if (nodo == nullptr) {
            cout << "  [!] Estudiante no encontrado." << endl;
            return nullptr;
        }

        if (cedula < nodo->datos.cedula) {
            nodo->izquierda = eliminar(nodo->izquierda, cedula);
        } else if (cedula > nodo->datos.cedula) {
            nodo->derecha = eliminar(nodo->derecha, cedula);
        } else {
            // Caso 1: hoja
            if (nodo->izquierda == nullptr && nodo->derecha == nullptr) {
                delete nodo;
                return nullptr;
            }
            // Caso 2: un hijo
            else if (nodo->izquierda == nullptr) {
                Nodo* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == nullptr) {
                Nodo* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }
            // Caso 3: dos hijos — reemplazar con sucesor inorden
            else {
                Nodo* sucesor = minNodo(nodo->derecha);
                nodo->datos = sucesor->datos;
                nodo->derecha = eliminar(nodo->derecha, sucesor->datos.cedula);
            }
        }
        return nodo;
    }