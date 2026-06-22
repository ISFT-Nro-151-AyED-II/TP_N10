#pragma once
#include <memory>
#include <string>
#include "../interfaces/Alojamiento.hpp"

// Clase decoradora base. Actúa como intermediaria en la jerarquía.
// Implementa la interfaz Alojamiento y, a su vez, mantiene una relación de agregación
// con un componente del mismo tipo para poder delegar el comportamiento.
class DecoradorAlojamiento : public Alojamiento 
    {
        protected:

            // Se utiliza std::unique_ptr para asegurar la transferencia de propiedad exclusiva.
            // Al destruir el decorador en cascada, la memoria del objeto envuelto se libera sola.
            std::unique_ptr<Alojamiento> alojamientoEnvuelto_;

        public:
        
            // explicit evita que el compilador realice conversiones de tipo implícitas 
            // al pasar un unique_ptr, forzando un diseño de código más seguro y predecible.
            explicit DecoradorAlojamiento(std::unique_ptr<Alojamiento> alojamiento);
            
            ~DecoradorAlojamiento() override = default;

            // Se declaran como virtuales para que los decoradores concretos puedan 
            // extender la funcionalidad base al sobrescribirlos.
            [[nodiscard]] std::string obtenerDescripcion() const override;
            [[nodiscard]] double calcularPresupuesto() const override;
    };