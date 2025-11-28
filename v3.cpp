#include <iostream>
#include <string>
#include <limits>
#include <fstream>
using namespace std;

// Estructura que representa cada nodo del árbol binario
struct Nodo {
    int id;           // Identificador único del nodo
    string nombre;    // Nombre o etiqueta del nodo
    Nodo* izq;        // Puntero al hijo izquierdo
    Nodo* der;        // Puntero al hijo derecho
};

// ---------------------
// Limpieza de buffer
// ---------------------
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para crear un nuevo nodo
Nodo* crearNodo(int id, string nombre) {
    Nodo* n = new Nodo;
    n->id = id;
    n->nombre = nombre;
    n->izq = NULL;
    n->der = NULL;
    return n;
}

// Busca un nodo por su ID de forma recursiva
Nodo* buscar(Nodo* raiz, int id) {
    if (raiz == NULL) return NULL;
    if (raiz->id == id) return raiz;
    
    Nodo* encontrado = buscar(raiz->izq, id);
    if (encontrado != NULL) return encontrado;
    
    return buscar(raiz->der, id);
}

// Inserta un hijo en un nodo específico
bool insertarHijoManual(Nodo* raiz, int idPadre, Nodo* nuevoHijo, char lado) {
    Nodo* padre = buscar(raiz, idPadre);
    if (padre == NULL) {
        cout << "? No existe un nodo con ID " << idPadre << "\n";
        return false;
    }

    if (lado == 'I' || lado == 'i') {
        if (padre->izq != NULL) {
            cout << "? Advertencia: Se reemplazará el hijo izquierdo.\n";
        }
        padre->izq = nuevoHijo;
        cout << "? Hijo izquierdo insertado correctamente.\n";
        return true;
    }
    else if (lado == 'D' || lado == 'd') {
        if (padre->der != NULL) {
            cout << "? Advertencia: Se reemplazará el hijo derecho.\n";
        }
        padre->der = nuevoHijo;
        cout << "? Hijo derecho insertado correctamente.\n";
        return true;
    }

    cout << "? Lado inválido.\n";
    return false;
}

// Muestra los hijos de un nodo
void mostrarHijos(Nodo* raiz, int id) {
    Nodo* nodo = buscar(raiz, id);
    if (nodo == NULL) {
        cout << "? No existe un nodo con ese ID.\n";
        return;
    }
    
    cout << "\nNodo " << id << " (" << nodo->nombre << "):\n";
    
    cout << "  Hijo izquierdo: ";
    if (nodo->izq != NULL)
        cout << nodo->izq->id << " (" << nodo->izq->nombre << ")\n";
    else
        cout << "VACÍO\n";

    cout << "  Hijo derecho: ";
    if (nodo->der != NULL)
        cout << nodo->der->id << " (" << nodo->der->nombre << ")\n";
    else
        cout << "VACÍO\n";
}

// Elimina todo el árbol
void eliminarArbol(Nodo* raiz) {
    if (raiz == NULL) return;
    eliminarArbol(raiz->izq);
    eliminarArbol(raiz->der);
    delete raiz;
}

// Elimina un nodo específico
Nodo* eliminarNodo(Nodo* raiz, int id) {
    if (raiz == NULL) return NULL;
    
    if (raiz->id == id) {
        eliminarArbol(raiz);
        return NULL;
    }
    
    raiz->izq = eliminarNodo(raiz->izq, id);
    raiz->der = eliminarNodo(raiz->der, id);
    
    return raiz;
}

// Imprime el árbol de forma gráfica
void imprimirArbol(Nodo* raiz, int espacio = 0, string lado = "RAIZ") {
    if (raiz == NULL) return;
    
    espacio += 8;
    imprimirArbol(raiz->der, espacio, "DER");
    
    cout << "\n";
    for (int i = 8; i < espacio; i++)
        cout << " ";
    cout << "[" << lado << "] " << raiz->id << " (" << raiz->nombre << ")";
    
    imprimirArbol(raiz->izq, espacio, "IZQ");
}

