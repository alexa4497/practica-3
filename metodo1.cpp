#include "librerias.h"

void contar_bits(const char* buffer_datos, int num_bytes, int n, int* unos, int* ceros) {
    *unos = 0;
    *ceros = 0;
    int bits_contados = 0;

    for (int i = 0; i < num_bytes; ++i) {
        char byte_actual = buffer_datos[i];
        for (int j = 7; j >= 0 && bits_contados < n; --j) {
            if (byte_actual & (1 << j)) {
                (*unos)++;
            } else {
                (*ceros)++;
            }
            bits_contados++;
        }
    }
}

void aplicar_regla_codificacion(char* buffer_datos,
                                int num_bytes,
                                int n,
                                int conteo_unos_ant,
                                int conteo_ceros_ant) {

    int inversion_cada = 0;


    if (conteo_unos_ant == conteo_ceros_ant) {
        inversion_cada = 1;
    } else if (conteo_ceros_ant > conteo_unos_ant) {
        inversion_cada = 2;
    } else {
        inversion_cada = 3;
    }

    int bit_posicion_global = 1;

    for (int i = 0; i < num_bytes; ++i) {
        for (int j = 7; j >= 0 && bit_posicion_global <= n; --j) {
            if (bit_posicion_global % inversion_cada == 0) {
                // Inversión de bit usando XOR
                buffer_datos[i] ^= (1 << j);
            }
            bit_posicion_global++;
        }
    }
}


void codificar_primer_metodo(const char* archivo_fuente,
                             const char* archivo_salida,
                             int n) {

    ifstream entrada(archivo_fuente, ios::in | ios::binary | ios::ate);
    ofstream salida(archivo_salida, ios::out | ios::binary);

    try {
        if (!entrada.is_open() || !salida.is_open()) {
            string mensaje_error1 = "Error al abrir archivos.";
            throw mensaje_error1;
        }
    } catch (const char *error1) {
        cout << "Error : " << error1;
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

        int conteo_unos = 0;
        int conteo_ceros = 0;
        contar_bits(buffer_original, NUM_BYTES_REAL, n, &conteo_unos, &conteo_ceros);

        aplicar_regla_codificacion(buffer_codificado, NUM_BYTES_REAL, n, conteo_unos, conteo_ceros);

        salida.write(buffer_codificado, NUM_BYTES_REAL);
    }

    delete[] buffer_original;
    delete[] buffer_codificado;

    entrada.close();
    salida.close();
}
