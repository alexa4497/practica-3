#include "librerias.h"

void imprimirByteBinario(char byte) {
    for (int i = 7; i >= 0; i--) {
        cout << ((byte >> i) & 1);
    }
}

void imprimirArchivoBinario(const char* nombre_archivo) {
    ifstream entrada(nombre_archivo, ios::in | ios::binary);

    try {
        if (!entrada.is_open()) {
            throw "No se pudo abrir el archivo para impresion.";
        }
    } catch (const char *error) {
        cout << "Error: " << error;
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
