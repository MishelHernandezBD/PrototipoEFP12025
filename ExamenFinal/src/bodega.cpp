#include "bitacora.h"
#include "bodega.h"
#include "usuarios.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<conio.h>
#include<iomanip>
using namespace std;

extern usuarios usuariosrRegistrado;

void bodega::menu()
{
    int choice;
    char x;
    do {
        system("cls");
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t|  SISTEMA GESTION Bodega |"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t 1. Ingreso bodega"<<endl;
        cout<<"\t\t\t 2. Despliegue bodega"<<endl;
        cout<<"\t\t\t 3. Modifica bodega"<<endl;
        cout<<"\t\t\t 4. Busca bodega"<<endl;
        cout<<"\t\t\t 5. Borra bodega"<<endl;
        cout<<"\t\t\t 6. Reportes bodega"<<endl;
        cout<<"\t\t\t 7. Salida"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\tOpcion a escoger:[1/2/3/4/5/6]"<<endl;
        cout<<"\t\t\tIngresa tu Opcion: ";
        cin>>choice;

        switch(choice)
        {
        case 1:
            do {
                insertar(); // Agregar nuevo acreedor
                cout<<"\n\t\t\t Agrega otro registro (Y/N): ";
                cin>>x;
            } while(x=='y'||x=='Y');
            break;
        case 2:
            desplegar(); // Mostrar todos
            break;
        case 3:
            modificar(); // Editar informaci�n
            break;
        case 4:
            buscar(); // Buscar bodega por ID
            break;
        case 5:
            borrar(); // Eliminar bodega por ID
            break;
        case 6:
            reporte(); // Mostrar reporte tabular
            break;
        case 7:
            break;
        default:
            cout<<"\n\t\t\t Opcion invalida...Por favor prueba otra vez..";
            cin.get();
        }
    } while(choice!= 7);
}

void bodega::insertar()
{
    system("cls");
    fstream file;
    char confirmar;
    try{
        do {
            cout << "\n----------------------------------------------------------------------------------";
            cout << "\n-------------------------------- Agregar Registro --------------------------------\n";

            cout << "\t\t\tIngresa ID       : ";
            cin >> id;
            cout << "\t\t\tIngresa el id del tipo     : ";
            cin >> idTipoBodega;
            cout << "\t\t\tIngresa Nombre   : ";
            cin >> nombre;
            cout << "\t\t\tIngresa direccion : ";
            cin >> direccion;
            cout << "\t\t\tIngresa estado  : ";
            cin >> estado;

            cout << "\nResumen de la informaci�n ingresada:\n";
            cout << "\t\t\tID        : " << id << endl;
            cout << "\t\t\tId tipo   : " << idTipoBodega << endl;
            cout << "\t\t\tNombre    : " << nombre << endl;
            cout << "\t\t\tDireccion : " << direccion << endl;
            cout << "\t\t\tEstado    : " << estado << endl;

            cout << "\n Esta seguro de guardar esta informacion? (S/N): ";
            cin >> confirmar;

            if (confirmar == 's' || confirmar == 'S') {
                file.open("bodega.txt", ios::app | ios::out);
                if (!file.is_open()) throw runtime_error ("No se pudo abrir el archivo"); //Eror en tiempo de ejecucion
                file << left << setw(15) << id
                     << left << setw(15) << idTipoBodega
                     << left << setw(15) << nombre
                     << left << setw(15) << direccion
                     << left << setw(15) << estado << "\n";
                file.close();

                bitacora auditoria;
                auditoria.insertar(usuariosrRegistrado.getNombre(), "8040", "Ins"); // Insertar nuevo Registro
                cout << "\nRegistro guardado correctamente.\n";
            } else {
                cout << "\nVolvamos a ingresar los datos...\n";
            }

        } while (confirmar != 's' && confirmar != 'S');
    } catch (const exception& e) {
        cout << "\n\t\t\t Error ocurrido: " << e.what() << endl;
    }
}

// Muestra todos los acreedores registrados
void bodega::desplegar()
{
    system("cls");
    fstream file;
    int total=0;
    cout<<"\n------------------------ Lista de Registro ------------------------"<<endl;
    file.open("bodega.txt", ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...\n";
        system("pause");
    }
    else {
        file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        while(!file.eof()) {
            total++;
            cout<<"\n\t\t\tID      : "<<id<<endl;
            cout<<"\t\t\t ID tipo  : "<<idTipoBodega<<endl;
            cout<<"\t\t\t Nombre   : "<<nombre<<endl;
            cout<<"\t\t\t Direccion: "<<direccion<<endl;
            cout<<"\t\t\t Estado   : "<<estado<<endl;

            file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        }
        if(total==0){
            cout<<"\n\t\t\tNo hay informacion...";
        }
        system("pause");
    }
    file.close();
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8041", "MA"); // Mostrar Acreedor
}

