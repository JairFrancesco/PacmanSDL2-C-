#include "Colision.h"
#include "Jugador.h"
#include "Enemigo.h"
#include "CapaTile.h"
#include <ManejadorEntrada.h>

void Colision::verificarColisionJugadorEnemigo(Jugador* pJugador, const std::vector<ObjetoJuego*> &objetos)
{
    //std::cout<<"Verificando colision con enemigo"<<endl;
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pJugador->getPosicion().getX();
    pRect1->y = pJugador->getPosicion().getY();
    pRect1->w = pJugador->getAncho();
    pRect1->h = pJugador->getAltura();

    for(int i = 0; i < objetos.size(); i++)
    {
        if (objetos[i]->tipo()==std::string("Comida"))
        {
            SDL_Rect* pRect2 = new SDL_Rect();
            pRect2->x = objetos[i]->getPosicion().getX();
            pRect2->y = objetos[i]->getPosicion().getY();
            pRect2->w = objetos[i]->getAncho();
            pRect2->h = objetos[i]->getAltura();

            if(RectRect(pRect1, pRect2))
            {
                objetos[i]->colisionEnemigo();
                std::cout<<"COlisiono con la comida :V"<<endl;
            }
        }
        if(objetos[i]->tipo() != std::string("Enemigo") || !objetos[i]->actualizando())
        {
            continue;
        }


        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = objetos[i]->getPosicion().getX();
        pRect2->y = objetos[i]->getPosicion().getY();
        pRect2->w = objetos[i]->getAncho();
        pRect2->h = objetos[i]->getAltura();

        if(RectRect(pRect1, pRect2))
        {
            std::cout<<"COlisiono con el fantasma"<<endl;
            if(!objetos[i]->muerto() && !objetos[i]->muriendo())
            {
                std::cout<<"COlisiono con el fantasma"<<endl;
                pJugador->colisionEnemigo();
            }
        }

        delete pRect2;
    }

    delete pRect1;
}


void Colision::verificarColisionJugadorTile(Jugador* pJugador, const std::vector<CapaTile*>& capasColision)
{
     int ULx,ULy, URx, URy, DLx, DLy, DRx, DRy;  //Estas variables son solo las cordenadas de las esquinas del pacman
     int x=pJugador->getPosicion().getX(), y=pJugador->getPosicion().getY(); //las cordenadas del Pacman que es la esquina superior izquierda
        int a= pJugador->getVelocidad().getX(), b=pJugador->getVelocidad().getY();

//        std::cout<<"vel x:"<<a<<"vel y"<<b<<endl;
        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_UP)
            && pJugador->getPosicion().getY() > 0)
        {
            a=0;
            b=-(pJugador->getVelocidadMovimiento());;
        }
        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_DOWN)
            && (pJugador->getPosicion().getY() + pJugador->getAltura()) < ElJuego::Instancia()->getAlturaJuego() - 10)
        {

            a = 0;
            b = (pJugador->getVelocidadMovimiento());
        }

        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_LEFT) && pJugador->getPosicion().getX() > 0)
        {
            a = -(pJugador->getVelocidadMovimiento());
            b=0;
        }
        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_RIGHT)
        && (pJugador->getPosicion().getX() + pJugador->getAncho()) < ElJuego::Instancia()->getAnchoJuego())
        {
            a = (pJugador->getVelocidadMovimiento());
            b=0;
        }


    for(std::vector<CapaTile*>::const_iterator it = capasColision.begin(); it != capasColision.end(); ++it)
    {
        CapaTile* pCapaTile = (*it);
        std::vector<std::vector<int>> tiles = pCapaTile->getTileIDs();

//        Vector2D CapaPos = pCapaTile->getPosicion();

        int x, y;
//
//        x = CapaPos.getX() / pCapaTile->getMagnitudTile();
//        y = CapaPos.getY() / pCapaTile->getMagnitudTile();


        x=pJugador->getPosicion().getX()+a;
        y=pJugador->getPosicion().getY()+b;


        ULx=(x)/pCapaTile->getMagnitudTile();
        ULy=(y)/pCapaTile->getMagnitudTile();
        URx=(x+pJugador->getAncho())/pCapaTile->getMagnitudTile();
        URy=(y)/pCapaTile->getMagnitudTile();
        DLx=(x)/pCapaTile->getMagnitudTile();
        DLy=(y+pJugador->getAltura())/pCapaTile->getMagnitudTile();
        DRx=(x+pJugador->getAncho())/pCapaTile->getMagnitudTile();
        DRy=(y+pJugador->getAltura())/pCapaTile->getMagnitudTile();

        if ((tiles[ULy][ULx]==0)&&(tiles[URy][URx]==0)&&(tiles[DLy][DLx]==0)&&(tiles[DRy][DRx]==0)){
            pJugador->noColisionTile();
        }
        else
        {
            pJugador->colisionTile();
        }

    }
}

void  Colision::verificarColisionEnemigoTile(const std::vector<ObjetoJuego*>& vObjetos, const std::vector<CapaTile*>& capasColision)
{
    int ULx,ULy, URx, URy, DLx, DLy, DRx, DRy;  //Estas variables son solo las cordenadas de las esquinas del pacman
    for(int i = 0; i < vObjetos.size(); i++)
    {

            if(vObjetos[i]->tipo() != std::string("Enemigo") || !vObjetos[i]->actualizando())
            {
                continue;
            }
            for(std::vector<CapaTile*>::const_iterator it = capasColision.begin(); it != capasColision.end(); ++it)
            {
                CapaTile* pCapaTile = (*it);
                std::vector<std::vector<int>> tiles = pCapaTile->getTileIDs();
                int x, y;
                int a= vObjetos[i]->getVelocidad().getX(), b=vObjetos[i]->getVelocidad().getY();

  //              std::cout<<"aa: "<<a<<", b:"<<b<<std::endl;
                x=vObjetos[i]->getPosicion().getX()+a;
                y=vObjetos[i]->getPosicion().getY()+b;

//                std::cout<<"X:"<<x/32<<"Y:"<<y/32<<"ancho: "<<vObjetos[i]->getAncho()<<"Altura:"<<vObjetos[i]->getAltura()<<std::endl;


                ULx=(x)/pCapaTile->getMagnitudTile();
                ULy=(y)/pCapaTile->getMagnitudTile();
                URx=(x+vObjetos[i]->getAncho())/pCapaTile->getMagnitudTile();
                URy=(y)/pCapaTile->getMagnitudTile();
                DLx=(x)/pCapaTile->getMagnitudTile();
                DLy=(y+vObjetos[i]->getAltura())/pCapaTile->getMagnitudTile();
                DRx=(x+vObjetos[i]->getAncho())/pCapaTile->getMagnitudTile();
                DRy=(y+vObjetos[i]->getAltura())/pCapaTile->getMagnitudTile();

                if ((tiles[ULy][ULx]!=0)||(tiles[URy][URx]!=0)||(tiles[DLy][DLx]!=0)||(tiles[DRy][DRx]!=0)){
                    std::cout<<"COLISIONTILE()"<<std::endl;

                    vObjetos[i]->colisionTile();
                }
            }
    }

}
