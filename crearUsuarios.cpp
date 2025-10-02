// Para remove()
#include "librerias.h"

bool existeCedula(const string& cedula) {
    ifstream txt_in("usuarios.txt");
    if (!txt_in.is_open()) {
        return false;
    }

    string linea;
    while (getline(txt_in, linea)) {
        stringstream ss(linea);
        string cedula_almacenada;

        getline(ss, cedula_almacenada, ',');

        if (cedula_almacenada == cedula) {
            txt_in.close();
            return true;
        }
    }

    txt_in.close();
    return false;
}


void registrarUsuarioCajero(int n, int metodo) {
    string cedula, clave, saldo_str;

    const char* archivo_usuarios_txt = "usuarios.txt";
    const char* archivo_usuarios_bin = "usuarios.bin";

    const char* registro_fuente_txt = "registro_usuario_temp.txt";
    const char* registro_codificado_temp = "registro_codificado_temp.bin";

    cout << "\n--- REGISTRO DE NUEVO USUARIO ---" << endl;
    cout << "Ingrese Cedula: ";
    cin >> cedula;

    if (existeCedula(cedula)) {
        throw string("\n*** ERROR (Registro): La cedula ") + cedula + " ya se encuentra registrada. ***";
    }

    cout << "Ingrese Clave: ";
    cin >> clave;
    cout << "Ingrese Saldo Inicial (COP): ";
    cin >> saldo_str;

    string registro_completo = cedula + "," + clave + "," + saldo_str;

    ofstream txt_out(archivo_usuarios_txt, ios::out | ios::app);
    if (!txt_out.is_open()) {
        throw string("Error: No se pudo abrir usuarios.txt para escritura.");
    }
    txt_out << registro_completo << "\n";
    txt_out.close();

    ofstream fuente(registro_fuente_txt);
    if (!fuente.is_open()) {
        throw string("Error: No se pudo crear archivo temporal para cifrado.");
    }
    fuente << registro_completo;
    fuente.close();

    if (metodo == 1) {
        codificar_primer_metodo(registro_fuente_txt, registro_codificado_temp, n);
    } else if (metodo == 2) {
        codificar_segundo_metodo(registro_fuente_txt, registro_codificado_temp, n);
    }

    ofstream bin_out(archivo_usuarios_bin, ios::out | ios::app | ios::binary);
    ifstream registro_in(registro_codificado_temp, ios::in | ios::binary);

    if (!bin_out.is_open() || !registro_in.is_open()) {
        remove(registro_fuente_txt);
        remove(registro_codificado_temp);
        throw string("Error al abrir archivos para escribir en usuarios.bin.");
    }

    registro_in.seekg(0, ios::end);
    long size = registro_in.tellg();
    registro_in.seekg(0, ios::beg);

    char* buffer = new char[size];
    registro_in.read(buffer, size);

    bin_out.write(buffer, size);

    delete[] buffer;
    registro_in.close();

    bin_out << '\n';
    bin_out.close();

    remove(registro_fuente_txt);
    remove(registro_codificado_temp);

    cout << "Usuario " << cedula << " registrado en usuarios.txt (texto) y usuarios.bin (encriptado)." << endl;
}