// Recorrido PREORDEN
void preOrden(Nodo* raiz) {
    if (raiz == NULL) return;
    cout << raiz->id << " (" << raiz->nombre << ")  ";
    preOrden(raiz->izq);
    preOrden(raiz->der);
}

// Recorrido INORDEN
void inOrden(Nodo* raiz) {
    if (raiz == NULL) return;
    inOrden(raiz->izq);
    cout << raiz->id << " (" << raiz->nombre << ")  ";
    inOrden(raiz->der);
}

// Recorrido POSTORDEN
void postOrden(Nodo* raiz) {
    if (raiz == NULL) return;
    postOrden(raiz->izq);
    postOrden(raiz->der);
    cout << raiz->id << " (" << raiz->nombre << ")  ";
}

// Inserta un nodo usando reglas de ABB
Nodo* insertarABB(Nodo* raiz, int id, string nombre) {
    if (raiz == NULL) {
        return crearNodo(id, nombre);
    }

    if (id < raiz->id) {
        raiz->izq = insertarABB(raiz->izq, id, nombre);
    }
    else if (id > raiz->id) {
        raiz->der = insertarABB(raiz->der, id, nombre);
    }
    else {
        cout << "? El ID ya existe. No se puede insertar en un ABB.\n";
    }

    return raiz;
}

// Genera un árbol genealógico ficticio de 10 personas
Nodo* generarArbolFicticio() {
    // Crear raíz (Abuelo paterno)
    Nodo* raiz = crearNodo(1, "Carlos (Abuelo)");
    
    // Nivel 1: Hijos del abuelo (Padres y tíos)
    raiz->izq = crearNodo(2, "María (Madre)");
    raiz->der = crearNodo(3, "Roberto (Tío)");
    
    // Nivel 2: Nietos (Hijos de María)
    raiz->izq->izq = crearNodo(4, "Ana (Hija)");
    raiz->izq->der = crearNodo(5, "Pedro (Hijo)");
    
    // Nivel 2: Nietos (Hijos de Roberto)
    raiz->der->izq = crearNodo(6, "Sofía (Prima)");
    raiz->der->der = crearNodo(7, "Luis (Primo)");
    
    // Nivel 3: Bisnietos (Hijos de Ana)
    raiz->izq->izq->izq = crearNodo(8, "Emma (Nieta)");
    raiz->izq->izq->der = crearNodo(9, "Lucas (Nieto)");
    
    // Nivel 3: Bisnieto (Hijo de Pedro)
    raiz->izq->der->izq = crearNodo(10, "Mía (Nieta)");
    
    return raiz;
}

// Guarda el árbol en un archivo de texto (recorrido preorden)
void guardarEnArchivo(Nodo* raiz, ofstream& archivo, int nivel = 0) {
    if (raiz == NULL) return;
    
    // Escribir indentación según el nivel
    for (int i = 0; i < nivel; i++) {
        archivo << "    ";
    }
    
    // Escribir información del nodo
    archivo << "ID: " << raiz->id << " - Nombre: " << raiz->nombre << endl;
    
    // Guardar subárboles
    if (raiz->izq != NULL) {
        for (int i = 0; i < nivel; i++) {
            archivo << "    ";
        }
        archivo << "  [Hijo Izquierdo]" << endl;
        guardarEnArchivo(raiz->izq, archivo, nivel + 1);
    }
    
    if (raiz->der != NULL) {
        for (int i = 0; i < nivel; i++) {
            archivo << "    ";
        }
        archivo << "  [Hijo Derecho]" << endl;
        guardarEnArchivo(raiz->der, archivo, nivel + 1);
    }
}

// Función principal para guardar en archivo
bool guardarArbolEnArchivo(Nodo* raiz, string nombreArchivo) {
    ofstream archivo(nombreArchivo.c_str());
    
    if (!archivo.is_open()) {
        return false;
    }
    
    archivo << "========================================" << endl;
    archivo << "       ÁRBOL GENEALÓGICO FAMILIAR       " << endl;
    archivo << "========================================" << endl << endl;
    
    if (raiz == NULL) {
        archivo << "El árbol está vacío." << endl;
    } else {
        archivo << "[RAÍZ]" << endl;
        guardarEnArchivo(raiz, archivo, 0);
    }
    
    archivo << endl << "========================================" << endl;
    archivo.close();
    return true;
}

