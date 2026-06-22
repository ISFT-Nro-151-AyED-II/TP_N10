#include "../../include/componentes/Hostel.hpp"

// El hostel representa la opción más económica de la escala base, demostrando 
// que el decorador puede trabajar sobre cualquier variante de alojamiento de forma uniforme.
Hostel::Hostel() 
    : costoBase_(25000.0), nombre_("Hostel Psico Bates 🎒") {}

std::string Hostel::obtenerDescripcion() const 
    {
        return nombre_;
    }

double Hostel::calcularPresupuesto() const 
    {
        return costoBase_;
    }