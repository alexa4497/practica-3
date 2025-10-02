#include "librerias.h"
int main() {
    int semilla_n = 0;
    int opcion_menu = 0;
    bool salir = false;

    int metodo_elegido = inicioSistema(semilla_n);

    verificarInicializacionAdmin(semilla_n, metodo_elegido);

    while (!salir) {
        opcion_menu = menuPrincipal();

        switch (opcion_menu) {
        case 1:
            logicaAccesoAdministrador(semilla_n, metodo_elegido);
            break;
        case 2:

            break;
        case 3:
            cout << "\nSaliendo del programa. ¡chao!" << endl;
            salir = true;
            break;
        default:
            break;
        }
    }

    return 0;
}
