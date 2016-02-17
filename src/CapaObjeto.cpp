#include "CapaObjeto.h"
#include <Vector2D.h>
#include <Juego.h>
#include <Nivel.h>



CapaObjeto::~CapaObjeto()
{
    for(std::vector<ObjetoJuego*>::iterator it = vObjetosJuego.begin(); it != vObjetosJuego.end(); ++it)// < m_gameObjects.size(); i++)
    {
        delete (*it);
    }
    vObjetosJuego.clear();
}

void CapaObjeto::actualizar(Nivel* pNivel)
{
//    colision.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
//    colision.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
    colision.verificarColisionJugadorEnemigo(pNivel->getJugador(), (const std::vector<ObjetoJuego*>&) vObjetosJuego);
    //colision.verificarColisionEnemigoTile((const std::vector<ObjetoJuego*>&) vObjetosJuego, pNivel->getCapasCollidable());

    colision.verificarColisionEnemigoTile((const std::vector<ObjetoJuego*>&) vObjetosJuego, pNivel->getCapasCollidable());
	if(pNivel->getJugador()->getPosicion().getX() + pNivel->getJugador()->getAncho() < ElJuego::Instancia()->getAnchoJuego())
	{
		colision.verificarColisionJugadorTile(pNivel->getJugador(), pNivel->getCapasCollidable());

		/*
		objetos Collidable, es decir, que registrarán un estado de colisión.
		Esto no quiere decir que van a responder a la colisión (es decir respondable),
		que es algo diferente. Sólo las formas son objetos Collidable.
		*/
	}

    // iterar a traves de los objetos
    if(!vObjetosJuego.empty())
    {
        for(std::vector<ObjetoJuego*>::iterator it = vObjetosJuego.begin(); it != vObjetosJuego.end();)// < m_gameObjects.size(); i++)
        {
            if((*it)->getPosicion().getX() <= ElJuego::Instancia()->getAnchoJuego())
            {
                (*it)->setActualizando(true);
                (*it)->actualizar();
            }
            else
            {
                if((*it)->tipo() != std::string("Jugador"))
                {
                    (*it)->setActualizando(false);
                    //(*it)->scroll(TheGame::Instance()->getScrollSpeed());
                }
                else
                {
                    (*it)->actualizar();
                }
            }

            // verifica si esta muerto o fuera de la pantalla
            if((*it)->getPosicion().getX() < (0 - (*it)->getAncho()) || (*it)->getPosicion().getY() > (ElJuego::Instancia()->getAlturaJuego()) || ((*it)->muerto()))
            {
                delete * it;
                it = vObjetosJuego.erase(it); // erase from vector and get new iterator
            }
            else
            {
                ++it; // increment if all ok
            }

        }
    }
}

void CapaObjeto::renderizar()
{
    for(int i = 0; i < vObjetosJuego.size(); i++)
    {
        if(vObjetosJuego[i]->getPosicion().getX() <= ElJuego::Instancia()->getAnchoJuego())
        {
            vObjetosJuego[i]->dibujar();
        }
    }
}
