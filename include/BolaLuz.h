#ifndef BOLALUZ_H
#define BOLALUZ_H

#include <iostream>
#include <FabricaObjetosJuego.h>
#include <Sonido.h>
#include <math.h>
#include <Comida.h>

class BolaLuz : public Comida
{
    public:
        BolaLuz(){};
        virtual ~BolaLuz(){};
        virtual void colisionEnemigo();
};

class CreadorBolaDeLuz : public CreadorBase
{
    ObjetoJuego* crearObjetoJuego() const
    {
        return new BolaLuz();
    }
};

#endif // BOLALUZ_H
