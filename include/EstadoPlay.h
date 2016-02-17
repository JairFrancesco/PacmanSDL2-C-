#ifndef ESTADOPLAY_H
#define ESTADOPLAY_H
#include "EstadoJuego.h"
#include "Colision.h"
#include "Nivel.h"
#include "Vector2D.h"

class ObjetoJuego;
class ObjetoPacman;
class Nivel;

class EstadoPlay : public EstadoJuego
{
    public:
        virtual ~EstadoPlay() { delete pNivel; }
        virtual void actualizar();
        virtual void renderizar();
        virtual bool onEnter();
        virtual bool onExit();
        virtual std::string getEstadoID() const { return s_playID; }
    private:
        static const std::string s_playID;
        Colision colision;
        std::vector<ObjetoJuego*> vObjetosJuego;
        Nivel* pNivel;
};

#endif // ESTADOPLAY_H
