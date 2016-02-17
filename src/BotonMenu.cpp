#include "BotonMenu.h"
#include "ManejadorEntrada.h"

BotonMenu::BotonMenu() : ObjetoPacman(), callback(0), bLiberado(true)
{
}

void BotonMenu::cargar(std::unique_ptr<CargadorParametros> const &pParametros)
{
    ObjetoPacman::cargar(std::move(pParametros));
    callbackID = pParametros->getCallbackID();
    frameActual = MOUSE_OUT;
}

void BotonMenu::dibujar()
{
    ObjetoPacman::dibujar();
}

void BotonMenu::actualizar()
{
    Vector2D* pMousePos = ManejadorDeEntrada::Instancia()->getMousePosition();

    if(pMousePos->getX() < (posicion.getX() + ancho) && pMousePos->getX() > posicion.getX()
       && pMousePos->getY() < (posicion.getY() + altura) && pMousePos->getY() > posicion.getY())
    {
        if(ManejadorDeEntrada::Instancia()->getMouseButtonState(LEFT) && bLiberado)
        {
            frameActual = CLICKED;

            if(callback != 0)
            {
                callback();
            }

            bLiberado = false;
        }
        else if(!ManejadorDeEntrada::Instancia()->getMouseButtonState(LEFT))
        {
            bLiberado = true;
            frameActual = MOUSE_OVER;
        }
    }
    else
    {
        frameActual = MOUSE_OUT;
    }
}

void BotonMenu::limpiar()
{
    ObjetoPacman::limpiar();
}
