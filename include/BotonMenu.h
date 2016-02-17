#ifndef BOTONMENU_H
#define BOTONMENU_H

#include "ObjetoPacman.h"
#include "FabricaObjetosJuego.h"

class BotonMenu : public ObjetoPacman {
    private:
        enum estado_boton
        {
            MOUSE_OUT = 0,
            MOUSE_OVER = 1,
            CLICKED = 2
        };

        bool bLiberado;
        int callbackID;
        void (*callback)();

    public:
        BotonMenu();
        virtual ~BotonMenu() {}

        virtual void cargar(std::unique_ptr<CargadorParametros> const &pParametros);

        virtual void dibujar();
        virtual void actualizar();
        virtual void limpiar();

        void setCallback(void(*callback)()) { this->callback = callback;}
        int getCallbackID() { return callbackID; }
};

class CreadorBotonMenu : public CreadorBase {
    ObjetoJuego* crearObjetoJuego() const {
        return new BotonMenu();
    }
};

#endif // BOTONMENU_H
