#pragma once
#include <memory>
#include <string>
#include "DecoradorAlojamiento.hpp"

// Decorador concreto que añade el costo y la descripción del servicio de desayuno.
class ServicioDesayuno : public DecoradorAlojamiento 
    {
        private:

            double costoServicio_;

        public:
        
            explicit ServicioDesayuno(std::unique_ptr<Alojamiento> alojamiento);
            ~ServicioDesayuno() override = default;

            // Sobrescritura obligatoria para inyectar el comportamiento específico del servicio.
            [[nodiscard]] std::string obtenerDescripcion() const override;
            [[nodiscard]] double calcularPresupuesto() const override;
    };