#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int inicioSistema() {
    bool entrada_valida = false;
    string input_str;
    int n;
    while (!entrada_valida) {
        cout << "Ingrese la semilla de codificación (n - número entero positivo): ";

        if (!(cin >> input_str)) {
            cin.clear();
            continue;
        }

        n = atoi(input_str.c_str());

        if (n > 0) {
            entrada_valida = true;
            cout << "Semilla (n) guardada: " << n << endl;
            return n;
        } else {
            cout << "Error de validación: La semilla debe ser un número entero positivo (n > 0)." << endl;
        }
    }
    return -1;
}
