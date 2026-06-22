#pragma once
#include <string>
#include "../interfaces/Alojamiento.hpp"

class Apartamento : public Alojamiento 
    {
        private:

            double costoBase_;
            std::string nombre_;

        public:
        
            Apartamento();
            ~Apartamento() override = default;

            [[nodiscard]] std::string obtenerDescripcion() const override;
            [[nodiscard]] double calcularPresupuesto() const override;
    };