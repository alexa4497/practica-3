#include "librerias.h"

int inicioSistema() {
    // --- Sección Semilla n ---
    bool entrada_valida = false;
    string input_str;
    int n = -1;

    while (!entrada_valida) {
        cout << "Ingrese la semilla de codificacion n : ";

        if (!(cin >> input_str)) {
            continue;
        }
        try {
            n = stoi(input_str);
            if (n <= 0) {
                throw 1;
            }
            entrada_valida = true;
            cout << "Semilla (n) guardada: " << n << endl;

        }
        catch (int error_code) {
            if (error_code == 1) {
                cout << "Error de validacion: La semilla debe ser un numero entero positivo." << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << "Error: Valor incorrecto. Ingrese solo numeros enteros." << endl;
        }
    }

    // --- Sección Método de Codificación con Validación ---
    string metodo ="";
    bool metodo_valido = false;

    while (!metodo_valido) {
        cout << "Ingrese el metodo de codificacion deseado (1 o 2): ";
        cin >> metodo;

        if (metodo == "1"){
            metodo_valido = true;
        }else if (metodo == "2"){
            metodo_valido = true;
        } else {
            cout << "Error: Metodo no valido. Ingrese '1' o '2'." << endl;
        }
    }
    return n;
}

int menuPrincipal(){
    cout << "--- CAJERO ELECTRÓNICO UdeA ---"<< endl;
}
