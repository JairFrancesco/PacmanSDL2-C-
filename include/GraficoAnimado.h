#ifndef GRAFICOANIMADO_H
#define GRAFICOANIMADO_H

#include "FabricaObjetosJuego.h"
#include "ObjetoPacman.h"


class GraficoAnimado : public ObjetoPacman
{
public:

    GraficoAnimado();
    virtual ~GraficoAnimado() {}

    virtual void cargar(std::unique_ptr<CargadorParametros> const &pParametros);

    virtual void dibujar();
    virtual void actualizar();
    virtual void limpiar();

private:

    int velocidadAnimacion;
    int contadorFrames;
};

class CreadorGraficoAnimado : public CreadorBase
{
public:

    virtual ObjetoJuego* crearObjetoJuego() const
    {
        return new GraficoAnimado();
    }
};


#endif // GRAFICOANIMADO_H