int main() {
    setlocale(LC_CTYPE, "Spanish");
    Nodo* raiz = NULL;
    int opcion;
    
    do {
        limpiarPantalla();
        cout << "\n\n===== MENU DEL ÁRBOL BINARIO =====\n";
        cout << "1. Crear raíz\n";
        cout << "2. Insertar hijo manual\n";
        cout << "3. Ver hijos de un nodo\n";
        cout << "4. Buscar miembro\n";
        cout << "5. Eliminar miembro\n";
        cout << "6. Mostrar árbol\n";
        cout << "7. Limpiar árbol completo\n";
        cout << "8. Recorrido Preorden\n";
        cout << "9. Recorrido Inorden\n";
        cout << "10. Recorrido Postorden\n";
        cout << "11. Salir\n";
        cout << "12. Insertar nodo estilo ABB (automático)\n";
        cout << "13. Generar árbol genealógico ficticio (10 personas)\n";
        cout << "14. Guardar árbol en archivo TXT\n";
        cout << "Seleccione una opción: ";
        
        cin >> opcion;
        limpiarEntrada();

        if (opcion == 1) {
            if (raiz != NULL) {
                cout << "? Ya existe una raíz.\n";
                pausar();
                continue;
            }
            int id;
            string nombre;
            cout << "ID: ";
            if (!(cin >> id)) {
                cout << "? Error: Debe ingresar un número.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            cout << "Nombre: ";
            getline(cin, nombre);

            raiz = crearNodo(id, nombre);
            cout << "? Raíz creada.\n";
        }
        else if (opcion == 2) {
            if (!raiz) {
                cout << "? Primero cree la raíz.\n";
                pausar();
                continue;
            }

            int idPadre, idHijo;
            string nombre;
            char lado;

            cout << "ID del padre: ";
            if (!(cin >> idPadre)) {
                cout << "? Error: Debe ingresar un número.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();

            Nodo* padreEncontrado = buscar(raiz, idPadre);
            
            if (!padreEncontrado) {
                cout << "? No existe ese padre.\n";
                cout << "  (Asegúrate de que el ID " << idPadre << " existe en el árbol)\n";
                pausar();
                continue;
            }

            cout << "ID del nuevo hijo: ";
            if (!(cin >> idHijo)) {
                cout << "? Error: Debe ingresar un número.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();

            if (buscar(raiz, idHijo)) {
                cout << "? Ese ID ya existe.\n";
                pausar();
                continue;
            }

            cout << "Nombre hijo: ";
            getline(cin, nombre);

            cout << "Lado (I/D): ";
            cin >> lado;
            limpiarEntrada();

            insertarHijoManual(raiz, idPadre, crearNodo(idHijo, nombre), lado);
        }
        else if (opcion == 3) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                pausar();
                continue;
            }
            int id;
            cout << "ID: ";
            if (!(cin >> id)) {
                cout << "? Error: Debe ingresar un número.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            mostrarHijos(raiz, id);
        }
        else if (opcion == 4) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                pausar();
                continue;
            }
            int id;
            cout << "ID: ";
            if (!(cin >> id)) {
                cout << "? Error: Debe ingresar un número.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            Nodo* b = buscar(raiz, id);
            if (b) cout << "? Encontrado: " << b->nombre << endl;
            else cout << "? No existe.\n";
        }
        else if (opcion == 5) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                pausar();
                continue;
            }
            int id;
            cout << "ID a eliminar: ";
            if (!(cin >> id)) {
                cout << "? Error: Debe ingresar un número.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            
            if (!buscar(raiz, id)) {
                cout << "? No existe un nodo con ese ID.\n";
                pausar();
                continue;
            }
            
            if (id == raiz->id) {
                cout << "? No se puede eliminar la raíz. Use la opción 7 para limpiar todo.\n";
                pausar();
                continue;
            }
            
            raiz = eliminarNodo(raiz, id);
            cout << "? Nodo y su subárbol eliminados.\n";
        }
        else if (opcion == 6) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
            } else {
                cout << "\n===== ESTRUCTURA DEL ÁRBOL =====\n";
                imprimirArbol(raiz);
                cout << "\n================================\n";
            }
        }
        else if (opcion == 7) {
            if (!raiz) {
                cout << "? El árbol ya está vacío.\n";
                pausar();
                continue;
            }

            char c;
            cout << "¿Seguro? (S/N): ";
            cin >> c;
            limpiarEntrada();

            if (c == 'S' || c == 's') {
                eliminarArbol(raiz);
                raiz = NULL;
                cout << "? Árbol eliminado.\n";
            } else {
                cout << "Operación cancelada.\n";
            }
        }
        else if (opcion == 8) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
            } else {
                cout << "\n===== RECORRIDO PREORDEN =====\n";
                preOrden(raiz);
                cout << "\n==============================\n";
            }
        }
        else if (opcion == 9) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
            } else {
                cout << "\n===== RECORRIDO INORDEN =====\n";
                inOrden(raiz);
                cout << "\n=============================\n";
            }
        }
        else if (opcion == 10) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
            } else {
                cout << "\n===== RECORRIDO POSTORDEN =====\n";
                postOrden(raiz);
                cout << "\n===============================\n";
            }
        }
        else if (opcion == 12) {
            int id;
            string nombre;

            cout << "ID del nuevo miembro: ";
            if (!(cin >> id)) {
                cout << "? Error: Debe ingresar un número.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();

            if (buscar(raiz, id)) {
                cout << "? Ese ID ya está en el árbol.\n";
                pausar();
                continue;
            }

            cout << "Nombre: ";
            getline(cin, nombre);

            raiz = insertarABB(raiz, id, nombre);
            cout << "? Nodo insertado siguiendo reglas de ABB.\n";
        }
        else if (opcion == 13) {
            if (raiz != NULL) {
                char respuesta;
                cout << "? Ya existe un árbol. ¿Desea reemplazarlo? (S/N): ";
                cin >> respuesta;
                limpiarEntrada();
                
                if (respuesta == 'S' || respuesta == 's') {
                    eliminarArbol(raiz);
                    raiz = NULL;
                } else {
                    cout << "Operación cancelada.\n";
                    pausar();
                    continue;
                }
            }
            
            raiz = generarArbolFicticio();
            cout << "\n? Árbol genealógico ficticio generado exitosamente!\n";
            cout << "\nFamilia creada:\n";
            cout << "- 1 Abuelo (raíz)\n";
            cout << "- 2 Hijos del abuelo (madre y tío)\n";
            cout << "- 4 Nietos (2 hijos + 2 primos)\n";
            cout << "- 3 Bisnietos\n";
            cout << "\nTotal: 10 personas en 4 generaciones\n";
        }
        else if (opcion == 14) {
            if (!raiz) {
                cout << "? El árbol está vacío. No hay nada que guardar.\n";
                pausar();
                continue;
            }
            
            string nombreArchivo;
            cout << "Ingrese el nombre del archivo (sin extensión): ";
            getline(cin, nombreArchivo);
            nombreArchivo += ".txt";
            
            if (guardarArbolEnArchivo(raiz, nombreArchivo)) {
                cout << "\n? Árbol guardado exitosamente en: " << nombreArchivo << "\n";
            } else {
                cout << "\n? Error: No se pudo crear el archivo.\n";
            }
        }
        else if (opcion == 11) {
            cout << "\n¡Hasta pronto!\n";
        }
        else {
            cout << "? Opción inválida.\n";
        }
        
        if (opcion != 11) {
            pausar();
        }
        
    } while (opcion != 11);

    // Liberar memoria antes de salir
    if (raiz != NULL) {
        eliminarArbol(raiz);
    }

    return 0;
}
