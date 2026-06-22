#include "../../include/decoradores/ServicioPileta.hpp"
#include <utility>

ServicioPileta::ServicioPileta(std::unique_ptr<Alojamiento> alojamiento)
    : DecoradorAlojamiento(std::move(alojamiento)), costoServicio_(11000.0) {}

std::string ServicioPileta::obtenerDescripcion() const 
    {
        return DecoradorAlojamiento::obtenerDescripcion() + " + Acceso a Pelopincho 🏊‍♂️";
    }

double ServicioPileta::calcularPresupuesto() const 
    {
        return DecoradorAlojamiento::calcularPresupuesto() + costoServicio_;
    }