#pragma once
#include <memory>
#include <string>
#include "DecoradorAlojamiento.hpp"

// Decorador concreto para el servicio de cochera.
class ServicioCochera : public DecoradorAlojamiento 
    {
        private:

            double costoServicio_;

        public:
        
            explicit ServicioCochera(std::unique_ptr<Alojamiento> alojamiento);
            ~ServicioCochera() override = default;

            [[nodiscard]] std::string obtenerDescripcion() const override;
            [[nodiscard]] double calcularPresupuesto() const override;
    };