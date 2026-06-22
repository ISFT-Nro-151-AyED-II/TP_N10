#include <windows.h>
#include "include/cliente/Menu.hpp"

// Punto de entrada único a la aplicación. Su rol se limita estrictamente
// a la inicialización del entorno y la delegación del control al módulo cliente.
int main() 
    {
        // Configuración obligatoria para que la consola de Windows interprete correctamente
        // el estándar UTF-8, garantizando el renderizado de caracteres especiales (ñ, tildes)
        // y los emojis contextuales de la interfaz de usuario sin romper el diseño de pantalla.
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);

        // Se instancia el controlador del menú en la pila (stack) por eficiencia,
        // ya que no requiere persistencia extendida fuera del ciclo de vida de main.
        Menu clienteMenu;
        clienteMenu.iniciar();

        return 0;
    }