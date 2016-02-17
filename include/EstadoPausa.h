#ifndef ESTADOPAUSA_H
#define ESTADOPAUSA_H
#include <iostream>
#include <vector>
#include <EstadoMenu.h>

class ObjetoJuego;

class EstadoPausa : public EstadoMenu
{
    public:
        virtual ~EstadoPausa() {}

        virtual void actualizar();
        virtual void renderizar();

        virtual bool onEnter();
        virtual bool onExit();

        virtual std::string getEstadoID() const { return s_pauseID; }

        virtual void setCallbacks(const std::vector<Callback>& vCallbacks);
    private:
        static void s_pauseToMain();
        static void s_resumePlay();

        static const std::string s_pauseID;

        std::vector<ObjetoJuego*> vObjetosJuego;
};

#endif // ESTADOPAUSA_H
