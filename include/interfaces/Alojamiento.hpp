#pragma once
#include <string>

// Interfaz base (Componente). Define el contrato estricto para la jerarquía.
class Alojamiento 
    {
        public:
        
            // Destructor virtual por defecto. Es mandatorio en clases base polimórficas para garantizar 
            // que la vtable delegue la destrucción a la clase derivada correcta y evitar fugas de memoria 
            // al usar punteros inteligentes en el cliente.
            virtual ~Alojamiento() = default;

            // Métodos virtuales puros. 
            // [[nodiscard]] fuerza a nivel compilador que el valor retornado sea utilizado.
            [[nodiscard]] virtual std::string obtenerDescripcion() const = 0;
            [[nodiscard]] virtual double calcularPresupuesto() const = 0;
    };