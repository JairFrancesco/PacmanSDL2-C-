#ifndef JUGADOR_H
#define JUGADOR_H
#include <ObjetoPacman.h>
#include <FabricaObjetosJuego.h>

class Jugador: public ObjetoPacman
{
    public:
        Jugador();
        virtual ~Jugador(){};

        virtual void cargar(std::unique_ptr<CargadorParametros> const &pParametros);

        virtual void dibujar();
        virtual void actualizar();
        virtual void limpiar();

        virtual void colisionTile();
        void noColisionTile();
        virtual void colisionEnemigo();

        int getVelocidadMovimiento(){return ObjetoPacman::velocidadMovimiento;}
        void setColisiono(bool col){colisiono=col;};

        virtual std::string tipo() { return "Jugador"; }
    protected:
    private:
        void resucitar();       // Trae al jugador de vuelta si tiene vidas restantes
        void manejarEntrada();     // handle any input from the keyboard, mouse, or joystick
        void manejarAnimacion(); // handle any animation for the player

        // jugador puede ser inmortal por un tiempo
        bool bInmune;
        int tiempoInmune;
        int contadorInmune;
        bool colisiono;
};


// para la fabrica
class CreadorJugador : public CreadorBase {
    ObjetoJuego* crearObjetoJuego() const { return new Jugador(); }
};

#endif // JUGADOR_H
