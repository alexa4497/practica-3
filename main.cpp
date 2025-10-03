#include "librerias.h"

int semilla_n_global = 0;
int metodo_elegido_global = 0;

int main() {
    int semilla_n = 0;
    int opcion_menu = 0;
    bool salir = false;

    int metodo_elegido = inicioSistema(semilla_n);

    semilla_n_global = semilla_n;
    metodo_elegido_global = metodo_elegido;

    verificarInicializacionAdmin(semilla_n, metodo_elegido);

    while (!salir) {
        opcion_menu = menuPrincipal();

        switch (opcion_menu) {
        case 1:
            logicaAccesoAdministrador(semilla_n, metodo_elegido);
            break;
        case 2:
            menuUsuario();
            break;
        case 3:
            cout << "\nSaliendo del programa." << endl;
            salir = true;
            break;
        default:
            cout << "\n[!] Opcion no valida. Intente de nuevo." << endl;
            break;
        }
    }

    return 0;
}
