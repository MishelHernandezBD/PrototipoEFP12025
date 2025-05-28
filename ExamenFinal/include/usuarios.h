#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
using namespace std;

class usuarios
{
    public:
        usuarios();
        bool loginUsuarios();
        bool registrarUsuario();
        bool consultarUsuarios();
        bool modificarUsuario();
        bool eliminarUsuario();
        bool buscar(string user, string passw);
        string getNombre();
        void setNombre(string nombre);

    protected:

    private:
        string id;
        string name;
        string pass;
};

#endif // USUARIOS_H
