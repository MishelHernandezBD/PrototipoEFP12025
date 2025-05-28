

#include "catalogos.h"
#include "bodega.h"
#include "usuarios.h"
#include "bodega.h"

#include <iostream>
using namespace std;

extern usuarios usuariosrRegistrado;

//Declaracion de objetos
bodega bod;

catalogos::catalogos()
{

}

void catalogos::menuCatalogos(){
    int opciones;
    do{
        system("cls"); // Limpia la pantalla
        cout << "\t\t\tUsuario en linea: " << usuariosrRegistrado.getNombre() << "\n" << endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout<<"\t\t\t |   Menu de catalogos        |"<<endl;
        cout<<"\t\t\t-------------------------------"<<endl;
        cout <<"\t\t\t1. Catalogo de Bodega" << endl;
        cout <<"\t\t\t2. Volver al menu principal" << endl;

        cout<<"\t\t Opcion a escoger:[1/2]"<<endl;
        cout << "\n\t\t Ingrese una opcion: ";
        cin >> opciones;

        switch (opciones) {
            case 1:
                bod.menu();
                break;
            case 2:
                break;
            default:
                cout << "n\t\tOpci�n no v�lida. Intente de nuevo" << endl;
                system("pause");
        }
    } while (opciones != 2); // Repite el men� hasta que el usuario quiera salir
}
