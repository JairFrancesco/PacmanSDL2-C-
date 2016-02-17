#ifndef ESTADOGAMEOVER_H
#define ESTADOGAMEOVER_H
#include <iostream>
#include <vector>
#include <EstadoMenu.h>

class ObjetoJuego;

class EstadoGameOver: public EstadoMenu
{
    public:
        virtual ~EstadoGameOver() {}

        virtual void actualizar();
        virtual void renderizar();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getEstadoID() const { return s_gameOverID; }

        virtual void setCallbacks(const std::vector<Callback>& vCallbacks);

    private:
        static void s_gameOverToMain();
        static void s_restartPlay();

        static const std::string s_gameOverID;

        std::vector<ObjetoJuego*> vObjetosJuego;
};

#endif // ESTADOGAMEOVER_H
