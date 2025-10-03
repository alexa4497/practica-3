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

// Variables globales para compartir entre funciones
extern int semilla_n_global;
extern int metodo_elegido_global;
//inicio administradores
void logicaAccesoAdministrador(int n, int metodo);
bool validarAccesoAdmin(int n, int metodo, const string& clave_ingresada);
void inicializarBaseAdmin(int n, int metodo);
void verificarInicializacionAdmin(int n, int metodo) ;

//metodo 1
void contar_bits(const char* buffer_datos, int num_bytes, int n, int* unos, int* ceros);
void aplicar_regla_codificacion(char* buffer_datos, int num_bytes, int n, int conteo_unos_ant, int conteo_ceros_ant);
// CORRECTO en librerias.h: solo la declaracion (termina en punto y coma)

void codificar_primer_metodo(const char* mensaje, const char* clave, int n);
void codificar_segundo_metodo(const char* mensaje, const char* clave, int n);
//crear usuarios
void registrarUsuarioCajero(int n, int metodo);
bool existeCedula(const string& cedula);

//leer binarios
void imprimirByteBinario(char byte);
void imprimirArchivoBinario(const char* nombre_archivo);

void menuUsuario();

#endif // LIBRERIAS_H
