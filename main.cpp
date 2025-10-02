#include "librerias.h"
int main() {
    int semilla_n = 0; // Se inicializa a 0. Su valor real se obtiene por referencia.
    int opcion_menu = 0;
    bool salir = false;

    // --- 1. CONFIGURACIÓN INICIAL DEL SISTEMA ---
    // Llama a la función que pide n y el método, y asigna los valores a las variables.
    int metodo_elegido = inicioSistema(semilla_n);

    // **CRÍTICO: LLAMADA DE INICIALIZACIÓN TEMPRANA**
    // Verifica y crea sudo.bin (con 1097 y 4776) si no existe, usando la semilla y método correctos.
    verificarInicializacionAdmin(semilla_n, metodo_elegido);

    // Nombres de archivos a codificar/decodificar (puedes solicitarlos al usuario si es necesario)
    const char* archivo_entrada = "sudo.txt";
    const char* archivo_codificado = "transacciones_codificadas.bin";

    // ... (Tu código de codificación de prueba, si aplica) ...

    // --- 2. CICLO PRINCIPAL DEL CAJERO ---
    while (!salir) {
        opcion_menu = menuPrincipal(); // Obtiene la opción 1, 2, o 3

        switch (opcion_menu) {
        case 1:
            // La lógica del administrador ahora SOLO valida, la inicialización ya se hizo.
            logicaAccesoAdministrador(semilla_n, metodo_elegido);
            break;
        case 2:
            // ... (Resto del código) ...
            break;
        case 3:
            cout << "\nSaliendo del programa. ¡Hasta luego!" << endl;
            salir = true;
            break;
        default:
            break;
        }
    }

    return 0;
}
