#include "librerias.h"

void codificar_segundo_metodo(const char* archivo_fuente,
                              const char* archivo_salida,
                              int n) {

    ifstream entrada(archivo_fuente, ios::in | ios::binary | ios::ate);
    ofstream salida(archivo_salida, ios::out | ios::binary);

    try {
        if (!entrada.is_open() || !salida.is_open()) {
            string mensaje_error1 = "Error al abrir archivos.";
            throw mensaje_error1;
        }
    } catch (const char *error11) {
        cout << "Error : " << error11;
    }

    long size_total_bytes = entrada.tellg();
    entrada.seekg(0, ios::beg);

    if (size_total_bytes <= 0) {
        entrada.close();
        salida.close();
        return;
    }

    const int NUM_BYTES_REAL = size_total_bytes;
    char* buffer_original = new char[NUM_BYTES_REAL];
    char* buffer_codificado = new char[NUM_BYTES_REAL];


    if (entrada.read(buffer_original, NUM_BYTES_REAL)) {
        memcpy(buffer_codificado, buffer_original, NUM_BYTES_REAL);

        int conteo_unos_falso = 10;
        int conteo_ceros_falso = 20;

        aplicar_regla_codificacion(buffer_codificado,
                                   NUM_BYTES_REAL,
                                   n,
                                   conteo_unos_falso,
                                   conteo_ceros_falso);

        salida.write(buffer_codificado, NUM_BYTES_REAL);
    }

    delete[] buffer_original;
    delete[] buffer_codificado;

    entrada.close();
    salida.close();
}
