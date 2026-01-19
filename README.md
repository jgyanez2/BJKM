# BJKM
OYE BERNARDO, ES CON ESO DE PREORDEN?
#include <iostream>
using namespace std;

// Estructura del nodo
struct Nodo {
    int dato;
    Nodo* izquierdo;
    Nodo* derecho;
};

// Función para crear un nuevo nodo
Nodo* crearNodo(int valor) {
    Nodo* nuevo = new Nodo;
    nuevo->dato = valor;
    nuevo->izquierdo = NULL;
    nuevo->derecho = NULL;
    return nuevo;
}

// Función para construir el árbol manualmente
Nodo* crearArbol() {
    int valor;
    cout << "Ingrese el valor del nodo: ";
    cin >> valor;

    Nodo* raiz = crearNodo(valor);

    int hijos;
    cout << "¿Cuantos hijos tiene el nodo " << valor << "? (0, 1 o 2): ";
    cin >> hijos;

    if (hijos >= 1) {
        cout << "Creando hijo izquierdo de " << valor << endl;
        raiz->izquierdo = crearArbol();
    }

    if (hijos == 2) {
        cout << "Creando hijo derecho de " << valor << endl;
        raiz->derecho = crearArbol();
    }

    return raiz;
}

// Recorrido Preorden
void preorden(Nodo* raiz) {
    if (raiz != NULL) {
        cout << raiz->dato << " ";
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

int main() {
    cout << "Creacion del arbol:\n";
    Nodo* arbol = crearArbol();

    cout << "\nRecorrido Preorden del arbol:\n";
    preorden(arbol);

    return 0;
}
