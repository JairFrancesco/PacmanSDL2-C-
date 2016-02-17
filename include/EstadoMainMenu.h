#ifndef ESTADOMAINMENU_H
#define ESTADOMAINMENU_H
#include <EstadoMenu.h>
#include <ObjetoJuego.h>


class EstadoMainMenu:public EstadoMenu
{
    public:
        virtual void actualizar();
        virtual void renderizar();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getEstadoID() const { return s_menuID; }
    private:
        virtual void setCallbacks(const std::vector<Callback>& vCallbacks);
        // call back functions para items de menu
        static void s_menuToPlay();
        static void s_salirDeMenu();
        static const std::string s_menuID;
        std::vector<ObjetoJuego*> vObjetosJuego;

};
#endif // ESTADOMAINMENU_H
