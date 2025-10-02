#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <cstdio>

using namespace std;

int menuPrincipal();
int inicioSistema(int& n);


void logicaAccesoAdministrador(int n, int metodo);
void registrarClaveAdmin(int n, int metodo);
bool validarAccesoAdmin(int n, int metodo, const string& clave_ingresada);
void inicializarBaseAdmin(int n, int metodo);
void verificarInicializacionAdmin(int n, int metodo) ;

void contar_bits(const char* buffer_datos, int num_bytes, int n, int* unos, int* ceros);
void aplicar_regla_codificacion(char* buffer_datos, int num_bytes, int n, int conteo_unos_ant, int conteo_ceros_ant);
void codificar_primer_metodo(const char* archivo_fuente, const char* archivo_salida, int n);





#endif // LIBRERIAS_H
