#include "GraficoAnimado.h"

using namespace std;

GraficoAnimado::GraficoAnimado() : ObjetoPacman()
{

}

void GraficoAnimado::cargar(std::unique_ptr<CargadorParametros> const &pParametros)
{
    ObjetoPacman::cargar(pParametros);
    velocidadAnimacion = pParametros->getVelocidadAnimacion();
}

void GraficoAnimado::dibujar()
{
    ObjetoPacman::dibujar();
}

void GraficoAnimado::actualizar()
{
    frameActual = int(((SDL_GetTicks() / (1000 / velocidadAnimacion)) % numFrames));
}

void GraficoAnimado::limpiar()
{
    ObjetoPacman::limpiar();
}
