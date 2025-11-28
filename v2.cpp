#include <iostream>
#include <string>
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
// Limpia el buffer de entrada para evitar errores al leer datos
void limpiarEntrada() {
    cin.clear();                    // Limpia los flags de error
    cin.ignore(1000, '\n');         // Ignora hasta 1000 caracteres o hasta encontrar '\n'
}

void pausar() {
    cout << "\nPresiona ENTER para continuar...";
    cin.clear();
    while (cin.get() != '\n');  // Vacía cualquier basura
    cin.get();                  // Espera ENTER real del usuario
}

void limpiarPantalla() {
    system("cls");
}

// Función para crear un nuevo nodo con los datos proporcionados
// Retorna un puntero al nodo creado
Nodo* crearNodo(int id, string nombre) {
    Nodo* n = new Nodo;      // Reserva memoria dinámica para el nuevo nodo
    n->id = id;              // Asigna el ID
    n->nombre = nombre;      // Asigna el nombre
    n->izq = NULL;           // Inicializa hijo izquierdo como NULL (vacío)
    n->der = NULL;           // Inicializa hijo derecho como NULL (vacío)
    return n;                // Retorna el puntero al nuevo nodo
}

// Busca un nodo por su ID recorriendo TODO el árbol de forma recursiva
// Retorna un puntero al nodo si lo encuentra, NULL si no existe
Nodo* buscar(Nodo* raiz, int id) {
    if (raiz == NULL) return NULL;      // Caso base: árbol vacío o llegamos al final
    if (raiz->id == id) return raiz;    // Encontramos el nodo buscado
    
    // Buscar en el subárbol izquierdo
    Nodo* encontrado = buscar(raiz->izq, id);
    if (encontrado != NULL) return encontrado;  // Si lo encontramos, retornar
    
    // Si no está en el izquierdo, buscar en el subárbol derecho
    return buscar(raiz->der, id);
}

