#include "EstadoMainMenu.h"
#include <iostream>
#include "AdministradorTexturas.h"
#include "Juego.h"
#include <BotonMenu.h>
#include <EstadoPlay.h>
#include <ManejadorEntrada.h>
#include "EstadoParser.h"
#include <assert.h>

const std::string EstadoMainMenu::s_menuID = "MENU";

// Callbacks
void EstadoMainMenu::s_menuToPlay()
{
    ElJuego::Instancia()->getMaquinaEstadoJuego()->cambiarEstado(new EstadoPlay());
}

void EstadoMainMenu::s_salirDeMenu()
{
    ElJuego::Instancia()->salir();
}

// end callbacks

void EstadoMainMenu::actualizar()
{
	if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_SPACE))
	{
		s_menuToPlay();
	}
    if(!vObjetosJuego.empty())
    {
			for(int i = 0; i < vObjetosJuego.size(); i++)
			{
				if(vObjetosJuego[i] != 0)
				{
					vObjetosJuego[i]->actualizar();
				}
			}
    }
}

void EstadoMainMenu::renderizar()
{
    if(bLoadingComplete && !vObjetosJuego.empty())
    {
        for(int i = 0; i < vObjetosJuego.size(); i++)
        {
            vObjetosJuego[i]->dibujar();
        }
    }
}

bool EstadoMainMenu::onEnter()
{
    // parsear el estado
    EstadoParser estadoParser;
    estadoParser.parseEstado("res/pacman.xml", s_menuID, &vObjetosJuego, &vTexturaIDLista);

    vCallBacks.push_back(0);
    vCallBacks.push_back(s_menuToPlay);
    vCallBacks.push_back(s_salirDeMenu);

    // set the callbacks for menu items
    setCallbacks(vCallBacks);

    bLoadingComplete = true;
    std::cout << "entrando a MenuState\n";
    return true;
}

bool EstadoMainMenu::onExit()
{
    bSaliendo = true;

    // limpiar los objetos juego
    if(bLoadingComplete && !vObjetosJuego.empty())
    {
		vObjetosJuego.back()->limpiar();
		vObjetosJuego.pop_back();
    }

	vObjetosJuego.clear();

    // reiniciar el manejador de entrada
    ManejadorDeEntrada::Instancia()->reiniciar();

    std::cout << "saliendo de MenuState\n";
    return true;
}

void EstadoMainMenu::setCallbacks(const std::vector<Callback>& callbacks)
{
    // ir a traves de los objetos de juego
    if(!vObjetosJuego.empty())
    {
        for(int i = 0; i < vObjetosJuego.size(); i++)
        {
            // Si son del tipo boton menu entonces asignar un callback basado en el id pasado desde el archivo
            if(dynamic_cast<BotonMenu*>(vObjetosJuego[i]))
            {
                BotonMenu* pBoton = dynamic_cast<BotonMenu*>(vObjetosJuego[i]);
                pBoton->setCallback(callbacks[pBoton->getCallbackID()]);
            }
        }
    }
}
