#include "librerias.h"
using namespace std;

void verificarInicializacionAdmin(int n, int metodo) {
    inicializarBaseAdmin(n, metodo);
    cout << "\n*** La base de datos de administradores fue CONFIGURADA/ACTUALIZADA con la Semilla (n): " << n << " y Metodo: " << metodo << " ***" << std::endl;
}

void inicializarBaseAdmin(int n, int metodo) {
    const string claves_a_registrar[] = {"1097", "4776"};
    const int num_claves = 2;

    ofstream archivo_limpieza("sudo.bin", ios::binary | ios::trunc);
    archivo_limpieza.close();

    cout << "\n--- INICIALIZACION DE BASE DE ADMINISTRADORES EN sudo.bin (SEMBRANDO N=" << n << ") ---" << std::endl;

    for (int i = 0; i < num_claves; ++i) {
        const string& clave_texto = claves_a_registrar[i];

        const char* clave_fuente_txt = "clave_admin_temp.txt";
        const char* archivo_sudo_bin = "sudo.bin";
        const char* clave_codificada_temp = "clave_codificada_temp.bin";

        ofstream fuente(clave_fuente_txt);
        if (!fuente.is_open()) {
            cout << "Error: No se pudo crear el archivo temporal para la clave " << clave_texto <<endl;
            continue;
        }
        fuente << clave_texto;
        fuente.close();

        // Paso 2: Codificar el archivo temporal
        if (metodo == 1) {
            codificar_primer_metodo(clave_fuente_txt, clave_codificada_temp, n);
        } else if (metodo == 2) {
            codificar_segundo_metodo(clave_fuente_txt, clave_codificada_temp, n);
        }

        ofstream sudo_out(archivo_sudo_bin, ios::app | ios::binary);
        ifstream clave_in(clave_codificada_temp, ios::in | ios::binary);

        if (!sudo_out.is_open() || !clave_in.is_open()) {
            cerr << "Error al abrir archivos para escribir en sudo.bin." << endl;
            continue;
        }

        clave_in.seekg(0, ios::end);
        long size = clave_in.tellg();
        clave_in.seekg(0, ios::beg);

        char* buffer = new char[size];
        clave_in.read(buffer, size);

        sudo_out.write(buffer, size);

        delete[] buffer;

        sudo_out << '\n'; // Separador
        sudo_out.close();
        clave_in.close();

        remove(clave_fuente_txt);
        remove(clave_codificada_temp);

        cout << "Clave " << clave_texto << " registrada." << endl;
    }
}
bool validarAccesoAdmin(int n, int metodo, const string& clave_ingresada) {
    const char* archivo_sudo_bin = "sudo.bin";
    const char* clave_ingresada_temp = "clave_ingresada_temp.txt";
    const char* clave_codificada_temp = "clave_codificada_temp.bin";


    ofstream temp_in(clave_ingresada_temp);
    temp_in << clave_ingresada;
    temp_in.close();

    // 1. Codificar la clave ingresada por el usuario
    // ... (escritura de clave_ingresada_temp.txt) ...

    if (metodo == 1) {
        codificar_primer_metodo(clave_ingresada_temp, clave_codificada_temp, n);
    } else if (metodo == 2) {
        codificar_segundo_metodo(clave_ingresada_temp, clave_codificada_temp, n);
    }

    ifstream temp_file(clave_codificada_temp, ios::binary | ios::ate);
    if (!temp_file.is_open()) {
        remove(clave_ingresada_temp);
        return false;
    }

    long size_temp = temp_file.tellg();
    if (size_temp <= 0) {
        temp_file.close();
        remove(clave_ingresada_temp);
        remove(clave_codificada_temp);
        return false;
    }

    temp_file.seekg(0, ios::beg);
    char* buffer_temp = new char[size_temp];
    temp_file.read(buffer_temp, size_temp);
    temp_file.close();

    ifstream sudo_file(archivo_sudo_bin, ios::binary);
    if (!sudo_file.is_open()) {
        delete[] buffer_temp;
        return false;
    }

    bool son_iguales = false;

    while (sudo_file.peek() != EOF) {
        char* buffer_almacenado = new char[size_temp];

        if (sudo_file.read(buffer_almacenado, size_temp)) {
            if (memcmp(buffer_almacenado, buffer_temp, size_temp) == 0) {
                son_iguales = true;
                delete[] buffer_almacenado;
                break;
            }
        }
        sudo_file.clear();

        delete[] buffer_almacenado;
        sudo_file.seekg(1, ios::cur);

        if (sudo_file.eof()) break;
    }

    sudo_file.close();
    delete[] buffer_temp;
    remove(clave_ingresada_temp);
    remove(clave_codificada_temp);

    return son_iguales;
}


void logicaAccesoAdministrador(int n, int metodo) {

    string usuario_ingresado;
    string clave_ingresada;


    cout << "\n--- ACCESO ADMINISTRADOR: VALIDACION ---" << endl;
    cout << "Usuario: ";
    cin >> usuario_ingresado;
    cout << "Clave: ";
    cin >> clave_ingresada;

    if (validarAccesoAdmin(n, metodo, clave_ingresada)) {
        cout << "\n*** ACCESO PERMITIDO. Bienvenido " << usuario_ingresado << ". ***" << endl;

    } else {
        cout << "\n*** ACCESO DENEGADO. Usuario o clave incorrectos. ***" << endl;
    }
}
