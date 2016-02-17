#include "EstadoGameOver.h"
#include "EstadoMainMenu.h"
#include "EstadoPlay.h"
#include "AdministradorTexturas.h"
#include "GraficoAnimado.h"
#include "Juego.h"
#include "BotonMenu.h"
#include "ManejadorEntrada.h"
#include "EstadoParser.h"

const std::string EstadoGameOver::s_gameOverID = "GAMEOVER";

void EstadoGameOver::s_gameOverToMain()
{
    ElJuego::Instancia()->getMaquinaEstadoJuego()->cambiarEstado(new EstadoMainMenu());
}

void EstadoGameOver::s_restartPlay()
{
    ElJuego::Instancia()->getMaquinaEstadoJuego()->cambiarEstado(new EstadoPlay());
}

void EstadoGameOver::actualizar()
{
    if(bLoadingComplete && !vObjetosJuego.empty())
    {
        for(int i = 0; i < vObjetosJuego.size(); i++)
        {
            vObjetosJuego[i]->actualizar();
        }
    }
}

void EstadoGameOver::renderizar()
{
    if(bLoadingComplete && !vObjetosJuego.empty())
    {
        for(int i = 0; i < vObjetosJuego.size(); i++)
        {
            vObjetosJuego[i]->dibujar();
        }
    }
}

bool EstadoGameOver::onEnter()
{
    // parse the state
    EstadoParser estadoParser;
    estadoParser.parseEstado("res/pacman.xml", s_gameOverID, &vObjetosJuego, &vTexturaIDLista);

    vCallBacks.push_back(0);
    vCallBacks.push_back(s_gameOverToMain);
    vCallBacks.push_back(s_restartPlay);

    // set the callbacks for menu items
    setCallbacks(vCallBacks);

    bLoadingComplete = true;

    std::cout << "entrando al estado game over EstadoGameOver\n";
    return true;
}

bool EstadoGameOver::onExit()
{
    if(bLoadingComplete && !vObjetosJuego.empty())
    {
        for(int i = 0; i < vObjetosJuego.size(); i++)
        {
            vObjetosJuego[i]->limpiar();
            delete vObjetosJuego[i];
        }

        vObjetosJuego.clear();
    }

    std::cout << vObjetosJuego.size();

    // clear the texture manager
    for(int i = 0; i < vTexturaIDLista.size(); i++)
    {
        AdministradorDeTexturas::Instancia()->limpiarDelMapaTexturas(vTexturaIDLista[i]);
    }

    ManejadorDeEntrada::Instancia()->reiniciar();

    std::cout << "saliendo del EstadoGameOver\n";
    return true;
}

void EstadoGameOver::setCallbacks(const std::vector<Callback>& vCallbacks)
{
    // go through the game objects
    for(int i = 0; i < vObjetosJuego.size(); i++)
    {
        // if they are of type MenuButton then assign a callback based on the id passed in from the file
        if(dynamic_cast<BotonMenu*>(vObjetosJuego[i]))
        {
            BotonMenu* pBoton = dynamic_cast<BotonMenu*>(vObjetosJuego[i]);
            pBoton->setCallback(vCallbacks[pBoton->getCallbackID()]);
        }
    }
}
