#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>
using namespace std;

// Estructura que representa cada persona en el árbol genealógico
struct Persona {
    int id;                   // Identificador único de la persona
    string nombre;            // Nombre propio
    string apellido;          // Apellido
    int edad;                 // Edad de la persona
    string fechaNacimiento;   // Fecha de nacimiento
    string ocupacion;         // Ocupación o profesión
    string genero;            // Género (Masculino/Femenino)
    Persona* izq;             // Hijo izquierdo
    Persona* der;             // Hijo derecho
};

// ---------------------
// Utilidades
// ---------------------

// Limpia el estado de cin y descarta cualquier basura del buffer
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Pausa la ejecución hasta que el usuario presione ENTER
void pausar() {
    cout << "\n[Presiona ENTER para continuar]";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Limpia la pantalla dependiendo del sistema operativo
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");     // Windows
    #else
        system("clear");   // Linux / Mac
    #endif
}

// Imprime un encabezado con un formato decorativo
void mostrarEncabezado(string titulo) {
    cout << "\n+------------------------------------------------+\n";
    cout << "¦ " << setw(46) << left << titulo << " ¦\n";
    cout << "+------------------------------------------------+\n";
}

// ---------------------
// Funciones del Árbol
// ---------------------

// Crea una nueva persona en memoria dinámica y la retorna
Persona* crearPersona(int id, string nombre, string apellido, int edad, 
                      string fechaNac, string ocupacion, string genero) {
    Persona* p = new Persona;
    p->id = id;
    p->nombre = nombre;
    p->apellido = apellido;
    p->edad = edad;
    p->fechaNacimiento = fechaNac;
    p->ocupacion = ocupacion;
    p->genero = genero;
    p->izq = NULL;   // Inicialmente no tiene hijos
    p->der = NULL;
    return p;
}

// Busca a una persona por su ID mediante recorrido del árbol
Persona* buscar(Persona* raiz, int id) {
    if (raiz == NULL) return NULL;         // Árbol vacío o nodo inexistente
    if (raiz->id == id) return raiz;       // Nodo encontrado

    // Buscar recursivamente en el hijo izquierdo
    Persona* encontrado = buscar(raiz->izq, id);
    if (encontrado != NULL) return encontrado;

    // Si no se encontró en la izquierda, buscar en la derecha
    return buscar(raiz->der, id);
}

// Muestra todos los datos de una persona en formato de ficha
void mostrarPersonaDetalle(Persona* p) {
    cout << "\n+--------------- INFORMACIÓN PERSONAL ---------------+\n";
    cout << "¦ ID:                " << setw(30) << left << p->id << "¦\n";
    cout << "¦ Nombre Completo:   " << setw(30) << left << (p->nombre + " " + p->apellido) << "¦\n";
    cout << "¦ Edad:              " << setw(30) << left << p->edad << "¦\n";
    cout << "¦ Fecha Nacimiento:  " << setw(30) << left << p->fechaNacimiento << "¦\n";
    cout << "¦ Ocupación:         " << setw(30) << left << p->ocupacion << "¦\n";
    cout << "¦ Género:            " << setw(30) << left << p->genero << "¦\n";
    cout << "+----------------------------------------------------+\n";
}

// Inserta un hijo izquierdo o derecho según la letra indicada
bool insertarHijo(Persona* raiz, int idPadre, Persona* nuevoHijo, char lado) {
    // Buscar al padre en el árbol
    Persona* padre = buscar(raiz, idPadre);
    if (padre == NULL) {
        cout << " No existe una persona con ID " << idPadre << "\n";
        return false;
    }

    // Insertar como hijo izquierdo
    if (lado == 'I' || lado == 'i') {
        if (padre->izq != NULL) {
            cout << " Advertencia: Se reemplazará el hijo izquierdo existente.\n";
        }
        padre->izq = nuevoHijo;
        cout << " Hijo izquierdo agregado correctamente.\n";
        return true;
    }
    // Insertar como hijo derecho
    else if (lado == 'D' || lado == 'd') {
        if (padre->der != NULL) {
            cout << " Advertencia: Se reemplazará el hijo derecho existente.\n";
        }
        padre->der = nuevoHijo;
        cout << " Hijo derecho agregado correctamente.\n";
        return true;
    }

    // Si se ingresó una letra inválida
    cout << " Lado inválido. Use 'I' para izquierda o 'D' para derecha.\n";
    return false;
}

