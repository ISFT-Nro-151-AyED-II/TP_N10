#pragma once
#include <memory>
#include "../interfaces/Alojamiento.hpp"

// Clase Cliente. Se encarga de la interacción con el usuario y de orquestar la construcción dinámica 
// de la pila de decoradores en tiempo de ejecución.
class Menu 
    {
        public:

            Menu() = default;
            ~Menu() = default;

            // Punto de entrada único para el flujo de la interfaz de usuario.
            void iniciar();

        private:
        
            // Submódulos privados para segmentar responsabilidades y evitar un método monolítico.
            // Retornan unique_ptr para mover la propiedad del objeto configurado entre funciones.
            [[nodiscard]] std::unique_ptr<Alojamiento> mostrarOpcionesAlojamiento();

            // [[nodiscard]] impide ignorar el retorno. Aplica semántica de movimiento: toma la 
            // propiedad exclusiva del alojamiento, lo envuelve dinámicamente con un decorador concreto 
            // y devuelve la propiedad de la nueva estructura.
            [[nodiscard]] std::unique_ptr<Alojamiento> agregarServicios(std::unique_ptr<Alojamiento> alojamiento);
            
            // Se pasa por referencia constante para leer los datos del presupuesto sin alterar la propiedad 
            // ni el estado del objeto.
            void mostrarPresupuesto(const std::unique_ptr<Alojamiento>& alojamiento) const;
    };