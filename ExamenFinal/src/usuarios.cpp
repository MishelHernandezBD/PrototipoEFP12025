#include "usuarios.h"
#include "bitacora.h"
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <sstream>  // Agregado para procesar cada línea
#include <iostream>
#include <cstring>
#include "bitacora.h"
#include <limits>//para que se lea bien la limpiada del buffer de entrada

using namespace std;

// Aquí lo hice con estructuras, pero solo este. Estructura para almacenamiento binario
struct UsuarioBin {
    char id[20];
    char name[50];
    char pass[50];
};

usuarios::usuarios()
{
    // Constructor
}

usuarios::~usuarios()
{
    // Destructor
}

//INICIAN LOS CRUD

//Iniciar sesión de usuarios
bool usuarios::loginUsuarios() {
    string usuario, contra;
    int intentosIngreso = 0;
    bool ingresa = false;

    do {
        system("cls");
        cout << "\n\t\t-------------------------" << endl;
        cout << "\t\t   INGRESO DE USUARIOS   " << endl;
        cout << "\t\t-------------------------" << endl << endl;

        cout << "\t\tUsuario: ";
        getline(cin, usuario);

        cout << "\n\t\tContraseña: ";
        char caracter;
        caracter = getch();
        contra = "";

        while (caracter != 13) {
            if (caracter != 8) {
                contra.push_back(caracter);
                cout << "*";
            }
            else {
                if (contra.length() > 0) {
                    cout << "\b \b";
                    contra = contra.substr(0, contra.length() - 1);
                }
            }
            caracter = getch();
        }

        if (buscar(usuario, contra)) {
            ingresa = true;
        }
        else {
            cout << "\n\t\tEl Usuario y/o contraseña son incorrectos" << endl;
            bitacora auditoria;
            auditoria.insertar("usuario", "100", "LOGF"); //Login fallido
            cin.get();
            intentosIngreso++;
        }

    } while (ingresa == false && intentosIngreso < 3);

    if (ingresa == false) {
        cout << "\t\t\nIngreso denegado...\n\t\tUsuario y/o contraseña invalidos. Intentos agotados" << endl;
        bitacora auditoria;
        auditoria.insertar("usuario", "100", "LOGF");
        cin.get();
    }
    else {
        cout << "\t\t\n\nINGRESANDO AL SISTEMA..." << endl;
        system("pause");
        bitacora auditoria;
        name = usuario;
        auditoria.insertar(name, "100", "LOGS"); //Login Successful xdd
        cin.get();
    }

    return ingresa;
}

//Registrar nuevo usuario
bool usuarios::registrarUsuario() {
    string nuevoId, nuevoNombre, nuevaContra;

    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t   REGISTRO DE USUARIO   " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    cout << "\t\tIngrese ID: ";
    cin.ignore();
    getline(cin, nuevoId);

    cout << "\t\tIngrese Nombre: ";
    getline(cin, nuevoNombre);

    cout << "\t\tIngrese Contraseña: ";

    //contraseña ocualtado como en el login
    char caracter;
    caracter = getch();
    nuevaContra = "";
    while (caracter != 13) {
        if (caracter != 8) {
            nuevaContra.push_back(caracter);
            cout << "*";
        }
        else {
            if (nuevaContra.length() > 0) {
                cout << "\b \b";
                nuevaContra = nuevaContra.substr(0, nuevaContra.length() - 1);
            }
        }
        caracter = getch();
    }

    fstream file;
    file.open("Usuarios.bin", ios::app | ios::out | ios::binary);

    if (!file) {
        file.open("Usuarios.bin", ios::out | ios::binary);
        if (!file) {
            cout << "\n\t\tError al crear el archivo." << endl;
            system("pause");
            return false;
        }
    }

    // copia un número limitado de caracteres de una cadena a otra, protegiendo contra desbordamientos de buffer.
    // copiar de forma segura los datos del usuario a la estructura de almacenamiento
    UsuarioBin usuario;
    strncpy(usuario.id, nuevoId.c_str(), sizeof(usuario.id) - 1);
    strncpy(usuario.name, nuevoNombre.c_str(), sizeof(usuario.name) - 1); //Copia hasta un carácter menos que el tamaño del buffer
    strncpy(usuario.pass, nuevaContra.c_str(), sizeof(usuario.pass) - 1);
    usuario.id[sizeof(usuario.id) - 1] = '\0';
    usuario.name[sizeof(usuario.name) - 1] = '\0'; // Asegura manualmente que el último carácter sea NULL
    usuario.pass[sizeof(usuario.pass) - 1] = '\0';

    file.write(reinterpret_cast<char*>(&usuario), sizeof(UsuarioBin));
    file.close();

    //utilicé el reinterpret_cast del capitulo d c++, para convertir  convertir UsuarioBin en una secuencia de bytes crudos (char*) para poder escribirla en el archivo binario.

    cout << "\n\n\t\tUsuario registrado exitosamente!" << endl;

    bitacora auditoria;
    auditoria.insertar(name, "100", "INSERTUS"); // INSERTAR USUARIO

    return true;
}


