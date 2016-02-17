#ifndef MAQUINAESTADOJUEGO_H
#define MAQUINAESTADOJUEGO_H

#include <EstadoJuego.h>

class MaquinaEstadoJuego
{
    public:
        MaquinaEstadoJuego(){};
        virtual ~MaquinaEstadoJuego(){};

        void actualizar();
        void renderizar();

        void pushEstado(EstadoJuego* pEstado);
        void cambiarEstado(EstadoJuego* pEstado);
        void popEstado();
        void limpiar();
        std::vector<EstadoJuego*>& getEstadosJuego(){return vEstadosJuego;}
    protected:
    private:
        std::vector<EstadoJuego*> vEstadosJuego;
};

#endif // MAQUINAESTADOJUEGO_H
