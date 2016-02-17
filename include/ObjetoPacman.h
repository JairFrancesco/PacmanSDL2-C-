#ifndef OBJETOPACMAN_H
#define OBJETOPACMAN_H
#include <SDL2/SDL.h>
#include <ObjetoJuego.h>

class ObjetoPacman: public ObjetoJuego
{
    public:
        virtual ~ObjetoPacman(){};
        virtual void cargar(std::unique_ptr<CargadorParametros> const &pParametros);

        virtual void dibujar();
        virtual void actualizar();

        virtual void limpiar() {}
        virtual void colisionTile() {}
        virtual void colisionEnemigo() {}

        virtual std::string tipo() { return "SDLGameObject"; }
    protected:
        ObjetoPacman();
        void haciendoAnimacion();
//
//        int velocidadBajaDisparo;
//        int m_bulletCounter;
        int velocidadMovimiento;

        // cuánto tiempo tarda la animación de la muerte, junto con un contador
        int tiempoMuriendo;
        int contadorMuriendo;

        // tiene sonido cuando muere el jugador?
        bool bSonidoMuerteJugador;
    private:
};

#endif // OBJETOPACMAN_H
