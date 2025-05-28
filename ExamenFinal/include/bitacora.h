//Documentado por Britany Hernandez 28/05/2025 9959-24-4178
//Declaracion de la clase bitacora que ayuda a registrar acciones en el sistema
//Se encarga de almacenar la informacion relacionada con las acciones del usuario
//especificando el nombre de este, la accion ejecutada, la fecha y la hora de la accion
#ifndef BITACORA_H
#define BITACORA_H

#include<iostream>
using std::string;

class bitacora
{
    public:
        bitacora();//Constructor de la clase
        void menu();//Menu de gestion de la bitacora
        //Agrega un nuevo registro en la bitacora
        void insertar(string nombre, string aplicacion, string accion);
        void desplegar();//Muestra todos los registros de la bitacora
        bool backupBitacora();

    protected:

    private:
        string nombre; //Nombre del usuario registrado
        string aplicacion;//Nombre de la aplicacion usada
        string accion;//Nombre de la accion realizada
        string fecha;//Fecha y hora de la accion realizada
};

#endif // BITACORA_H

