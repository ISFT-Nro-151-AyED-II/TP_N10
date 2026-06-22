#pragma once
#include <memory>
#include <string>
#include "DecoradorAlojamiento.hpp"

// Decorador concreto para el servicio de acceso a la pileta.
class ServicioPileta : public DecoradorAlojamiento 
    {
        private:

            double costoServicio_;

        public:
        
            explicit ServicioPileta(std::unique_ptr<Alojamiento> alojamiento);
            ~ServicioPileta() override = default;

            [[nodiscard]] std::string obtenerDescripcion() const override;
            [[nodiscard]] double calcularPresupuesto() const override;
    };