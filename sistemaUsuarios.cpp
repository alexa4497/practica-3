#include "librerias.h"

void realizarRetiro(string cedula, string clave, string& saldo_actual) {
    const char* archivo_txt = "usuarios.txt";
    const char* archivo_bin = "usuarios.bin";
    const char* usuario_temp_txt = "usuario_temp.txt";
    const char* usuario_codificado_temp = "usuario_codificado_temp.bin";

    int saldo = stoi(saldo_actual);
    int cantidad_retiro;

    cout << "\n--- RETIRO DE DINERO ---" << endl;
    cout << "Saldo disponible: $" << saldo << endl;
    cout << "Costo por retiro: $1000" << endl;
    cout << "Ingrese la cantidad a retirar: $";
    cin >> cantidad_retiro;

    // Verificar si tiene suficiente saldo (incluyendo el costo de $1000)
    if (saldo >= (cantidad_retiro + 1000)) {
        // Calcular nuevo saldo
        int nuevo_saldo = saldo - cantidad_retiro - 1000;
        saldo_actual = to_string(nuevo_saldo);

        // ACTUALIZAR ARCHIVO TXT
        ifstream txt_lectura(archivo_txt);
        ofstream txt_temporal("usuarios_temp.txt");
        string linea;

        while (getline(txt_lectura, linea)) {
            stringstream ss(linea);
            string cedula_archivo, clave_archivo, saldo_old;
            getline(ss, cedula_archivo, ',');
            getline(ss, clave_archivo, ',');
            getline(ss, saldo_old, ',');

            if (cedula_archivo == cedula && clave_archivo == clave) {
                txt_temporal << cedula << "," << clave << "," << saldo_actual << endl;
            } else {
                txt_temporal << linea << endl;
            }
        }
        txt_lectura.close();
        txt_temporal.close();

        // Reemplazar archivo original
        remove(archivo_txt);
        rename("usuarios_temp.txt", archivo_txt);

        // ACTUALIZAR ARCHIVO BIN
        ofstream limpiar_bin(archivo_bin, ios::binary | ios::trunc);
        limpiar_bin.close();

        ifstream txt_completo(archivo_txt);
        string linea_actual;
        while (getline(txt_completo, linea_actual)) {
            ofstream temp_linea(usuario_temp_txt);
            temp_linea << linea_actual;
            temp_linea.close();

            if (metodo_elegido_global == 1) {
                codificar_primer_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
            } else if (metodo_elegido_global == 2) {
                codificar_segundo_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
            }

            ofstream bin_out(archivo_bin, ios::app | ios::binary);
            ifstream codificado_in(usuario_codificado_temp, ios::binary);

            if (bin_out.is_open() && codificado_in.is_open()) {
                codificado_in.seekg(0, ios::end);
                long size = codificado_in.tellg();
                codificado_in.seekg(0, ios::beg);

                char* buffer = new char[size];
                codificado_in.read(buffer, size);
                bin_out.write(buffer, size);
                delete[] buffer;
                bin_out << '\n';
            }
            bin_out.close();
            codificado_in.close();
        }
        txt_completo.close();

        remove(usuario_temp_txt);
        remove(usuario_codificado_temp);

        cout << "\n*** RETIRO EXITOSO ***" << endl;
        cout << "Cantidad retirada: $" << cantidad_retiro << endl;
        cout << "Costo por retiro: $1000" << endl;
        cout << "Nuevo saldo: $" << saldo_actual << endl;
        cout << "**********************" << endl;
    } else {
        cout << "✗ Saldo insuficiente para realizar el retiro" << endl;
        cout << "Necesitas: $" << (cantidad_retiro + 1000) << " (retiro + costo)" << endl;
        cout << "Saldo disponible: $" << saldo << endl;
    }
}