//Consulta de todos los usuarios
//Lee y muestra los datos del archivo binario
bool usuarios::consultarUsuarios() {
    fstream file;
    UsuarioBin usuario;
    int total = 0; // Contador para verificar si hay datos

    system("cls");
    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t LISTADO DE USUARIOS " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    file.open("Usuarios.bin", ios::in | ios::binary);
    if (!file) {
        cout << "\n\t\tNo hay información disponible de usuarios..." << endl;
        system("pause");
        return false;
    }
    //leyendo el archivo
    while (file.read(reinterpret_cast<char*>(&usuario), sizeof(UsuarioBin))) {
        total++;
        cout << "\n\t\tID: " << usuario.id << endl;
        cout << "\t\tNombre: " << usuario.name << endl;
        cout << "\t\tContraseña: " << usuario.pass << endl;
    }
    system("pause");

    file.close();

    if (total == 0) {
        cout << "\n\t\tNo hay usuarios registrados..." << endl;
    }
    system("pause");

//Bitacora
    bitacora auditoria;
    auditoria.insertar(name, "100", "SRCH"); //search

    system("pause");
    return true;
}

//Modificar un usuario por medio del ID (Cambiar nombre y contraseña)
bool usuarios::modificarUsuario() {
    system("cls");
    fstream file, tempFile;
    string searchId;
    UsuarioBin usuario;
    bool found = false;

    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t MODIFICACIÓN DE USUARIO " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    cout << "\t\tIngrese ID del usuario a modificar: ";
    cin.ignore();
    getline(cin, searchId);

    file.open("Usuarios.bin", ios::in | ios::binary);
    if (!file) {
        cout << "\n\t\tNo hay información disponible..." << endl;
        return false;
    }
    system("cls");

    //Crear archivo temporal
    tempFile.open("Temp.bin", ios::out | ios::binary);

    //leer archivo original
    while (file.read(reinterpret_cast<char*>(&usuario), sizeof(UsuarioBin))) {
        if (searchId == string(usuario.id)) {
            found = true;
            //muestra los datos actuales para qu el usuario sepa q está modificando
            cout << "\n\t\tDatos actuales:" << endl;
            cout << "\t\tID: " << usuario.id << endl;
            cout << "\t\tNombre: " << usuario.name << endl;
            cout << "\t\tContraseña: " << usuario.pass << endl << endl;

            //solicita los nuevos datos
            string newName, newPass;
            cout << "\t\tNuevo nombre: ";
            getline(cin, newName);

            cout << "\t\tNueva contraseña: ";
            //el mismo coso para la contraseña
            char caracter;
            newPass = "";
            caracter = getch();
            while (caracter != 13) {
                if (caracter != 8) {
                    newPass.push_back(caracter);
                    cout << "*";
                } else {
                    if (!newPass.empty()) {
                        cout << "\b \b";
                        newPass.pop_back();
                    }
                }
                caracter = getch();
            }
            //guarda los datos en el archivo temporal
            strncpy(usuario.name, newName.c_str(), sizeof(usuario.name) - 1);
            strncpy(usuario.pass, newPass.c_str(), sizeof(usuario.pass) - 1);
            usuario.name[sizeof(usuario.name) - 1] = '\0';
            usuario.pass[sizeof(usuario.pass) - 1] = '\0';
        }
        tempFile.write(reinterpret_cast<char*>(&usuario), sizeof(UsuarioBin));
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("Usuarios.bin");
        rename("Temp.bin", "Usuarios.bin");
        cout << "\n\t\tUsuario modificado exitosamente!" << endl;
        bitacora auditoria;
        auditoria.insertar(name, "100", "UPDUS"); //update usuarios
        return true;
    }
    else {
        remove("Temp.bin");
        cout << "\n\t\tNo se encontró el usuario con ID: " << searchId << endl;
        return false;
    }
    system("cls");
}

//eliminar usuario por ID
bool usuarios::eliminarUsuario() {
    system("cls");
    fstream file, tempFile;
    string searchId;
    UsuarioBin usuario;
    bool found = false;

    cout << "\n\t\t-------------------------" << endl;
    cout << "\t\t ELIMINACIÓN DE USUARIO  " << endl;
    cout << "\t\t-------------------------" << endl << endl;

    cout << "\t\tIngrese ID del usuario a eliminar: ";
    cin.ignore();
    getline(cin, searchId);

    file.open("Usuarios.bin", ios::in | ios::binary);
    if (!file) {
        cout << "\n\t\tNo hay información disponible..." << endl;
        return false;
    }
    system("cls");

    tempFile.open("Temp.bin", ios::out | ios::binary);

    while (file.read(reinterpret_cast<char*>(&usuario), sizeof(UsuarioBin))) {
        if (searchId == string(usuario.id)) {
            found = true;
            cout << "\n\t\tDatos del usuario a eliminar:" << endl;
            cout << "\t\tID: " << usuario.id << endl;
            cout << "\t\tNombre: " << usuario.name << endl;
            cout << "\t\tContraseña: " << usuario.pass << endl << endl;

            char confirmar;
            cout << "\t\t¿Está seguro de eliminar este usuario? (S/N): ";
            cin >> confirmar;
            cin.ignore();

            if (toupper(confirmar) == 'S') {
                cout << "\n\t\tUsuario eliminado exitosamente!" << endl;
                bitacora auditoria;
                auditoria.insertar(name, "100", "DELUS");
                continue;
            }
            else {
                tempFile.write(reinterpret_cast<char*>(&usuario), sizeof(UsuarioBin));
                cout << "\n\t\tOperación cancelada." << endl;
            }
        }
        else {
            tempFile.write(reinterpret_cast<char*>(&usuario), sizeof(UsuarioBin));
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("Usuarios.bin");
        rename("Temp.bin", "Usuarios.bin");
        return true;
    }
    else {
        remove("Temp.bin");
        cout << "\n\t\tNo se encontró el usuario con ID: " << searchId << endl;
        return false;
    }
}

