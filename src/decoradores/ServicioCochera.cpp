#include "../../include/decoradores/ServicioCochera.hpp"
#include <utility>

ServicioCochera::ServicioCochera(std::unique_ptr<Alojamiento> alojamiento)
    : DecoradorAlojamiento(std::move(alojamiento)), costoServicio_(10000.0) {}

std::string ServicioCochera::obtenerDescripcion() const 
    {
        return DecoradorAlojamiento::obtenerDescripcion() + " + Cochera Casi Cubierta 🚗";
    }

double ServicioCochera::calcularPresupuesto() const 
    {
        return DecoradorAlojamiento::calcularPresupuesto() + costoServicio_;
    }