// Muestra los hijos izquierdo y derecho de una persona específica
void mostrarHijos(Persona* raiz, int id) {
    // Buscar a la persona por ID
    Persona* persona = buscar(raiz, id);
    if (persona == NULL) {
        cout << " No existe una persona con ese ID.\n";
        return;
    }
    
    // Mostrar los datos completos de la persona encontrada
    mostrarPersonaDetalle(persona);
    
    cout << "\n+------------------- HIJOS ----------------------+\n";
    
    // Mostrar hijo izquierdo si existe
    cout << "¦ Hijo Izquierdo:  ";
    if (persona->izq != NULL)
        cout << persona->izq->nombre << " " << persona->izq->apellido 
             << " (ID: " << persona->izq->id << ")" << endl;
    else
        cout << "NINGUNO" << endl;

    // Mostrar hijo derecho si existe
    cout << "¦ Hijo Derecho:    ";
    if (persona->der != NULL)
        cout << persona->der->nombre << " " << persona->der->apellido 
             << " (ID: " << persona->der->id << ")" << endl;
    else
        cout << "NINGUNO" << endl;

    cout << "+------------------------------------------------+\n";
}

// Libera toda la memoria del árbol en forma recursiva
void eliminarArbol(Persona* raiz) {
    if (raiz == NULL) return;
    
    // Primero elimina subárbol izquierdo
    eliminarArbol(raiz->izq);
    // Luego subárbol derecho
    eliminarArbol(raiz->der);
    // Finalmente elimina el nodo actual
    delete raiz;
}

// Elimina una persona específica del árbol junto con todos sus descendientes
Persona* eliminarPersona(Persona* raiz, int id) {
    if (raiz == NULL) return NULL;

    // Si se encuentra el nodo a eliminar
    if (raiz->id == id) {
        eliminarArbol(raiz);  // Elimina el subárbol completo
        return NULL;          // Retorna nulo para desconectar este nodo
    }
    
    // Continúa buscando recursivamente en los hijos
    raiz->izq = eliminarPersona(raiz->izq, id);
    raiz->der = eliminarPersona(raiz->der, id);
    
    return raiz; // Retorna el árbol actualizado
}

// Imprime el árbol gráficamente en forma horizontal
void imprimirArbol(Persona* raiz, int espacio = 0, string lado = "RAÍZ") {
    if (raiz == NULL) return;

    // Aumenta el espaciado entre niveles del árbol
    espacio += 10;

    // Primero imprime el lado derecho (se muestra arriba)
    imprimirArbol(raiz->der, espacio, "DER");
    
    // Imprime el nodo actual con indentación adecuada
    cout << "\n";
    for (int i = 10; i < espacio; i++)
        cout << " ";
    
    cout << "[" << lado << "] " << raiz->id << ": " << raiz->nombre 
         << " " << raiz->apellido << " (" << raiz->edad << " años)";
    
    // Luego imprime el lado izquierdo (abajo)
    imprimirArbol(raiz->izq, espacio, "IZQ");
}

// Recorrido en PRE-ORDEN: raíz ? izquierda ? derecha
void preOrden(Persona* raiz) {
    if (raiz == NULL) return;

    // Primero se muestra la raíz
    cout << "  • " << raiz->nombre << " " << raiz->apellido 
         << " (ID:" << raiz->id << ", " << raiz->edad << " años)\n";

    // Luego subárbol izquierdo
    preOrden(raiz->izq);
    // Después subárbol derecho
    preOrden(raiz->der);
}

// Recorrido IN-ORDEN: izquierda ? raíz ? derecha
void inOrden(Persona* raiz) {
    if (raiz == NULL) return;

    // Subárbol izquierdo
    inOrden(raiz->izq);

    // Imprime la raíz
    cout << "  • " << raiz->nombre << " " << raiz->apellido 
         << " (ID:" << raiz->id << ", " << raiz->edad << " años)\n";

    // Subárbol derecho
    inOrden(raiz->der);
}

// Recorrido POST-ORDEN: izquierda ? derecha ? raíz
void postOrden(Persona* raiz) {
    if (raiz == NULL) return;

    // Subárbol izquierdo
    postOrden(raiz->izq);
    // Subárbol derecho
    postOrden(raiz->der);

    // Finalmente se muestra la raíz
    cout << "  • " << raiz->nombre << " " << raiz->apellido 
         << " (ID:" << raiz->id << ", " << raiz->edad << " años)\n";
}

