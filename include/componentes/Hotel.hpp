#pragma once
#include <string>
#include "../interfaces/Alojamiento.hpp"

// Componente concreto. Representa la entidad base a la que luego se le apilarán decoradores.
class Hotel : public Alojamiento 
    {
        private:
        
            // Los datos intrínsecos del componente se mantienen privados para evitar corrupción de estado.
            double costoBase_;
            std::string nombre_;

        public:

            Hotel();
            
            // override garantiza en tiempo de compilación que estamos sobrescribiendo un método existente 
            // en la interfaz base. Si la firma en la base cambia, el compilador falla acá.
            ~Hotel() override = default;

            [[nodiscard]] std::string obtenerDescripcion() const override;
            [[nodiscard]] double calcularPresupuesto() const override;
    };