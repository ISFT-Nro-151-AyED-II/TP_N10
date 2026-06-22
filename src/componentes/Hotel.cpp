#include "../../include/componentes/Hotel.hpp"

// Se utiliza la lista de inicialización para optimizar la asignación de memoria 
// de los atributos intrínsecos desde el nacimiento del objeto.
Hotel::Hotel() 
    : costoBase_(50000.0), nombre_("Hotel Medio Pelo del Mar 🌟") {}

std::string Hotel::obtenerDescripcion() const 
    {
        // Retorna una copia directa de la cadena. Al ser const-correct, garantizamos seguridad absoluta 
        // contra efectos secundarios en el estado de la instancia.
        return nombre_;
    }

double Hotel::calcularPresupuesto() const 
    {
        // Punto de anclaje inicial de la recursión para el cálculo del presupuesto.
        return costoBase_;
    }