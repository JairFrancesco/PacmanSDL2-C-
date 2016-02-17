#ifndef FANTASMA_H
#define FANTASMA_H
#include <iostream>
#include <FabricaObjetosJuego.h>
#include <Sonido.h>
#include <math.h>
#include <Enemigo.h>

class Fantasma: public Enemigo
{
    public:
        Fantasma();
        virtual ~Fantasma() {};
        virtual void cargar(std::unique_ptr<CargadorParametros> const &pParametros);
        virtual void colisionTile();
        virtual void colisionEnemigo();
        virtual void actualizar();
};

class CreadorFantasma: public CreadorBase
{
    ObjetoJuego* crearObjetoJuego() const
    {
        return new Fantasma();
    }
};


#endif // FANTASMA_H
