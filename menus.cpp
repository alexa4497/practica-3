#include "librerias.h"


int inicioSistema(int& n) {
    bool entrada_valida = false;
    string input_str;
    n = 0;

    while (!entrada_valida) {
        cout << "Ingrese la semilla de codificacion n: ";
        if (!(cin >> input_str)) {
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }
        try {
            n = stoi(input_str);
            if (n <= 0) throw 1;
            entrada_valida = true;
            cout << "Semilla (n) guardada: " << n << endl;
        } catch (int error0) {
            cout << "Error: La semilla debe ser un numero entero positivo." << endl;
        }
    }

    string metodo_str;
    int metodo = -1;
    bool metodo_valido = false;

    while (!metodo_valido) {
        cout << "Ingrese el metodo de codificacion deseado (1 o 2): ";
        cin >> metodo_str;
        try {
            if (metodo_str == "1"){
                metodo = 1; metodo_valido = true;
            } else if (metodo_str == "2"){
                metodo = 2; metodo_valido = true;
            } else {
                throw "Metodo no valido. Ingrese '1' o '2'.";
            }
        } catch (const char *error) {
            cout << "Error: " << error << endl;
        }

    }
    return metodo;
}

int menuPrincipal() {
    string opcion = "";
    int opcion_int = -1;
    bool entrada_valida = false;

    while (!entrada_valida) {
        cout << "\n--- CAJERO ELECTONICO UdeA ---" << endl;
        cout << "1. Acceder como administrador " << endl;
        cout << "2. Acceder como usuario " << endl;
        cout << "3. Salir del programa " << endl;
        cout << "-------------------------------" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        try {
            if (opcion == "1" || opcion == "2" || opcion == "3") {
                opcion_int = stoi(opcion);
                entrada_valida = true;
            } else {
                throw "ingrese un alguno de los numeros 1,2,3";
            }
        } catch (const char *error) {
            cout << "Error: " << error << endl;
        }
    }
    return opcion_int;
}
