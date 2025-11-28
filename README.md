##  📚 Sistema de Árbol Genealógico Familiar
Proyecto en C++ — Gestión completa de personas y relaciones familiares

Este proyecto implementa un sistema interactivo para gestionar un árbol genealógico familiar, utilizando estructuras dinámicas en C++.
Permite registrar personas, agregar hijos, consultar información, recorrer el árbol, generar árboles ficticios, eliminarlos y guardar el árbol en un archivo.

##  🚀 Características principales
✔ Gestión completa del árbol

Insertar raíces (primer ancestro) con ID manual.

Insertar hijos con validación completa.

Validación estricta de:

Edad (numérica y no negativa)

Género (Masculino / Femenino / Otro)

IDs ingresados por el usuario en raíces

Prevención de duplicados por ID.

## ✔ Consultas avanzadas

Buscar persona por ID.

Mostrar hijos de cualquier nodo.

Mostrar árbol completo con indentación jerárquica.

Estadísticas automáticas:

Cantidad total de personas

Promedio de edades

Género predominante

Número de generaciones

##  ✔ Recorridos clásicos

Preorden

Inorden

Postorden

##  ✔ Gestión de estructura

Eliminar persona por ID (junto con todos sus descendientes).

Eliminar árbol completo con confirmación.

Generar un árbol ficticio predefinido.

Guardar el árbol actual en un archivo .txt.

##  ✔ Validación robusta

Incluye validación en:

Menú principal

Submenús

Ingreso de datos

IDs

Opciones numéricas

##  📦 Estructura principal del proyecto
# struct Persona
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

##  📁 Estructura del Sistema
# Menú Principal
1. Insertar personas
2. Consultar información
3. Recorridos del árbol
4. Eliminar persona
5. Limpiar árbol completo
6. Generar árbol ficticio
7. Guardar árbol en archivo
8. Salir

# Submenú Insertar
1. Insertar raíz
2. Insertar hijo
3. Volver

# Submenú Consultar
1. Buscar persona por ID
2. Ver hijos de una persona
3. Mostrar árbol completo
4. Ver estadísticas del árbol
5. Volver

# Submenú Recorridos
1. Preorden
2. Inorden
3. Postorden
4. Volver
