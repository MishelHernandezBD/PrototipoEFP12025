#ifndef BODEGA_H
#define BODEGA_H

#include<iostream>
using namespace std;

class bodega
{
    public:
        bodega();
        void menu();
        void insertar();
        void desplegar();
        void modificar();
        void buscar();
        void reporte();
        void borrar();

    private:
        string id,idTipoBodega,nombre,direccion,estado;

#endif // BODEGA_H