// Inserta una persona en un Árbol Binario de Búsqueda (ABB) según su ID
Persona* insertarABB(Persona* raiz, Persona* nueva) {
    // Si el árbol está vacío, la nueva persona se convierte en la raíz
    if (raiz == NULL) return nueva;

    // Si el ID es menor, insertar en el subárbol izquierdo
    if (nueva->id < raiz->id) {
        raiz->izq = insertarABB(raiz->izq, nueva);
    }
    // Si el ID es mayor, insertar en el subárbol derecho
    else if (nueva->id > raiz->id) {
        raiz->der = insertarABB(raiz->der, nueva);
    }
    // Si el ID ya existe, se descarta la inserción
    else {
        cout << " El ID ya existe en el árbol.\n";
        delete nueva; // Se elimina para evitar fugas de memoria
    }

    return raiz; // Se retorna la raíz actual del ABB
}

// Genera un árbol genealógico ficticio para pruebas
Persona* generarArbolFicticio() {
    // Crear raíz del árbol
    Persona* raiz = crearPersona(1, "Carlos", "González", 75, "15/03/1950", "Jubilado", "Masculino");
    
    // Hijos directos
    raiz->izq = crearPersona(2, "María", "González", 50, "22/07/1975", "Doctora", "Femenino");
    raiz->der = crearPersona(3, "Roberto", "González", 48, "10/11/1977", "Ingeniero", "Masculino");
    
    // Nietos por lado izquierdo
    raiz->izq->izq = crearPersona(4, "Ana", "Rodríguez", 28, "05/01/1997", "Abogada", "Femenino");
    raiz->izq->der = crearPersona(5, "Pedro", "Rodríguez", 25, "18/09/2000", "Estudiante", "Masculino");
    
    // Nietos por lado derecho
    raiz->der->izq = crearPersona(6, "Sofía", "González", 22, "30/04/2003", "Diseñadora", "Femenino");
    raiz->der->der = crearPersona(7, "Luis", "González", 20, "12/12/2005", "Estudiante", "Masculino");
    
    // Bisnietos
    raiz->izq->izq->izq = crearPersona(8, "Emma", "López", 5, "08/06/2020", "Preescolar", "Femenino");
    raiz->izq->izq->der = crearPersona(9, "Lucas", "López", 3, "20/02/2022", "Preescolar", "Masculino");
    
    raiz->izq->der->izq = crearPersona(10, "Mía", "Rodríguez", 2, "14/08/2023", "N/A", "Femenino");
    
    return raiz; // Retorna el árbol listo
}

// Guarda recursivamente la estructura del árbol en un archivo de texto
void guardarEnArchivo(Persona* raiz, ofstream& archivo, int nivel = 0) {
    if (raiz == NULL) return;

    // Índentación para mostrar estructura jerárquica
    for (int i = 0; i < nivel; i++) archivo << "    ";
    
    // Guardar información del nodo actual
    archivo << "+- ID: " << raiz->id << " | " << raiz->nombre << " " << raiz->apellido 
            << " | Edad: " << raiz->edad << " años | " << raiz->ocupacion << endl;
    
    // Si tiene hijo izquierdo, guardarlo recursivamente
    if (raiz->izq != NULL) {
        for (int i = 0; i < nivel; i++) archivo << "    ";
        archivo << "¦  [Hijo Izquierdo]" << endl;
        guardarEnArchivo(raiz->izq, archivo, nivel + 1);
    }
    
    // Si tiene hijo derecho, guardarlo recursivamente
    if (raiz->der != NULL) {
        for (int i = 0; i < nivel; i++) archivo << "    ";
        archivo << "¦  [Hijo Derecho]" << endl;
        guardarEnArchivo(raiz->der, archivo, nivel + 1);
    }
}

// Función que controla la escritura del árbol en archivo
bool guardarArbolEnArchivo(Persona* raiz, string nombreArchivo) {
    ofstream archivo(nombreArchivo.c_str());
    
    if (!archivo.is_open()) return false; // Error al abrir archivo
    
    archivo << "-------------------------------------------------------\n";
    archivo << "          ÁRBOL GENEALÓGICO FAMILIAR\n";
    archivo << "-------------------------------------------------------\n\n";
    
    if (raiz == NULL) {
        archivo << "El árbol está vacío.\n";
    } else {
        archivo << "[RAÍZ DEL ÁRBOL]\n";
        guardarEnArchivo(raiz, archivo, 0); // Guardado recursivo
    }
    
    archivo << "\n-------------------------------------------------------\n";
    archivo.close();
    return true; // Guardado exitoso
}

