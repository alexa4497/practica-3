#include "librerias.h"

bool verificarUsuario() {
    extern int semilla_n_global;
    extern int metodo_elegido_global;

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


    ofstream limpiar_bin(archivo_bin, ios::binary | ios::trunc);
    limpiar_bin.close();

    ifstream txt_completo(archivo_txt);
    if (!txt_completo.is_open()) {
        cout << "Error: No se pudo abrir usuarios.txt" << endl;
        return false;
    }

    string linea_actual;
    while (getline(txt_completo, linea_actual)) {
        ofstream temp_linea(usuario_temp_txt);
        temp_linea << linea_actual;
        temp_linea.close();

        // Codificar la línea
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
        return false;
    }

    string linea_txt;
    bool encontrado = false;
    string linea_completa;

    while (getline(txt_file, linea_txt)) {
        stringstream ss(linea_txt);
        string cedula, clave, saldo;

        getline(ss, cedula, ',');
        getline(ss, clave, ',');
        getline(ss, saldo, ',');

        if (cedula == cedulaBuscada && clave == claveBuscada) {
            encontrado = true;
            linea_completa = linea_txt;
            break;
        }
    }
    txt_file.close();

    if (!encontrado) {
        cout << "Usuario no encontrado en usuarios.txt" << endl;
        return false;
    }

    ofstream temp_txt(usuario_temp_txt);
    temp_txt << linea_completa;
    temp_txt.close();


    if (metodo_elegido_global == 1) {
        codificar_primer_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
    } else if (metodo_elegido_global == 2) {
        codificar_segundo_metodo(usuario_temp_txt, usuario_codificado_temp, semilla_n_global);
    }

    ifstream temp_codificado(usuario_codificado_temp, ios::binary | ios::ate);
    if (!temp_codificado.is_open()) {
        remove(usuario_temp_txt);
        return false;
    }

    long size_temp = temp_codificado.tellg();
    temp_codificado.seekg(0, ios::beg);
    char* buffer_temp = new char[size_temp];
    temp_codificado.read(buffer_temp, size_temp);
    temp_codificado.close();

    // Buscar en BIN (que ahora está actualizado)
    ifstream bin_file(archivo_bin, ios::binary);
    if (!bin_file.is_open()) {
        delete[] buffer_temp;
        remove(usuario_temp_txt);
        remove(usuario_codificado_temp);
        return false;
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

    if (son_iguales) {
        cout << "✓ VERIFICACION EXITOSA: Usuario validado" << endl;
    } else {
        cout << "✗ VERIFICACION FALLIDA: Usuario no coincide" << endl;
    }

    return son_iguales;
}
