# 💻 Trabajo Práctico N°10: Unidad N°3 - Segunda Parte

**Instituto Superior de Formación Técnica Nº 151**   
**Carrera:** Tecnicatura Superior en Análisis de Sistemas  
**Materia:** Algoritmos y Estructuras de Datos II  
**Tema:** Patrones de Diseño Estructurales - Decorador (Decorator)    
**Alumno:** David Hernán Bravo  

---

## 💡 Enfoque Técnico y Arquitectura

### 📂 Estructura del Proyecto

```text
📂 D:\Repositorios de GitHub\ISFT N°151\Algoritmos y Estructuras de Datos II\Trabajos Prácticos\TP_N10\
├── 📁 diagramas\
│   ├── 📊 DiagramaClases.drawio
│   └── 📊 DiagramaSecuencia.drawio
├── 📁 include\
│   ├── 📁 interfaces\
│   │   └── 📘 Alojamiento.hpp               (Interfaz componente base)
│   ├── 📁 componentes\
│   │   ├── 📘 Hotel.hpp                     (Componente concreto)
│   │   ├── 📘 Apartamento.hpp               (Componente concreto)
│   │   └── 📘 Hostel.hpp                    (Componente concreto)
│   ├── 📁 decoradores\
│   │   ├── 📘 DecoradorAlojamiento.hpp      (Clase abstracta decoradora)
│   │   ├── 📘 ServicioDesayuno.hpp          (Decorador concreto)
│   │   ├── 📘 ServicioCochera.hpp           (Decorador concreto)
│   │   └── 📘 ServicioPileta.hpp            (Decorador concreto)
│   └── 📁 cliente\
│       └── 📘 Menu.hpp                      (Interfaz de usuario / Cliente)
├── 📁 src\
│   ├── 📁 componentes\
│   │   ├── 📙 Hotel.cpp                     (Implementación)
│   │   ├── 📙 Apartamento.cpp               (Implementación)
│   │   └── 📙 Hostel.cpp                    (Implementación)
│   ├── 📁 decoradores\
│   │   ├── 📙 DecoradorAlojamiento.cpp      (Implementación)
│   │   ├── 📙 ServicioDesayuno.cpp          (Implementación)
│   │   ├── 📙 ServicioCochera.cpp           (Implementación)
│   │   └── 📙 ServicioPileta.cpp            (Implementación)
│   └── 📁 cliente\
│       └── 📙 Menu.cpp                      (Implementación de la UI)
├── ⚙️ compilame.bat                         (Script de compilación CMD)
├── 🚀 main.cpp                              (Punto de entrada: solo llama a Menu)
└── 📖 README.md                             (Documentación y enfoque técnico)
```
Para la resolución de este sistema de presupuestos dinámicos, se aplicó el **Patrón Estructural Decorator**, priorizando un diseño fuertemente tipado y modular para cumplir con el Principio de Abierto/Cerrado (OCP). A continuación, el racional técnico detrás de las decisiones de arquitectura e implementación:

### 1. Gestión de Memoria, Ownership y Semántica de Movimiento

A diferencia de enfoques clásicos con punteros crudos (`*`), en este proyecto se impuso el uso exclusivo de punteros inteligentes (`std::unique_ptr<Alojamiento>`).

* **Decisión:** Se garantiza la propiedad exclusiva (*ownership*) del objeto en memoria. Para apilar decoradores, la propiedad se transfiere obligatoriamente mediante semántica de movimiento (`std::move`). Esto asegura que cada decorador sea el único dueño legal del objeto que envuelve (*zero-overhead abstraction*).
  
* **Seguridad y Destrucción en Cascada:** Al definir un destructor virtual por defecto en la interfaz base (`virtual ~Alojamiento() = default;`), cuando el cliente (`Menu`) descarta el puntero principal, se activa una reacción en cadena. El decorador más externo se destruye, lo que aniquila al puntero interno, destruyendo al siguiente decorador, hasta llegar al alojamiento base. Se garantiza cero fugas de memoria (*memory leaks*) sin escribir un solo `delete` manual.

### 2. Principios SOLID Aplicados

* **Open/Closed Principle (OCP):** Es el corazón de este TP. El sistema permite la adición infinita de nuevos servicios (ej. `ServicioSpa`, `ServicioTraslado`) o nuevos alojamientos (ej. `Cabaña`) creando nuevas clases concretas, sin alterar ni compilar de nuevo el código de las clases existentes.
  
* **Single Responsibility Principle (SRP):** Desacoplamiento total. El `Hotel` solo conoce su costo base. El `ServicioCochera` solo conoce su tarifa adicional. Ninguna clase centraliza la lógica matemática del presupuesto total.
  
* **Liskov Substitution Principle (LSP):** Cualquier decorador (ej. `ServicioPileta`) implementa la interfaz `Alojamiento`, por lo que el cliente puede tratar a un "Hotel con 3 servicios apilados" exactamente igual que a un "Hotel básico".

### 3. Delegación Recursiva (El núcleo del Decorador)

La abstracción principal ocurre en el método `calcularPresupuesto()` de `DecoradorAlojamiento`. Cuando el cliente solicita el total, el decorador actual suspende su cálculo y delega la ejecución al objeto que envuelve (`alojamientoEnvuelto_->calcularPresupuesto()`). Este burbujeo desciende hasta la clase base concreta, y luego retorna acumulando los costos matemáticamente en la pila de llamadas.