// Cuenta cuántos nodos existen en el árbol
int contarNodos(Persona* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

// Calcula la altura del árbol (profundidad máxima)
int calcularAltura(Persona* raiz) {
    if (raiz == NULL) return 0;

    int altIzq = calcularAltura(raiz->izq);
    int altDer = calcularAltura(raiz->der);

    return 1 + (altIzq > altDer ? altIzq : altDer);
}

// Muestra estadísticas generales del árbol
void mostrarEstadisticas(Persona* raiz) {
    if (raiz == NULL) {
        cout << " El árbol está vacío.\n";
        return;
    }
    
    mostrarEncabezado("ESTADÍSTICAS DEL ÁRBOL");

    cout << "  • Total de personas:      " << contarNodos(raiz) << endl;
    cout << "  • Altura del árbol:       " << calcularAltura(raiz) << " niveles" << endl;
    cout << "  • Generaciones:           " << calcularAltura(raiz) << endl;
    cout << "  • Raíz (Patriarca):       " << raiz->nombre << " " << raiz->apellido << endl;
}


// ------------------------------------------------------
// Entrada de Datos - Registro completo de una persona
// ------------------------------------------------------
Persona* ingresarPersonaCompleta(int id) {
    string nombre, apellido, fechaNac, ocupacion, genero;
    int edad;
    
    cout << "\n--- Datos de la nueva persona (ID: " << id << ") ---\n";
    
    // Solicitar nombre
    cout << "Nombre: ";
    getline(cin, nombre);
    
    // Solicitar apellido
    cout << "Apellido: ";
    getline(cin, apellido);
    
    // ----------------------------
    // Validación de Edad
    // ----------------------------
    cout << "Edad: ";
    while (!(cin >> edad) || edad < 0 || edad > 120) {
        cout << " Edad inválida. Ingrese un valor entre 0 y 120: ";
        limpiarEntrada();
    }
    limpiarEntrada(); // Limpiar buffer
    
    // Solicitar fecha de nacimiento
    cout << "Fecha de Nacimiento (DD/MM/AAAA): ";
    getline(cin, fechaNac);
    
    // Solicitar ocupación
    cout << "Ocupación: ";
    getline(cin, ocupacion);
    
    // ----------------------------
    // Validación de Género
    // ----------------------------
    cout << "Género (Masculino/Femenino): ";
    getline(cin, genero);

    // Validar entrada correcta del género
    while (genero != "Masculino" && genero != "Femenino" &&
           genero != "masculino" && genero != "femenino") 
    {
        cout << " Género inválido. Debe ser Masculino o Femenino: ";
        getline(cin, genero);
    }

    // Crear y devolver la persona
    return crearPersona(id, nombre, apellido, edad, fechaNac, ocupacion, genero);
}

// ------------------------------------------------------
// Submenú para insertar personas en el árbol genealógico
// ------------------------------------------------------
void submenuInsertar(Persona*& raiz) {
    int opcion;
    do {
        limpiarPantalla();
        mostrarEncabezado("SUBMENÚ - INSERTAR PERSONAS");

        // Opciones del submenú
        cout << "  1. Crear raíz (patriarca/matriarca)\n";
        cout << "  2. Agregar hijo manualmente\n";
        cout << "  3. Insertar usando árbol binario de búsqueda (ABB)\n";
        cout << "  4. Volver al menú principal\n";
        cout << "\nSeleccione una opción: ";
        
        // Validación de opción ingresada
        if (!(cin >> opcion)) {
            limpiarEntrada();
            continue;
        }
        limpiarEntrada();
        
        // ----------------------------
        // Opción 1: Crear raíz del árbol
        // ----------------------------
        if (opcion == 1) {
            if (raiz != NULL) {
                cout << " Ya existe una raíz en el árbol.\n";
                pausar();
                continue;
            }
            
            int idRaiz;

            cout << "ID de la raíz: ";
            if (!(cin >> idRaiz)) {
                cout << " ID inválido.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            
            // Validar que el ID sea positivo
            if (idRaiz <= 0) {
                cout << " El ID debe ser un número entero positivo.\n";
                pausar();
                continue;
            }
            
            // Registrar los datos completos de la persona raíz
            raiz = ingresarPersonaCompleta(idRaiz);
            cout << "\n Raíz del árbol creada exitosamente!\n";
        }

        // ----------------------------
        // Opción 2: Insertar hijo manualmente (izq/der)
        // ----------------------------
        else if (opcion == 2) {
            if (!raiz) {
                cout << " Primero debe crear la raíz del árbol.\n";
                pausar();
                continue;
            }
            
            int idPadre, idHijo;
            char lado;
            
            // Ingresar ID del padre
            cout << "ID del padre/madre: ";
            if (!(cin >> idPadre)) {
                cout << " ID inválido.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            
            // Verificar que exista en el árbol
            if (!buscar(raiz, idPadre)) {
                cout << " No existe una persona con ese ID.\n";
                pausar();
                continue;
            }
            
            // Ingresar ID del hijo
            cout << "ID del nuevo hijo: ";
            if (!(cin >> idHijo)) {
                cout << " ID inválido.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            
            // Validación de ID repetido
            if (buscar(raiz, idHijo)) {
                cout << " Ese ID ya existe en el árbol.\n";
                pausar();
                continue;
            }
            
            // Registrar datos completos del nuevo hijo
            Persona* nuevo = ingresarPersonaCompleta(idHijo);
            
            // Elegir si va a la izquierda o derecha
            cout << "\nPosición (I=Izquierda, D=Derecha): ";
            cin >> lado;
            limpiarEntrada();
            
            insertarHijo(raiz, idPadre, nuevo, lado);
        }

        // ----------------------------
        // Opción 3: Insertar usando ABB
        // ----------------------------
        else if (opcion == 3) {
            int id;

            // Ingresar ID del nuevo nodo
            cout << "ID de la nueva persona: ";
            if (!(cin >> id)) {
                cout << " ID inválido.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            
            // Verificar duplicados
            if (buscar(raiz, id)) {
                cout << " Ese ID ya existe.\n";
                pausar();
                continue;
            }
            
            // Ingresar datos completos de la persona
            Persona* nuevo = ingresarPersonaCompleta(id);

            // Insertar según reglas de árbol binario de búsqueda
            raiz = insertarABB(raiz, nuevo);

            cout << "\n Persona insertada usando reglas de ABB.\n";
        }
        
        // Pausa después de cada operación
        if (opcion >= 1 && opcion <= 3) pausar();
        
    } while (opcion != 4); // Volver al menú principal
}


// ------------------------------------------------------
// Submenú de Consultas
// ------------------------------------------------------
void submenuConsultar(Persona* raiz) {
    int opcion;
    do {
        limpiarPantalla();
        mostrarEncabezado("SUBMENÚ - CONSULTAR INFORMACIÓN");

        // Opciones de consulta
        cout << "  1. Buscar persona por ID\n";
        cout << "  2. Ver hijos de una persona\n";
        cout << "  3. Mostrar árbol completo\n";
        cout << "  4. Ver estadísticas del árbol\n";
        cout << "  5. Volver al menú principal\n";
        cout << "\nSeleccione una opción: ";
        
        // Validar entrada numérica
        if (!(cin >> opcion)) {
            limpiarEntrada();
            continue;
        }
        limpiarEntrada();
        
        // Validar que el árbol no esté vacío (excepto si quiere salir)
        if (raiz == NULL && opcion != 5) {
            cout << " El árbol está vacío.\n";
            pausar();
            continue;
        }
        
        // ----------------------------
        // Opción 1: Buscar persona por ID
        // ----------------------------
        if (opcion == 1) {
            int id;
            cout << "ID a buscar: ";
            if (!(cin >> id)) {
                cout << " ID inválido.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();

            // Buscar persona
            Persona* p = buscar(raiz, id);
            if (p) {
                mostrarPersonaDetalle(p);
            } else {
                cout << " No se encontró una persona con ese ID.\n";
            }
        }

        // ----------------------------
        // Opción 2: Ver hijos de una persona
        // ----------------------------
        else if (opcion == 2) {
            int id;
            cout << "ID de la persona: ";
            if (!(cin >> id)) {
                cout << " ID inválido.\n";
                limpiarEntrada();
                pausar();
                continue;
            }
            limpiarEntrada();
            
            // Mostrar hijos del nodo especificado
            mostrarHijos(raiz, id);
        }

        // ----------------------------
        // Opción 3: Mostrar el árbol completo
        // ----------------------------
        else if (opcion == 3) {
            mostrarEncabezado("ESTRUCTURA DEL ÁRBOL GENEALÓGICO");
            imprimirArbol(raiz);
            cout << "\n";
        }

        // ----------------------------
        // Opción 4: Ver estadísticas del árbol
        // ----------------------------
        else if (opcion == 4) {
            mostrarEstadisticas(raiz);
        }
        
        // Pausa tras cada operación
        if (opcion >= 1 && opcion <= 4) pausar();
        
    } while (opcion != 5); // Volver al menú principal
}

// ------------------------------------------------------
// Submenú de Recorridos del Árbol
// ------------------------------------------------------
void submenuRecorridos(Persona* raiz) {
    int opcion;
    do {
        limpiarPantalla();
        mostrarEncabezado("SUBMENÚ - RECORRIDOS DEL ÁRBOL");

        // Opciones de recorridos
        cout << "  1. Recorrido Preorden (Raíz-Izq-Der)\n";
        cout << "  2. Recorrido Inorden (Izq-Raíz-Der)\n";
        cout << "  3. Recorrido Postorden (Izq-Der-Raíz)\n";
        cout << "  4. Volver al menú principal\n";
        cout << "\nSeleccione una opción: ";
        
        // Validar entrada numérica
        if (!(cin >> opcion)) {
            limpiarEntrada();
            continue;
        }
        limpiarEntrada();
        
        // El árbol no debe estar vacío
        if (raiz == NULL && opcion != 4) {
            cout << " El árbol está vacío.\n";
            pausar();
            continue;
        }
        
        // ----------------------------
        // Opción 1: Recorrido Preorden
        // ----------------------------
        if (opcion == 1) {
            mostrarEncabezado("RECORRIDO PREORDEN");
            preOrden(raiz);
            cout << "\n";
        }

        // ----------------------------
        // Opción 2: Recorrido Inorden
        // ----------------------------
        else if (opcion == 2) {
            mostrarEncabezado("RECORRIDO INORDEN");
            inOrden(raiz);
            cout << "\n";
        }

        // ----------------------------
        // Opción 3: Recorrido Postorden
        // ----------------------------
        else if (opcion == 3) {
            mostrarEncabezado("RECORRIDO POSTORDEN");
            postOrden(raiz);
            cout << "\n";
        }
        
        // Pausa después de recorridos
        if (opcion >= 1 && opcion <= 3) pausar();
        
    } while (opcion != 4); // Volver al menú principal
}


// ------------------------------------------------------
// Menú Principal del Programa
// ------------------------------------------------------
int main() {
    setlocale(LC_CTYPE, "Spanish");  // Configurar idioma para caracteres especiales
    Persona* raiz = NULL;            // Puntero a la raíz del árbol genealógico
    int opcion;
    
    do {
        limpiarPantalla();
        
        // Encabezado del sistema
        cout << "\n+------------------------------------------------+\n";
        cout << "¦       SISTEMA DE ÁRBOL GENEALÓGICO FAMILIAR    ¦\n";
        cout << "+------------------------------------------------+\n\n";
        
        // Menú principal – opciones disponibles
        cout << "  +-------------------------------------+\n";
        cout << "  ¦  1. Insertar personas               ¦\n";
        cout << "  ¦  2. Consultar información           ¦\n";
        cout << "  ¦  3. Recorridos del árbol            ¦\n";
        cout << "  ¦  4. Eliminar persona                ¦\n";
        cout << "  ¦  5. Limpiar árbol completo          ¦\n";
        cout << "  ¦  6. Generar árbol ficticio          ¦\n";
        cout << "  ¦  7. Guardar árbol en archivo        ¦\n";
        cout << "  ¦  8. Salir                           ¦\n";
        cout << "  +-------------------------------------+\n";
        cout << "\n  Seleccione una opción: ";
        
        // Validar entrada numérica del menú
        if (!(cin >> opcion)) {
            limpiarEntrada();
            continue;
        }
        limpiarEntrada();
        
        switch (opcion) {

            // ---------------------------------
            // 1. Submenú para insertar personas
            // ---------------------------------
            case 1:
                submenuInsertar(raiz);
                break;
                
            // ---------------------------------
            // 2. Submenú para consultas
            // ---------------------------------
            case 2:
                submenuConsultar(raiz);
                break;
                
            // ---------------------------------
            // 3. Submenú de recorridos del árbol
            // ---------------------------------
            case 3:
                submenuRecorridos(raiz);
                break;
                
            // ---------------------------------
            // 4. Eliminar una persona específica
            // ---------------------------------
            case 4: {
                if (!raiz) {
                    cout << " El árbol está vacío.\n";
                    pausar();
                    break;
                }
                
                int id;
                cout << "ID de la persona a eliminar: ";
                
                // Validar ID
                if (!(cin >> id)) {
                    cout << " ID inválido.\n";
                    limpiarEntrada();
                    pausar();
                    break;
                }
                limpiarEntrada();
                
                // Comprobar que exista
                if (!buscar(raiz, id)) {
                    cout << " No existe una persona con ese ID.\n";
                    pausar();
                    break;
                }
                
                // No permitir eliminar la raíz desde este menú
                if (id == raiz->id) {
                    cout << " No se puede eliminar la raíz. Use opción 5.\n";
                    pausar();
                    break;
                }
                
                // Llamar a la función de eliminación
                raiz = eliminarPersona(raiz, id);
                cout << " Persona y sus descendientes eliminados.\n";
                pausar();
                break;
            }
                
            // ---------------------------------
            // 5. Eliminar todo el árbol completo
            // ---------------------------------
            case 5: {
                if (!raiz) {
                    cout << " El árbol ya está vacío.\n";
                    pausar();
                    break;
                }
                
                char conf;
                cout << " ¿Está seguro de eliminar TODO el árbol? (S/N): ";
                cin >> conf;
                limpiarEntrada();
                
                if (conf == 'S' || conf == 's') {
                    eliminarArbol(raiz);
                    raiz = NULL;
                    cout << " Árbol eliminado completamente.\n";
                } else {
                    cout << "Operación cancelada.\n";
                }
                pausar();
                break;
            }
                
            // ---------------------------------
            // 6. Generar automáticamente un árbol ficticio
            // ---------------------------------
            case 6: {
                // Verificar si ya existe un árbol
                if (raiz != NULL) {
                    char resp;
                    cout << " Ya existe un árbol. ¿Reemplazarlo? (S/N): ";
                    cin >> resp;
                    limpiarEntrada();
                    
                    if (resp == 'S' || resp == 's') {
                        eliminarArbol(raiz);
                        raiz = NULL;
                    } else {
                        cout << "Operación cancelada.\n";
                        pausar();
                        break;
                    }
                }
                
                // Crear árbol ficticio
                raiz = generarArbolFicticio();
                cout << "\n Árbol genealógico ficticio generado!\n";
                
                // Información del árbol creado
                cout << "\n  Familia González - 4 generaciones:\n";
                cout << "  • 1 Patriarca (Carlos - 75 años)\n";
                cout << "  • 2 Hijos adultos\n";
                cout << "  • 4 Nietos jóvenes\n";
                cout << "  • 3 Bisnietos pequeños\n";
                cout << "  ----------------------------\n";
                cout << "  Total: 10 personas\n";
                
                pausar();
                break;
            }
                
            // ---------------------------------
            // 7. Guardar árbol en archivo de texto
            // ---------------------------------
            case 7: {
                if (!raiz) {
                    cout << " El árbol está vacío. No hay datos para guardar.\n";
                    pausar();
                    break;
                }
                
                string nombreArch;
                cout << "Nombre del archivo (sin extensión): ";
                getline(cin, nombreArch);
                nombreArch += ".txt";  // Agregar extensión
                
                // Guardar datos del árbol
                if (guardarArbolEnArchivo(raiz, nombreArch)) {
                    cout << "\n Árbol guardado en: " << nombreArch << "\n";
                } else {
                    cout << "\n Error al crear el archivo.\n";
                }
                pausar();
                break;
            }
                
            // ---------------------------------
            // 8. Salir del sistema
            // ---------------------------------
            case 8:
                cout << "\n+------------------------------------------------+\n";
                cout << "¦     ¡Gracias por usar el sistema!             ¦\n";
                cout << "¦     Hasta pronto...                           ¦\n";
                cout << "+------------------------------------------------+\n\n";
                break;
                
            // ---------------------------------
            // Opción inválida
            // ---------------------------------
            default:
                cout << " Opción inválida. Intente nuevamente.\n";
                pausar();
        }
        
    } while (opcion != 8); // Repetir hasta elegir salir
    
    // Limpieza final de memoria
    if (raiz != NULL) {
        eliminarArbol(raiz);
    }
    
    return 0;
}

