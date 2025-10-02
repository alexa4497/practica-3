#ifndef LIBRERIAS_H
#define LIBRERIAS_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <cstdio>
#include <stdio.h>
#include <sstream>

using namespace std;

//menus
int menuPrincipal();
int inicioSistema(int& n);

//inicio administradores
void logicaAccesoAdministrador(int n, int metodo);
bool validarAccesoAdmin(int n, int metodo, const string& clave_ingresada);
void inicializarBaseAdmin(int n, int metodo);
void verificarInicializacionAdmin(int n, int metodo) ;

//metodo 1
void contar_bits(const char* buffer_datos, int num_bytes, int n, int* unos, int* ceros);
void aplicar_regla_codificacion(char* buffer_datos, int num_bytes, int n, int conteo_unos_ant, int conteo_ceros_ant);
void codificar_primer_metodo(const char* archivo_fuente, const char* archivo_salida, int n);

//metodo 2
void codificar_segundo_metodo(const char* archivo_fuente, const char* archivo_salida, int n);

//crear usuarios
void registrarUsuarioCajero(int n, int metodo);
bool existeCedula(const string& cedula);

//leer archivos
void imprimirByteBinario(char byte);
void imprimirArchivoBinario(const char* nombre_archivo);


#endif // LIBRERIAS_H
