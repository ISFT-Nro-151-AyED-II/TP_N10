#include "../../include/decoradores/ServicioDesayuno.hpp"
#include <utility>

// Se transfiere la propiedad del puntero hacia arriba en la jerarquía (a la clase base)
// y se inicializa el costo específico de este decorador en la misma lista.
ServicioDesayuno::ServicioDesayuno(std::unique_ptr<Alojamiento> alojamiento)
    : DecoradorAlojamiento(std::move(alojamiento)), costoServicio_(7500.0) {}

std::string ServicioDesayuno::obtenerDescripcion() const 
    {
        // Se concatena la descripción del servicio actual con la cadena acumulada 
        // que retorna la delegación al decorador base.
        return DecoradorAlojamiento::obtenerDescripcion() + " + Desayuno Continental ☕";
    }

double ServicioDesayuno::calcularPresupuesto() const 
    {
        // Se suma el costo intrínseco del decorador al costo acumulado que viene de la base.
        return DecoradorAlojamiento::calcularPresupuesto() + costoServicio_;
    }