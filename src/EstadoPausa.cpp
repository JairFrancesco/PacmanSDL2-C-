#include "EstadoPausa.h"
#include "EstadoMainMenu.h"
#include "EstadoPlay.h"
#include "AdministradorTexturas.h"
#include "Juego.h"
#include "BotonMenu.h"
#include "ManejadorEntrada.h"
#include "EstadoParser.h"

const std::string EstadoPausa::s_pauseID = "PAUSE";

void EstadoPausa::s_pauseToMain()
{
    ElJuego::Instancia()->getMaquinaEstadoJuego()->cambiarEstado(new EstadoMainMenu());
}

void EstadoPausa::s_resumePlay()
{
    ElJuego::Instancia()->getMaquinaEstadoJuego()->popEstado();
}

void EstadoPausa::actualizar()
{
    if(bLoadingComplete && !vObjetosJuego.empty())
    {
        for(int i = 0; i < vObjetosJuego.size(); i++)
        {
            vObjetosJuego[i]->actualizar();
        }
    }
}

void EstadoPausa::renderizar()
{
    if(bLoadingComplete && !vObjetosJuego.empty())
    {
        for(int i = 0; i < vObjetosJuego.size(); i++)
        {
            vObjetosJuego[i]->dibujar();
        }
    }
}

bool EstadoPausa::onEnter()
{
    EstadoParser estadoParser;
    estadoParser.parseEstado("res/pacman.xml", s_pauseID, &vObjetosJuego, &vTexturaIDLista);

    vCallBacks.push_back(0);
    vCallBacks.push_back(s_pauseToMain);
    vCallBacks.push_back(s_resumePlay);

    setCallbacks(vCallBacks);

    bLoadingComplete = true;

    std::cout << "entrando a EstadoPausa\n";
    return true;
}

bool EstadoPausa::onExit()
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
    // limpiar el administrador de texturas
    for(int i = 0; i < vTexturaIDLista.size(); i++)
    {
        AdministradorDeTexturas::Instancia()->limpiarDelMapaTexturas(vTexturaIDLista[i]);
    }
    ManejadorDeEntrada::Instancia()->reiniciar();

    std::cout << "Saliendo de EstadoPausa\n";
    return true;
}

void EstadoPausa::setCallbacks(const std::vector<Callback>& vCallbacks)
{
    // go through the game objects
    if(!vObjetosJuego.empty())
    {
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
}
