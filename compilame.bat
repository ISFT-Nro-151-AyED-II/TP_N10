@echo off
rem Forzamos la consola a usar UTF-8 para que no se rompa con los emojis
chcp 65001 > nul

title Compilador - Sistema de Presupuestos (Patron Decorator)
echo =======================================================
echo ⚙️ Compilando el proyecto con g++ (Estandar C++20)...
echo =======================================================
echo.

g++ -std=c++20 -Wall -Wextra main.cpp src\componentes\Hotel.cpp src\componentes\Apartamento.cpp src\componentes\Hostel.cpp src\decoradores\DecoradorAlojamiento.cpp src\decoradores\ServicioDesayuno.cpp src\decoradores\ServicioCochera.cpp src\decoradores\ServicioPileta.cpp src\cliente\Menu.cpp -o PresupuestoAlojamiento.exe

rem Usamos ERRORLEVEL 1 y goto para evitar el uso de parentesis que rompen el CMD
if ERRORLEVEL 1 goto error

echo ✅ [EXITO] Compilacion terminada sin errores.
echo 🚀 Iniciando PresupuestoAlojamiento.exe...
echo.

PresupuestoAlojamiento.exe

echo.
pause
exit /b 0

:error
echo.
echo ❌ [ERROR] Hubo fallos durante la compilacion. Revisa la salida del compilador arriba.
pause
exit /b 1