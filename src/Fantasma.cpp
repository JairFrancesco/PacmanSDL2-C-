#include "Fantasma.h"
#include "Colision.h"

Fantasma::Fantasma():Enemigo()
{
    tiempoMuriendo = 4;
    velocidadMovimiento = 3;
    velocidad.setX(2);
}

void Fantasma::cargar(std::unique_ptr<CargadorParametros> const &pParametros)
{
    ObjetoPacman::cargar(std::move(pParametros));
//    ancho=32;
//    altura=32;
//    velocidad.setX(-velocidadMovimiento);
//    velocidad.setY(velocidadMovimeiento)

}

void Fantasma::colisionTile()
{
//    if (!bSonidoMuerteJugador)
//    {
//        Sonido::Instancia()->playMusic("fantasmaComido", 0);
//        //bMuriendo=true;
//    }

    if (velocidad.getY()==0)
    {
        if (velocidad.getX()>0)
        {
            velocidad.setY(3);
            velocidad.setX(0);
        }
        else if (velocidad.getX()<0)
        {
            velocidad.setY(-3);
            velocidad.setX(0);
        }
    }
    else if (velocidad.getX()==0)
    {
        if (velocidad.getY()>0)
        {
            velocidad.setY(0);
            velocidad.setX(-3);
        }
        else if (velocidad.getY()<0)
        {
            velocidad.setY(0);
            velocidad.setX(3);
        }
    }


}

void Fantasma::colisionEnemigo()
{

}

void Fantasma::actualizar()
{
    if (bMuriendo)
    {
        std::cout<<"EL Enemigo Murio!!!"<<std::endl;
        velocidad.setX(0);
        velocidad.setY(0);
    }
    ObjetoPacman::actualizar();
}
