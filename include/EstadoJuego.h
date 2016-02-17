#ifndef ESTADOJUEGO_H
#define ESTADOJUEGO_H
#include <iostream>
#include <vector>

using namespace std;

class EstadoJuego
{
public:

    virtual ~EstadoJuego() {}

    virtual void actualizar() = 0;
    virtual void renderizar() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual void resume() {}

    virtual std::string getEstadoID() const = 0;

protected:

    EstadoJuego() : bLoadingComplete(false), bSaliendo(false)
    {
    }

    bool bLoadingComplete;
    bool bSaliendo;

    std::vector<std::string> vTexturaIDLista;
};

#endif // ESTADOJUEGO_H
