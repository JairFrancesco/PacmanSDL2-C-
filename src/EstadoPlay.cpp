#include "EstadoPlay.h"
#include "EstadoGameOver.h"
#include "EstadoPausa.h"
#include "AdministradorTexturas.h"
#include "Juego.h"
#include "ManejadorEntrada.h"
#include "NivelParser.h"
#include "Nivel.h"


const std::string EstadoPlay::s_playID = "PLAY";

void EstadoPlay::actualizar()
{
    if(bLoadingComplete && !bSaliendo)
    {
        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_ESCAPE))
        {
            ElJuego::Instancia()->getMaquinaEstadoJuego()->pushEstado(new EstadoPausa());
        }
//
//        TheBulletHandler::Instance()->updateBullets();

        if(ElJuego::Instancia()->getVidasJugador() == 0)
        {
            ElJuego::Instancia()->getMaquinaEstadoJuego()->cambiarEstado(new EstadoGameOver());
        }

        if(pNivel != 0)
        {
            pNivel->actualizar();
        }
    }

}
void EstadoPlay::renderizar()
{
    if(bLoadingComplete)
    {
        if(pNivel != 0)
        {
            pNivel->renderizar();
        }
        AdministradorDeTexturas::Instancia()->dibujarFrame("lblVidas", 350, 580, 150, 75, 0, 0, ElJuego::Instancia()->getRenderizador(), 0.0, 255);
        AdministradorDeTexturas::Instancia()->dibujarFrame("lblPuntaje", 150, 580, 150, 75, 0, 0, ElJuego::Instancia()->getRenderizador(), 0.0, 255);
        for(int i = 0; i < ElJuego::Instancia()->getVidasJugador(); i++)
        {
            AdministradorDeTexturas::Instancia()->dibujarFrame("vidas", (i * 32) + 500, 600, 32, 32, 0, 0, ElJuego::Instancia()->getRenderizador(), 0.0, 255);
        }
    }

}
bool EstadoPlay::onEnter()
{
    ElJuego::Instancia()->setVidasJugador(3);

    NivelParser nivelParser;
    pNivel = nivelParser.parseNivel(ElJuego::Instancia()->getArchivosNivel()[ElJuego::Instancia()->getNivelActual() - 1].c_str());

//    AdministradorDeTexturas::Instancia()->cargar("bullet1.png", "bullet1", TheGame::Instance()->getRenderer());
//    AdministradorDeTexturas::Instancia()->cargar("bullet2.png", "bullet2", TheGame::Instance()->getRenderer());
//    AdministradorDeTexturas::Instancia()->cargar("bullet3.png", "bullet3", TheGame::Instance()->getRenderer());
    AdministradorDeTexturas::Instancia()->cargar("vidaslabel.png", "lblVidas", ElJuego::Instancia()->getRenderizador());
    AdministradorDeTexturas::Instancia()->cargar("puntajelabel.png", "lblPuntaje", ElJuego::Instancia()->getRenderizador());
    AdministradorDeTexturas::Instancia()->cargar("vidas.png", "vidas", ElJuego::Instancia()->getRenderizador());

    if(pNivel != 0)
    {
        bLoadingComplete = true;
    }

    std::cout << "Entrando a Estado Play\n";
    return true;
}

bool EstadoPlay::onExit()
{
    bSaliendo = true;

    ManejadorDeEntrada::Instancia()->reiniciar();

    std::cout << "Salindo de Estado Play\n";
    return true;
}
