#include "../../include/componentes/Apartamento.hpp"

// Definimos un costo base y nombre diferenciados para cumplir con el requisito 
// de extensibilidad, permitiendo que el cliente elija este componente como raíz.
Apartamento::Apartamento() 
    : costoBase_(35000.0), nombre_("Apartamento 1/2 ambiente 🏢") {}

std::string Apartamento::obtenerDescripcion() const 
    {
        return nombre_;
    }

double Apartamento::calcularPresupuesto() const 
    {
        return costoBase_;
    }