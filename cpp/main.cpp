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