### 4. Complejidad Algorítmica

* **Tiempo:** $O(N)$, siendo $N$ la cantidad total de capas instanciadas (el componente base + la cantidad de decoradores apilados). El cálculo del presupuesto y la concatenación de la descripción requieren atravesar linealmente cada capa una única vez.
  
* **Espacio:** $O(N)$ en el Heap por la asignación dinámica de cada capa (cada decorador y el componente base ocupan su propio bloque de memoria). Adicionalmente, se requiere $O(N)$ en el Stack para mantener el marco de llamadas (Call Stack) durante la recursión polimórfica.

### 5. Atributos de C++ Moderno (C++17/20)

* **`[[nodiscard]]`:** Aplicado en las interfaces y en el retorno de las fábricas del `Menu` para forzar a nivel de compilador que el código cliente no ignore el puntero retornado, evitando la pérdida de la referencia en memoria.
  
* **`explicit`:** Utilizado en los constructores de los decoradores para prohibir conversiones de tipo implícitas por parte del compilador, asegurando un diseño estricto.
  
* **`std::make_unique`:** Se empleó para instanciar los objetos en el Heap de forma segura frente a excepciones (Exception Safety), evitando el uso directo del operador `new`.
  
* **`override` y `const`:** Garantizan la correctitud polimórfica en tiempo de compilación y aseguran que los métodos de consulta no muten el estado interno de los objetos (*Const-correctness*).

## 🖥️ Simulación de Ejecución (Consola)

El sistema integra `<windows.h>` y la asignación `SetConsoleOutputCP(CP_UTF8)` para el renderizado nativo de emojis y caracteres especiales, garantizando una UI limpia. Se incluye además saneamiento de búfer (`std::cin.clear()`, `std::cin.ignore()`) para mitigar inyecciones inválidas.

A continuación, una traza de ejecución demostrando robustez y delegación dinámica:

```text
D:\Repositorios de GitHub\ISFT N°151\Algoritmos y Estructuras de Datos II\Trabajos Prácticos\TP_N10>compilame
=======================================================
⚙️ Compilando el proyecto con g++ (Estandar C++20)...
=======================================================

✅ [EXITO] Compilacion terminada sin errores.
🚀 Iniciando PresupuestoAlojamiento.exe...


============================================
 🏨 SISTEMA DE PRESUPUESTOS DE ALOJAMIENTOS
============================================

📌 Seleccioná el tipo de alojamiento base:

1. Hotel Medio Pelo del Mar 🌟
2. Apartamento 1/2 ambiente 🏢
3. Hostel Psico Bates 🎒
4. Salir ❌

👉 Opción: a

⚠️ Error: Ingresá un número válido.

📌 Seleccioná el tipo de alojamiento base:

1. Hotel Medio Pelo del Mar 🌟
2. Apartamento 1/2 ambiente 🏢
3. Hostel Psico Bates 🎒
4. Salir ❌

👉 Opción: 2

➕ ¿Qué servicios adicionales querés sumar al presupuesto?

1. Desayuno Continental ☕
2. Cochera Casi Cubierta 🚗
3. Acceso a Pelopincho Climatizada 🏊‍♂️
4. Terminar y Calcular Presupuesto Total 📈

👉 Opción: 7

❌ Opción incorrecta. Intentá de nuevo.

➕ ¿Qué servicios adicionales querés sumar al presupuesto?

1. Desayuno Continental ☕
2. Cochera Casi Cubierta 🚗
3. Acceso a Pelopincho Climatizada 🏊‍♂️
4. Terminar y Calcular Presupuesto Total 📈

👉 Opción: 1

✅ Desayuno agregado.

➕ ¿Qué servicios adicionales querés sumar al presupuesto?

1. Desayuno Continental ☕
2. Cochera Casi Cubierta 🚗
3. Acceso a Pelopincho Climatizada 🏊‍♂️
4. Terminar y Calcular Presupuesto Total 📈

👉 Opción: 2

✅ Cochera agregada.

➕ ¿Qué servicios adicionales querés sumar al presupuesto?

1. Desayuno Continental ☕
2. Cochera Casi Cubierta 🚗
3. Acceso a Pelopincho Climatizada 🏊‍♂️
4. Terminar y Calcular Presupuesto Total 📈

👉 Opción: 3

✅ Acceso a pileta agregado.

➕ ¿Qué servicios adicionales querés sumar al presupuesto?

1. Desayuno Continental ☕
2. Cochera Casi Cubierta 🚗
3. Acceso a Pelopincho Climatizada 🏊‍♂️
4. Terminar y Calcular Presupuesto Total 📈

👉 Opción: 4


 🧾 DETALLE DEL PRESUPUESTO FINAL
===================================

📝 Detalle: Apartamento 1/2 ambiente 🏢 + Desayuno Continental ☕ + Cochera Casi Cubierta 🚗 + Acceso a Pelopincho 🏊‍♂️
💰 Total Estimado: $63500

=============================================
 ✨ Gracias por utilizar nuestro sistema ✨
=============================================

Presione una tecla para continuar . . .
```