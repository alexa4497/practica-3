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

// Implementación de codificar_primer_metodo (VERSION DEFINITIVA para Claves de Admin)
void codificar_primer_metodo(const char* archivo_fuente,
                             const char* archivo_salida,
                             int n) {

    // Paso 1: Abrir archivos y obtener el tamaño total del archivo de la clave
    ifstream entrada(archivo_fuente, ios::in | ios::binary | ios::ate);
    ofstream salida(archivo_salida, ios::out | ios::binary);

    if (!entrada.is_open() || !salida.is_open()) {
        cerr << "Error al abrir archivos." << endl;
        return;
    }

    long size_total_bytes = entrada.tellg();
    entrada.seekg(0, ios::beg);

    if (size_total_bytes <= 0) {
        entrada.close();
        salida.close();
        return;
    }

    // El buffer debe ser del tamaño EXACTO de la clave de texto (ej: 4 bytes para "1097")
    const int NUM_BYTES_REAL = size_total_bytes;
    char* buffer_original = new char[NUM_BYTES_REAL];
    char* buffer_codificado = new char[NUM_BYTES_REAL];

    // Paso 2: Leer el bloque completo de la clave
    if (entrada.read(buffer_original, NUM_BYTES_REAL)) {
        memcpy(buffer_codificado, buffer_original, NUM_BYTES_REAL);

        // --- LÓGICA DE CODIFICACIÓN (Determinista para Claves) ---

        // 1. Usar el buffer original para contar sus bits. (Simula el primer bloque)
        int conteo_unos = 0;
        int conteo_ceros = 0;
        contar_bits(buffer_original, NUM_BYTES_REAL, n, &conteo_unos, &conteo_ceros);

        // 2. Aplicar la regla de codificación usando el conteo (ahora sí, dependiente de N)
        aplicar_regla_codificacion(buffer_codificado, NUM_BYTES_REAL, n, conteo_unos, conteo_ceros);

        // 3. Escribir el bloque codificado
        salida.write(buffer_codificado, NUM_BYTES_REAL);
    }

    delete[] buffer_original;
    delete[] buffer_codificado;

    entrada.close();
    salida.close();
}