// Permite modificar la informaci�n de un acreedor ya existente
void bodega::modificar()
{
    system("cls");
    fstream file, file1;
    string acreedor_id;
    int found=0;
    cout<<"\n---------------- Modificar   Registro ----------------"<<endl;
    file.open("bodega.txt", ios::in);
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        system("pause");
        file.close();
    }
    else {
        cout<<"\nIngrese ID del Acreedor que quiere modificar: ";
        cin>>acreedor_id;
        file1.open("temporal.txt", ios::app | ios::out);

        file >> id >> idTipoBodega >> nombre >> direccion >> estado;

        while(!file.eof())
        {
            if(acreedor_id != id) {
                file1<<left<<setw(15)<< id << left<<setw(15)<< idTipoBodega <<left<<setw(15)<< nombre <<left << setw(15)
                << direccion << left << setw(15)<< estado << "\n";
            }
            else {
                cout<<"\t\t\tIngrese Id  : ";
                cin>>id;
                cout<<"\t\t\tIngrese Id tipo    : ";
                cin>>idTipoBodega;
                cout<<"\t\t\tIngrese Nombre  : ";
                cin>>nombre;
                cout<<"\t\t\tDireccion: ";
                cin >>direccion;
                cout<<"\t\t\tIngrese Estado     : ";
                cin>>estado;

                file1<<left<<setw(15)<< id << left<<setw(15)<< idTipoBodega <<left<<setw(15)<< nombre <<left << setw(15)
                << direccion << left << setw(15)<< estado << "\n";
                found++;
            }
            file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        }
        if(found==0){
            cout<<"\n\t\t\tAcreedor no encontrado...";
            system("pause");
        }

        file1.close();
        file.close();
        remove("bodega.txt");
        rename("temporal.txt","bodega.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8042", "Act"); // Actualizar Acreedor
    }
}

// Permite buscar un acreedor por ID y mostrar su informaci�n
void bodega::buscar()
{
    system("cls");
    fstream file;
    int found=0;

    file.open("bodega.txt", ios::in);
    cout<<"\n---------------- Buscar Registro ----------------"<<endl;
    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        file.close();
    } else {
        string acreedor_id;
        cout<<"\nIngrese ID del Acreedor que quiere buscar : ";
        cin>>acreedor_id;
        file >> id >> idTipoBodega >> nombre >> direccion >> estado;

        while(!file.eof()) {
            if(acreedor_id==id) {
                cout<<"\n\t\t\tID      : "<<id<<endl;
                cout<<"\t\t\t ID tipo  : "<<idTipoBodega<<endl;
                cout<<"\t\t\t Nombre   : "<<nombre<<endl;
                cout<<"\t\t\t Direccion: "<<direccion<<endl;
                cout<<"\t\t\t Estado   : "<<estado<<endl;
                found++;
            }
            file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        }
        if(found==0) cout<<"\n\t\t\tAcreedor no encontrado...\n";
        system("pause");
        file.close();
    }
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8043", "BAR"); // Buscar Acreedor
}

// Elimina un acreedor seg�n su ID
void bodega::borrar()
{
    system("cls");
    fstream file, file1;
    string acreedor_id;
    int found=0;
    cout<<"\n---------------- Borrar Registro ----------------"<<endl;
    file.open("bodega.txt", ios::in);

    if(!file) {
        cout<<"\n\t\t\tNo hay informacion...";
        system("pause");
        file.close();
    }
    else {
        cout<<"\n Ingrese el Id del Acreedor que quiere borrar: ";
        cin>>acreedor_id;
        file1.open("temporal.txt",ios::app | ios::out);
        file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        while(!file.eof()) {
            if(acreedor_id!= id) {
                file1<<left<<setw(15)<< id << left<<setw(15)<< idTipoBodega <<left<<setw(15)<< nombre <<left << setw(15)
                << direccion << left << setw(15)<< estado << "\n";
            } else {
                found++;
                cout << "\nAcreedor borrado exitosamente\n";
                system("pause");
            }
            file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        }
        if(found==0) {
            cout<<"\nAcreedor no encontrado\n";
            system("pause");
        }
        file1.close();
        file.close();
        remove("bodega.txt");
        rename("temporal.txt","bodega.txt");
        bitacora auditoria;
        auditoria.insertar(usuariosrRegistrado.getNombre(), "8044", "DAR"); // Eliminar Acreedor de bit�cora
    }
}

// Genera un reporte tabular con todos los acreedores y guarda una copia en reportes.txt
void bodega::reporte(){
    system("cls");
    fstream file, reporteFile;
    int found = 0;

    cout<<"\n----------------------------- Reporte de Registro -----------------------------\n"<<endl;
    file.open("bodega.txt", ios::in);
    reporteFile.open("reportes.txt", ios::app | ios::out); // nuevo archivo

    if (!file) {
        cout << "\n\t\t\tNo hay informacion ...\n";
        reporteFile << "No hay informacion en acreedor.txt\n\n";
    }
    else {
        cout << left << setw(15) << "ID" << setw(15) << "Id Tipo"  << setw(15) << "Nombre"
             << setw(15) << "Dirreccion" << setw(15) << "Estado" << endl;
        cout << "----------------------------------------------------------------------------------\n";

        reporteFile << "----------------------------- REPORTE DE ACREEDORES -----------------------------\n";
        reporteFile << left << setw(15) << "ID" << setw(15) << "Id Tipo"  << setw(15) << "Nombre"
                    << setw(15) << "Direccion" << setw(15) << "Estado" << "\n";
        reporteFile << "----------------------------------------------------------------------------------\n";

        file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        while (!file.eof()) {
            found++;
            cout << left << setw(15) << id << setw(15) << idTipoBodega << setw(15)
                 << nombre << setw(15) << direccion << setw(15) << estado << endl;

            reporteFile << left << setw(15) << id << setw(15) << idTipoBodega << setw(15)
                 << nombre << setw(15) << direccion << setw(15) << estado << endl;

            file >> id >> idTipoBodega >> nombre >> direccion >> estado;
        }

        reporteFile << "----------------------------------------------------------------------------------\n\n";

        if(found==0){
            cout<<"\n\t\t\tNo hay registros registrados...\n";
            reporteFile << "No hay registros guardados...\n\n";
        }
    }

    cout << endl;
    file.close();
    reporteFile.close();
    system("pause");
    bitacora auditoria;
    auditoria.insertar(usuariosrRegistrado.getNombre(), "8035", "RAR"); // Reporte Acreedor
}
