#include "librerias.h"

void imprimirByteBinario(char byte) {
    for (int i = 7; i >= 0; i--) {
        cout << ((byte >> i) & 1);
    }
}

void imprimirArchivoBinario(const char* nombre_archivo) {
    ifstream entrada(nombre_archivo, ios::in | ios::binary);

    if (!entrada.is_open()) {
        cout << "\n--- ERROR: No se pudo abrir el archivo " << nombre_archivo << " para impresion. ---" << endl;
        return;
    }

    cout << "\n--- CONTENIDO BINARIO DE " << nombre_archivo << " ---" << endl;

    char byte;
    int contador_bytes = 0;

    while (entrada.get(byte)) {
        imprimirByteBinario(byte);
        cout << " ";

        contador_bytes++;

        if (contador_bytes % 16 == 0) {
            cout << endl;
        }
    }

    cout << "\n\n--- FIN DE LECTURA. Total de bytes: " << contador_bytes << " ---" << endl;
    entrada.close();
}
