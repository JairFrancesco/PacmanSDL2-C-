#include "ObjetoPacman.h"
#include "AdministradorTexturas.h"
#include "Juego.h"

ObjetoPacman::ObjetoPacman() :    ObjetoJuego(),
                                    velocidadMovimiento(0),
                                    tiempoMuriendo(0),
                                    contadorMuriendo(0),
                                    bSonidoMuerteJugador(false)
{
}

void ObjetoPacman::cargar(std::unique_ptr<CargadorParametros> const &pParametros)
{
    // get posicion
    posicion = Vector2D(pParametros->getX(),pParametros->getY());

    // get dibujando variables
    ancho = pParametros->getAncho();
    altura = pParametros->getAltura();
    texturaID = pParametros->getTexturaID();
    numFrames = pParametros->getNumFrames();
}

// draw el objeto para la pantalla
void ObjetoPacman::dibujar()
{
    AdministradorDeTexturas::Instancia()->dibujarFrame(texturaID, (Uint32)posicion.getX(), (Uint32)posicion.getY(),
                                          ancho, altura, filaActual, frameActual, ElJuego::Instancia()->getRenderizador(),
                                           angulo, alpha);
}

// aplicar la velocidad a la posicion actual
void ObjetoPacman::actualizar()
{
    posicion += velocidad;
    frameActual = int(((SDL_GetTicks() / (1000 / 3)) % numFrames));
}

void ObjetoPacman::haciendoAnimacion()
{
    frameActual = int(((SDL_GetTicks() / (1000/ 10)) % numFrames));

    if(contadorMuriendo == tiempoMuriendo)
    {
        bMuerto = true;
    }
    contadorMuriendo++;
}
