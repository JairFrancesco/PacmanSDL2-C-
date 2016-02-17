#ifndef ESTADOMENU_H
#define ESTADOMENU_H
#include <EstadoJuego.h>

class EstadoMenu: public EstadoJuego
{
    public:
        virtual ~EstadoMenu(){};
    protected:
        typedef void(*Callback)();
        virtual void setCallbacks(const std::vector<Callback>& vCallbacks) = 0;

        std::vector<Callback> vCallBacks;
};
//    public:
//        virtual void actualizar();
//        virtual void renderizar();
//        virtual bool onEnter();
//        virtual bool onExit();
//        virtual std::string getEstadoID() const { return menuID; }
//    private:
//        static const std::string menuID;
//        std::vector<ObjetoJuego*> vObjetosJuego;
//};

#endif // ESTADOMENU_H
