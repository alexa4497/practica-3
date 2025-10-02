#include "librerias.h"


int inicioSistema(int& n) {
    bool entrada_valida = false;
    string input_str;
    n = 0;

    while (!entrada_valida) {
        cout << "Ingrese la semilla de codificacion n: ";
        if (!(cin >> input_str)) {
            // Manejo de error de cin
            cin.clear();
            cin.ignore(256, '\n');
            continue;
        }
        try {
            n = stoi(input_str);
            if (n <= 0) throw 1;
            entrada_valida = true;
            cout << "Semilla (n) guardada: " << n << endl;
        } catch (int error_code) {
            cout << "Error: La semilla debe ser un numero entero positivo." << endl;
        } catch (const invalid_argument& e) {
            cout << "Error: Valor incorrecto. Ingrese solo numeros enteros." << endl;
        }
    }

    string metodo_str;
    int metodo = -1;
    bool metodo_valido = false;

    while (!metodo_valido) {
        cout << "Ingrese el metodo de codificacion deseado (1 o 2): ";
        cin >> metodo_str;

        if (metodo_str == "1"){
            metodo = 1; metodo_valido = true;
        } else if (metodo_str == "2"){
            metodo = 2; metodo_valido = true;
        } else {
            cout << "Error: Metodo no valido. Ingrese '1' o '2'." << endl;
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

        if (opcion == "1" || opcion == "2" || opcion == "3") {
            opcion_int = stoi(opcion);
            entrada_valida = true;
        } else {
            cout << "Error: Opcion no valida. Por favor, ingrese 1, 2 o 3." << endl;
        }
    }
    return opcion_int;
}
