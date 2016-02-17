#include "MaquinaEstadoJuego.h"
#include <iostream>

void MaquinaEstadoJuego::limpiar()
{
    if (!vEstadosJuego.empty())
    {
        vEstadosJuego.back()->onExit();
        delete vEstadosJuego.back();
        vEstadosJuego.clear();
    }
}

void MaquinaEstadoJuego::actualizar()
{
    if(!vEstadosJuego.empty())
    {
        vEstadosJuego.back()->actualizar();
	}
}

void MaquinaEstadoJuego::renderizar()
{
    if(!vEstadosJuego.empty())
    {
        vEstadosJuego.back()->renderizar();
    }
}

void MaquinaEstadoJuego::pushEstado(EstadoJuego *pEstado)
{
    vEstadosJuego.push_back(pEstado);
    vEstadosJuego.back()->onEnter();
}

void MaquinaEstadoJuego::popEstado()
{
    if(!vEstadosJuego.empty())
    {
        vEstadosJuego.back()->onExit();
        vEstadosJuego.pop_back();
    }

    vEstadosJuego.back()->resume();
}

void MaquinaEstadoJuego::cambiarEstado(EstadoJuego *pEstado)
{
    if(!vEstadosJuego.empty())
    {
        if(vEstadosJuego.back()->getEstadoID() == pEstado->getEstadoID())
        {
            return; // do nothing
        }

		vEstadosJuego.back()->onExit();
		vEstadosJuego.pop_back();
    }

	// initialise it
    pEstado->onEnter();

    // push back our new state
    vEstadosJuego.push_back(pEstado);
}
