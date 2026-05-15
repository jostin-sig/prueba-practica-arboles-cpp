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
    // Recorrido Inorden (Izq → Raíz → Der) — produce orden ascendente
    void inorden(Nodo* nodo) const {
        if (nodo == nullptr) return;
        inorden(nodo->izquierda);
        mostrarEstudiante(nodo->datos);
        inorden(nodo->derecha);
    }

    // Recorrido Preorden (Raíz → Izq → Der)
    void preorden(Nodo* nodo) const {
        if (nodo == nullptr) return;
        mostrarEstudiante(nodo->datos);
        preorden(nodo->izquierda);
        preorden(nodo->derecha);
    }

    // Recorrido Postorden (Izq → Der → Raíz)
    void postorden(Nodo* nodo) const {
        if (nodo == nullptr) return;
        postorden(nodo->izquierda);
        postorden(nodo->derecha);
        mostrarEstudiante(nodo->datos);
    }

    // Contar nodos recursivamente
    int contarNodos(Nodo* nodo) const {
        if (nodo == nullptr) return 0;
        return 1 + contarNodos(nodo->izquierda) + contarNodos(nodo->derecha);
    }

    // Calcular altura del árbol
    int calcularAltura(Nodo* nodo) const {
        if (nodo == nullptr) return 0;
        int altIzq = calcularAltura(nodo->izquierda);
        int altDer = calcularAltura(nodo->derecha);
        return 1 + max(altIzq, altDer);
    }

    // Buscar nota mayor (máxima)
    void buscarNotaMayor(Nodo* nodo, Nodo*& mejorNodo) const {
        if (nodo == nullptr) return;
        if (mejorNodo == nullptr || nodo->datos.notaFinal > mejorNodo->datos.notaFinal)
            mejorNodo = nodo;
        buscarNotaMayor(nodo->izquierda, mejorNodo);
        buscarNotaMayor(nodo->derecha, mejorNodo);
    }

    // Buscar nota menor (mínima)
    void buscarNotaMenor(Nodo* nodo, Nodo*& peorNodo) const {
        if (nodo == nullptr) return;
        if (peorNodo == nullptr || nodo->datos.notaFinal < peorNodo->datos.notaFinal)
            peorNodo = nodo;
        buscarNotaMenor(nodo->izquierda, peorNodo);
        buscarNotaMenor(nodo->derecha, peorNodo);
    }

    // Mostrar aprobados (nota >= 7)
    void mostrarAprobados(Nodo* nodo) const {
        if (nodo == nullptr) return;
        mostrarAprobados(nodo->izquierda);
        if (nodo->datos.notaFinal >= 7.0f)
            mostrarEstudiante(nodo->datos);
        mostrarAprobados(nodo->derecha);
    }

    // Mostrar reprobados (nota < 7)
    void mostrarReprobados(Nodo* nodo) const {
        if (nodo == nullptr) return;
        mostrarReprobados(nodo->izquierda);
        if (nodo->datos.notaFinal < 7.0f)
            mostrarEstudiante(nodo->datos);
        mostrarReprobados(nodo->derecha);
    }

    // Liberar memoria (destructor)
    void destruir(Nodo* nodo) {
        if (nodo == nullptr) return;
        destruir(nodo->izquierda);
        destruir(nodo->derecha);
        delete nodo;
    }

public:
    // Constructor
    ArbolBST() : raiz(nullptr) {}

    // Destructor
    ~ArbolBST() { destruir(raiz); }

    // ---- Verificar si el árbol está vacío ----
    bool estaVacio() const { return raiz == nullptr; }

    // ---- Inserción directa (para datos de prueba) ----
    void insertar(Estudiante e) {
        raiz = insertar(raiz, e);
    }
    };