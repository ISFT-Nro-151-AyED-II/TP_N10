#include "../../include/decoradores/DecoradorAlojamiento.hpp"
#include <utility> // Necesario para std::move

// El constructor recibe la propiedad exclusiva del alojamiento y la mueve al 
// atributo protegido. std::move evita copias profundas y transfiere el control 
// de memoria directamente al decorador base.
DecoradorAlojamiento::DecoradorAlojamiento(std::unique_ptr<Alojamiento> alojamiento)
    : alojamientoEnvuelto_(std::move(alojamiento)) {}

std::string DecoradorAlojamiento::obtenerDescripcion() const 
    {
        // Delega la ejecución al objeto envuelto. Si hay múltiples decoradores apilados,
        // esto dispara una reacción en cadena hasta llegar al componente concreto base.
        return alojamientoEnvuelto_->obtenerDescripcion();
    }

double DecoradorAlojamiento::calcularPresupuesto() const 
    {
        // Burbujeo recursivo del cálculo del presupuesto.
        return alojamientoEnvuelto_->calcularPresupuesto();
    }