// Inserta un hijo en un nodo específico (padre) sin restricciones de árbol binario de búsqueda
// Puede reemplazar un hijo existente si ya hay uno en ese lado
bool insertarHijoManual(Nodo* raiz, int idPadre, Nodo* nuevoHijo, char lado) {
    // Buscar el nodo padre donde se insertará el hijo
    Nodo* padre = buscar(raiz, idPadre);
    if (padre == NULL) {
        cout << "? No existe un nodo con ID " << idPadre << "\n";
        return false;
    }

    // Insertar en el lado izquierdo
    if (lado == 'I' || lado == 'i') {
        if (padre->izq != NULL) {
            cout << "? Advertencia: Se reemplazará el hijo izquierdo.\n";
        }
        padre->izq = nuevoHijo;
        cout << "? Hijo izquierdo insertado correctamente.\n";
        return true;
    }
    // Insertar en el lado derecho
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

// Muestra los hijos (izquierdo y derecho) de un nodo específico
void mostrarHijos(Nodo* raiz, int id) {
    // Buscar el nodo del cual queremos ver los hijos
    Nodo* nodo = buscar(raiz, id);
    if (nodo == NULL) {
        cout << "? No existe un nodo con ese ID.\n";
        return;
    }
    
    // Mostrar información del nodo
    cout << "\nNodo " << id << " (" << nodo->nombre << "):\n";
    
    // Mostrar hijo izquierdo
    cout << "  Hijo izquierdo: ";
    if (nodo->izq != NULL)
        cout << nodo->izq->id << " (" << nodo->izq->nombre << ")\n";
    else
        cout << "VACÍO\n";

    // Mostrar hijo derecho
    cout << "  Hijo derecho: ";
    if (nodo->der != NULL)
        cout << nodo->der->id << " (" << nodo->der->nombre << ")\n";
    else
        cout << "VACÍO\n";
}

// Elimina todo el árbol liberando la memoria de forma recursiva (postorden)
void eliminarArbol(Nodo* raiz) {
    if (raiz == NULL) return;           // Caso base: nodo vacío
    eliminarArbol(raiz->izq);           // Eliminar subárbol izquierdo
    eliminarArbol(raiz->der);           // Eliminar subárbol derecho
    delete raiz;                        // Liberar memoria del nodo actual
}

// Elimina un nodo específico junto con todo su subárbol
// Retorna la nueva raíz (puede ser NULL si se eliminó todo)
Nodo* eliminarNodo(Nodo* raiz, int id) {
    if (raiz == NULL) return NULL;      // Caso base: árbol vacío
    
    // Si este es el nodo que queremos eliminar
    if (raiz->id == id) {
        eliminarArbol(raiz);            // Eliminar este nodo y todo su subárbol
        return NULL;                    // Retornar NULL porque ya no existe
    }
    
    // Buscar en los subárboles izquierdo y derecho
    raiz->izq = eliminarNodo(raiz->izq, id);
    raiz->der = eliminarNodo(raiz->der, id);
    
    return raiz;                        // Retornar la raíz actual
}

// Imprime el árbol de forma gráfica rotada 90° (el derecho arriba, izquierdo abajo)
void imprimirArbol(Nodo* raiz, int espacio = 0, string lado = "RAIZ") {
    if (raiz == NULL) return;           // Caso base: nodo vacío
    
    espacio += 8;                       // Incrementar espaciado para el siguiente nivel
    
    // Primero imprimir el subárbol derecho (aparecerá arriba)
    imprimirArbol(raiz->der, espacio, "DER");
    
    // Imprimir el nodo actual con la indentación correspondiente
    cout << "\n";
    for (int i = 8; i < espacio; i++)
        cout << " ";
    cout << "[" << lado << "] " << raiz->id << " (" << raiz->nombre << ")";
    
    // Luego imprimir el subárbol izquierdo (aparecerá abajo)
    imprimirArbol(raiz->izq, espacio, "IZQ");
}

///////////////////////////////////////////////////////
// RECORRIDOS DEL ÁRBOL (RECURSIVOS)
///////////////////////////////////////////////////////

// Recorrido PREORDEN: Raíz -> Izquierda -> Derecha
// Útil para copiar el árbol o generar expresiones con notación prefija
void preOrden(Nodo* raiz) {
    if (raiz == NULL) return;                           // Caso base
    cout << raiz->id << " (" << raiz->nombre << ")  ";  // Visitar raíz primero
    preOrden(raiz->izq);                                // Recorrer izquierda
    preOrden(raiz->der);                                // Recorrer derecha
}

// Recorrido INORDEN: Izquierda -> Raíz -> Derecha
// En árboles binarios de búsqueda, imprime los nodos en orden ascendente
void inOrden(Nodo* raiz) {
    if (raiz == NULL) return;                           // Caso base
    inOrden(raiz->izq);                                 // Recorrer izquierda primero
    cout << raiz->id << " (" << raiz->nombre << ")  ";  // Visitar raíz
    inOrden(raiz->der);                                 // Recorrer derecha
}

// Recorrido POSTORDEN: Izquierda -> Derecha -> Raíz
// Útil para eliminar el árbol o evaluar expresiones postfijas
void postOrden(Nodo* raiz) {
    if (raiz == NULL) return;                           // Caso base
    postOrden(raiz->izq);                               // Recorrer izquierda
    postOrden(raiz->der);                               // Recorrer derecha
    cout << raiz->id << " (" << raiz->nombre << ")  ";  // Visitar raíz al final
}

///////////////////////////////////////////////////////

// Inserta un nodo usando las reglas de un Árbol Binario de Búsqueda (ABB)
Nodo* insertarABB(Nodo* raiz, int id, string nombre) {
    if (raiz == NULL) {
        return crearNodo(id, nombre);   // Si el árbol está vacío, este se vuelve la nueva raíz
    }

    if (id < raiz->id) {
        raiz->izq = insertarABB(raiz->izq, id, nombre);   // Va a la izquierda
    }
    else if (id > raiz->id) {
        raiz->der = insertarABB(raiz->der, id, nombre);   // Va a la derecha
    }
    else {
        cout << "? El ID ya existe. No se puede insertar en un ABB.\n";
    }

    return raiz;
}

int main() {
	setlocale(LC_CTYPE, "Spanish");
    Nodo* raiz = NULL;      // Puntero a la raíz del árbol (inicialmente vacío)
    int opcion;             // Variable para almacenar la opción del menú
    
    do {
    	limpiarPantalla();
        // Mostrar el menú de opciones
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
        cout << "Seleccione una opción: ";
        
        cin >> opcion;              // Leer opción del usuario
        limpiarEntrada();           // Limpiar buffer

        // OPCIÓN 1: Crear la raíz del árbol
        if (opcion == 1) {
            if (raiz != NULL) {
                cout << "Ya existe una raíz.\n";
                continue;
            }
            int id;
            string nombre;
            cout << "ID: ";
            cin >> id;
            limpiarEntrada();
            cout << "Nombre: ";
            getline(cin, nombre);

            raiz = crearNodo(id, nombre);       // Crear el nodo raíz
            cout << "? Raíz creada.\n";
        }
        // OPCIÓN 2: Insertar un hijo en un nodo específico
        else if (opcion == 2) {
            if (!raiz) {
                cout << "? Primero cree la raíz.\n";
                continue;
            }

            int idPadre, idHijo;
            string nombre;
            char lado;

            cout << "ID del padre: ";
            cin >> idPadre;
            limpiarEntrada();

            // Verificar que el padre existe
            Nodo* padreEncontrado = buscar(raiz, idPadre);
            
            if (!padreEncontrado) {
                cout << "? No existe ese padre.\n";
                cout << "  (Asegúrate de que el ID " << idPadre << " existe en el árbol)\n";
                continue;
            }

            cout << "ID del nuevo hijo: ";
            cin >> idHijo;
            limpiarEntrada();

            // Verificar que el ID del hijo no existe ya en el árbol
            if (buscar(raiz, idHijo)) {
                cout << "? Ese ID ya existe.\n";
                continue;
            }

            cout << "Nombre hijo: ";
            getline(cin, nombre);

            cout << "Lado (I/D): ";
            cin >> lado;
            limpiarEntrada();

            // Insertar el nuevo hijo
            insertarHijoManual(raiz, idPadre, crearNodo(idHijo, nombre), lado);
        }
        // OPCIÓN 3: Ver los hijos de un nodo
        else if (opcion == 3) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                continue;
            }
            int id;
            cout << "ID: ";
            cin >> id;
            limpiarEntrada();
            mostrarHijos(raiz, id);
        }
        // OPCIÓN 4: Buscar un nodo por su ID
        else if (opcion == 4) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                continue;
            }
            int id;
            cout << "ID: ";
            cin >> id;
            limpiarEntrada();
            Nodo* b = buscar(raiz, id);
            if (b) cout << "? Encontrado: " << b->nombre << endl;
            else cout << "? No existe.\n";
        }
        // OPCIÓN 5: Eliminar un nodo y su subárbol
        else if (opcion == 5) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                continue;
            }
            int id;
            cout << "ID a eliminar: ";
            cin >> id;
            limpiarEntrada();
            
            // Verificar que el nodo existe
            if (!buscar(raiz, id)) {
                cout << "? No existe un nodo con ese ID.\n";
                continue;
            }
            
            // No permitir eliminar la raíz con esta opción
            if (id == raiz->id) {
                cout << "? No se puede eliminar la raíz. Use la opción 7 para limpiar todo.\n";
                continue;
            }
            
            raiz = eliminarNodo(raiz, id);
            cout << "? Nodo y su subárbol eliminados.\n";
        }
        // OPCIÓN 6: Mostrar el árbol completo gráficamente
        else if (opcion == 6) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                continue;
            }
            imprimirArbol(raiz);
            cout << "\n";
        }
        // OPCIÓN 7: Limpiar (eliminar) todo el árbol
        else if (opcion == 7) {
            if (!raiz) {
                cout << "? El árbol ya está vacío.\n";
                continue;
            }

            char c;
            cout << "¿Seguro? (S/N): ";
            cin >> c;
            limpiarEntrada();

            if (c == 'S' || c == 's') {
                eliminarArbol(raiz);        // Liberar toda la memoria
                raiz = NULL;                // Restablecer el puntero raíz
                cout << "? Árbol eliminado.\n";
            } else {
                cout << "Operación cancelada.\n";
            }
        }
        // OPCIÓN 8: Recorrido Preorden
        else if (opcion == 8) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                continue;
            }
            cout << "\n--- RECORRIDO PREORDEN ---\n";
            preOrden(raiz);
            cout << "\n";
        }
        // OPCIÓN 9: Recorrido Inorden
        else if (opcion == 9) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                continue;
            }
            cout << "\n--- RECORRIDO INORDEN ---\n";
            inOrden(raiz);
            cout << "\n";
        }
        // OPCIÓN 10: Recorrido Postorden
        else if (opcion == 10) {
            if (!raiz) {
                cout << "? El árbol está vacío.\n";
                continue;
            }
            cout << "\n--- RECORRIDO POSTORDEN ---\n";
            postOrden(raiz);
            cout << "\n";
        }
        
	    else if (opcion == 12) {
	    int id;
	    string nombre;
	
	    cout << "ID del nuevo miembro: ";
	    cin >> id;
	    limpiarEntrada();
	
	    // Verificar si el ID ya existe
	    if (buscar(raiz, id)) {
	        cout << "? Ese ID ya está en el árbol.\n";
	        continue;
	    }
	
	    cout << "Nombre: ";
	    getline(cin, nombre);
	
	    // Si el árbol estaba vacío, el primer nodo se vuelve la raíz automáticamente
	    raiz = insertarABB(raiz, id, nombre);
	
	    cout << "Nodo insertado siguiendo reglas de ABB.\n";
	}
	pausar();
    } while (opcion != 11);     // Repetir hasta que el usuario elija salir

    cout << "\n¡Hasta pronto!\n";
    return 0;
}
