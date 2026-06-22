#pragma once
#include <string>
#include "../interfaces/Alojamiento.hpp"

class Hostel : public Alojamiento 
    {
        private:

            double costoBase_;
            std::string nombre_;

        public:
        
            Hostel();
            ~Hostel() override = default;

            [[nodiscard]] std::string obtenerDescripcion() const override;
            [[nodiscard]] double calcularPresupuesto() const override;
    };