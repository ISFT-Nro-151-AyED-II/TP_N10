#include "../../include/cliente/Menu.hpp"
#include "../../include/componentes/Hotel.hpp"
#include "../../include/componentes/Apartamento.hpp"
#include "../../include/componentes/Hostel.hpp"
#include "../../include/decoradores/ServicioDesayuno.hpp"
#include "../../include/decoradores/ServicioCochera.hpp"
#include "../../include/decoradores/ServicioPileta.hpp"
#include <iostream>
#include <utility>
#include <limits>

void Menu::iniciar() 
    {
        std::cout << "\n============================================\n";
        std::cout << " 🏨 SISTEMA DE PRESUPUESTOS DE ALOJAMIENTOS \n";
        std::cout << "============================================\n";

        // Se captura el componente base seleccionado por el usuario.
        std::unique_ptr<Alojamiento> miAlojamiento = mostrarOpcionesAlojamiento();
        
        // Control de flujo defensivo en caso de que el usuario decida salir prematuramente.
        if (!miAlojamiento) 
            {
                std::cout << "\n👋 Operación cancelada por el usuario... ¡Volvé Cobarde! 🧐...\n";
                return;
            }

        // Se pasa la propiedad del objeto base a la función de adición de servicios 
        // y se recupera la estructura final completamente decorada.
        miAlojamiento = agregarServicios(std::move(miAlojamiento));

        // Despliegue de resultados finales en pantalla.
        mostrarPresupuesto(miAlojamiento);
    }

std::unique_ptr<Alojamiento> Menu::mostrarOpcionesAlojamiento() 
    {
        int opcion = 0;
        
        while (true) 
            {
                std::cout << "\n📌 Seleccioná el tipo de alojamiento base:\n\n";
                std::cout << "1. Hotel Medio Pelo del Mar 🌟\n";
                std::cout << "2. Apartamento 1/2 ambiente 🏢\n";
                std::cout << "3. Hostel Psico Bates 🎒\n";
                std::cout << "4. Salir ❌\n\n";
                std::cout << "👉 Opción: ";
                std::cin >> opcion;

                // Validación de tipo para mitigar la inyección de caracteres inválidos en el stream.
                if (std::cin.fail()) 
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "\n⚠️ Error: Ingresá un número válido.\n";
                        continue;
                    }

                // Se utiliza std::make_unique para instanciar el objeto de manera segura,
                // evitando fugas de memoria si el constructor arrojara una excepción.
                switch (opcion) 
                    {
                        case 1: return std::make_unique<Hotel>();
                        case 2: return std::make_unique<Apartamento>();
                        case 3: return std::make_unique<Hostel>();
                        case 4: return nullptr;
                        default:
                            std::cout << "\n❌ Opción incorrecta. Intentá de nuevo.\n";
                    }
            }
    }

std::unique_ptr<Alojamiento> Menu::agregarServicios(std::unique_ptr<Alojamiento> alojamiento) 
    {
        int opcion = 0;
        bool continuar = true;

        while (continuar) 
            {
                std::cout << "\n➕ ¿Qué servicios adicionales querés sumar al presupuesto?\n\n";
                std::cout << "1. Desayuno Continental ☕\n";
                std::cout << "2. Cochera Casi Cubierta 🚗\n";
                std::cout << "3. Acceso a Pelopincho Climatizada 🏊‍♂️\n";
                std::cout << "4. Terminar y Calcular Presupuesto Total 📈\n\n";
                std::cout << "👉 Opción: ";
                std::cin >> opcion;

                if (std::cin.fail()) 
                    {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "\n⚠️ Error: Ingresá un número válido.\n";
                        continue;
                    }

                // En cada caso, se envuelve el puntero actual dentro de un nuevo decorador,
                // logrando el acoplamiento dinámico en tiempo de ejecución. El uso de std::move
                // es obligatorio porque los decoradores exigen tomar la propiedad total del objeto previo.
                switch (opcion) 
                    {
                        case 1:
                            alojamiento = std::make_unique<ServicioDesayuno>(std::move(alojamiento));
                            std::cout << "\n✅ Desayuno agregado.\n";
                            break;
                        case 2:
                            alojamiento = std::make_unique<ServicioCochera>(std::move(alojamiento));
                            std::cout << "\n✅ Cochera agregada.\n";
                            break;
                        case 3:
                            alojamiento = std::make_unique<ServicioPileta>(std::move(alojamiento));
                            std::cout << "\n✅ Acceso a pileta agregado.\n";
                            break;
                        case 4:
                            continuar = false;
                            break;
                        default:
                            std::cout << "\n❌ Opción incorrecta. Intentá de nuevo.\n";
                    }
            }
            
        return alojamiento;
    }

void Menu::mostrarPresupuesto(const std::unique_ptr<Alojamiento>& alojamiento) const 
    {
        if (!alojamiento) return;

        std::cout << "\n\n 🧾 DETALLE DEL PRESUPUESTO FINAL \n";
        std::cout << "===================================\n\n";
        
        // Se invocan las operaciones polimórficas. Al estar el objeto completamente
        // decorado, la ejecución se propagará recursivamente a través de toda la pila.
        std::cout << "📝 Detalle: " << alojamiento->obtenerDescripcion() << "\n";
        std::cout << "💰 Total Estimado: $" << alojamiento->calcularPresupuesto() << "\n";
        std::cout << "\n=============================================\n";
        std::cout << " ✨ Gracias por utilizar nuestro sistema ✨\n";
        std::cout << "=============================================\n";
    }