void menuUsuario() {
    const char* archivo_txt = "usuarios.txt";
    const char* archivo_bin = "usuarios.bin";
    const char* usuario_temp_txt = "usuario_temp.txt";
    const char* usuario_codificado_temp = "usuario_codificado_temp.bin";

    string cedulaBuscada, claveBuscada;

    cout << "\n=== VERIFICACION DE USUARIO ===" << endl;
    cout << "Ingrese cedula: ";
    cin >> cedulaBuscada;
    cout << "Ingrese clave: ";
    cin >> claveBuscada;


    cout << "Actualizando base de datos..." << endl;


    ofstream limpiar_bin(archivo_bin, ios::binary | ios::trunc);
    limpiar_bin.close();


    ifstream txt_completo(archivo_txt);
    if (!txt_completo.is_open()) {
        cout << "Error: No se pudo abrir usuarios.txt" << endl;
        return;
    }

    string linea_actual;
    while (getline(txt_completo, linea_actual)) {

        ofstream temp_linea(usuario_temp_txt);
        temp_linea << linea_actual;
        temp_linea.close();


        if (metodo_elegido_global == 1) {
            codificar_primer_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
        } else if (metodo_elegido_global == 2) {
            codificar_segundo_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
        }

        ofstream bin_out(archivo_bin, ios::app | ios::binary);
        ifstream codificado_in(usuario_codificado_temp, ios::binary);

        if (bin_out.is_open() && codificado_in.is_open()) {
            codificado_in.seekg(0, ios::end);
            long size = codificado_in.tellg();
            codificado_in.seekg(0, ios::beg);

            char* buffer = new char[size];
            codificado_in.read(buffer, size);
            bin_out.write(buffer, size);

            delete[] buffer;
            bin_out << '\n';
        }

        bin_out.close();
        codificado_in.close();
    }
    txt_completo.close();


    remove(usuario_temp_txt);
    remove(usuario_codificado_temp);

    ifstream txt_file(archivo_txt);
    if (!txt_file.is_open()) {
        cout << "Error: No se pudo abrir usuarios.txt" << endl;
        return;
    }

    string linea_txt;
    bool encontrado = false;
    string linea_completa;
    string saldo_usuario;
    string cedula_encontrada, clave_encontrada;

    while (getline(txt_file, linea_txt)) {
        stringstream ss(linea_txt);
        string cedula, clave, saldo;

        getline(ss, cedula, ',');
        getline(ss, clave, ',');
        getline(ss, saldo, ',');

        if (cedula == cedulaBuscada && clave == claveBuscada) {
            encontrado = true;
            linea_completa = linea_txt;
            saldo_usuario = saldo;
            cedula_encontrada = cedula;
            clave_encontrada = clave;
            break;
        }
    }
    txt_file.close();

    if (!encontrado) {
        cout << "✗ Usuario no encontrado o clave incorrecta" << endl;
        return;
    }


    ofstream temp_txt(usuario_temp_txt);
    temp_txt << linea_completa;
    temp_txt.close();

    // Codificar
    if (metodo_elegido_global == 1) {
        codificar_primer_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
    } else if (metodo_elegido_global == 2) {
        codificar_segundo_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
    }


    ifstream temp_codificado(usuario_codificado_temp, ios::binary | ios::ate);
    if (!temp_codificado.is_open()) {
        remove(usuario_temp_txt);
        cout << "Error en codificación" << endl;
        return;
    }

    long size_temp = temp_codificado.tellg();
    temp_codificado.seekg(0, ios::beg);
    char* buffer_temp = new char[size_temp];
    temp_codificado.read(buffer_temp, size_temp);
    temp_codificado.close();

    // Buscar en BIN
    ifstream bin_file(archivo_bin, ios::binary);
    if (!bin_file.is_open()) {
        delete[] buffer_temp;
        remove(usuario_temp_txt);
        remove(usuario_codificado_temp);
        cout << "Error al abrir base de datos" << endl;
        return;
    }

    bool son_iguales = false;
    int linea_bin = 0;

    while (bin_file.peek() != EOF) {
        char* buffer_almacenado = new char[size_temp];

        if (bin_file.read(buffer_almacenado, size_temp)) {
            if (memcmp(buffer_almacenado, buffer_temp, size_temp) == 0) {
                son_iguales = true;
                delete[] buffer_almacenado;
                break;
            }
        }
        bin_file.clear();
        delete[] buffer_almacenado;
        bin_file.seekg(1, ios::cur);
        linea_bin++;
        if (bin_file.eof()) break;
    }

    bin_file.close();
    delete[] buffer_temp;
    remove(usuario_temp_txt);
    remove(usuario_codificado_temp);

    if (!son_iguales) {
        cout << "Error de seguridad: inconsistencia en base de datos" << endl;
        return;
    }

    cout << "VERIFICACION EXITOSA: Bienvenido " << cedula_encontrada << endl;

    // MENÚ DE OPCIONES PARA EL USUARIO
    int opcion_usuario = 0;
    do {
        cout << "\n--- MENU USUARIO ---" << endl;
        cout << "1. Consultar saldo (costo: $1000)" << endl;
        cout << "2. Realizar retiro (costo: $1000)" << endl;  // ← Actualiza esta línea
        cout << "3. Salir" << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion_usuario;

        switch (opcion_usuario) {
        case 1: {
            // Convertir saldo a número y restar 1000
            int saldo_actual = stoi(saldo_usuario);
            if (saldo_actual >= 1000) {
                saldo_actual -= 1000;
                saldo_usuario = to_string(saldo_actual);

                // ACTUALIZAR ARCHIVO TXT
                ifstream txt_lectura(archivo_txt);
                ofstream txt_temporal("usuarios_temp.txt");
                string linea;

                while (getline(txt_lectura, linea)) {
                    stringstream ss(linea);
                    string cedula, clave, saldo_old;
                    getline(ss, cedula, ',');
                    getline(ss, clave, ',');
                    getline(ss, saldo_old, ',');

                    if (cedula == cedula_encontrada && clave == clave_encontrada) {
                        txt_temporal << cedula << "," << clave << "," << saldo_usuario << endl;
                    } else {
                        txt_temporal << linea << endl;
                    }
                }
                txt_lectura.close();
                txt_temporal.close();

                // Reemplazar archivo original
                remove(archivo_txt);
                rename("usuarios_temp.txt", archivo_txt);

                // ACTUALIZAR ARCHIVO BIN
                ofstream limpiar_bin2(archivo_bin, ios::binary | ios::trunc);
                limpiar_bin2.close();

                ifstream txt_completo2(archivo_txt);
                string linea_actual2;
                while (getline(txt_completo2, linea_actual2)) {
                    ofstream temp_linea2(usuario_temp_txt);
                    temp_linea2 << linea_actual2;
                    temp_linea2.close();

                    if (metodo_elegido_global == 1) {
                        codificar_primer_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
                    } else if (metodo_elegido_global == 2) {
                        codificar_segundo_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
                    }

                    ofstream bin_out2(archivo_bin, ios::app | ios::binary);
                    ifstream codificado_in2(usuario_codificado_temp, ios::binary);

                    if (bin_out2.is_open() && codificado_in2.is_open()) {
                        codificado_in2.seekg(0, ios::end);
                        long size = codificado_in2.tellg();
                        codificado_in2.seekg(0, ios::beg);

                        char* buffer = new char[size];
                        codificado_in2.read(buffer, size);
                        bin_out2.write(buffer, size);
                        delete[] buffer;
                        bin_out2 << '\n';
                    }
                    bin_out2.close();
                    codificado_in2.close();
                }
                txt_completo2.close();

                remove(usuario_temp_txt);
                remove(usuario_codificado_temp);

                cout << "\n*** CONSULTA DE SALDO ***" << endl;
                cout << "Costo de consulta: $1000" << endl;
                cout << "Cedula: " << cedula_encontrada << endl;
                cout << "Saldo actual: $" << saldo_usuario << endl;
                cout << "**************************" << endl;
            } else {
                cout << "Saldo insuficiente para realizar consulta" << endl;
            }
            break;
        }

        case 2:
            realizarRetiro(cedula_encontrada, clave_encontrada, saldo_usuario);

            break;
        case 3:
            cout << "Saliendo del menu usuario..." << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
        }
    } while (opcion_usuario != 2);
}
