#ifndef NIVEL_H
#define NIVEL_H

#include <iostream>
#include <vector>
#include <Capa.h>
#include <NivelParser.h>
#include <Jugador.h>
#include <Colision.h>

class CapaTile;


struct ConjuntoTiles
{
    int primerGridID;
    int anchoTile;
    int alturaTile;
    int espaciado;
    int margen;
    int ancho;
    int altura;
    int numColumnas;
    std::string nombre;
};

class Nivel
{
    public:
        ~Nivel();
        void actualizar();
        void renderizar();

        std::vector<ConjuntoTiles>* getConjuntoTiles() { return &vConjuntoTiles; }
        std::vector<Capa*>* getCapas() { return &vCapas; }
        std::vector<CapaTile*>* getCapasDeColision() { return &vCapasDeColision; }

        const std::vector<CapaTile*>& getCapasCollidable() { return vCapasDeColision; }

        Jugador* getJugador() { return pJugador; }
        void setJugador(Jugador* pJugador) { this->pJugador = pJugador; }
    private:
        friend class NivelParser;

        Nivel();

        Jugador* pJugador;

        std::vector<Capa*> vCapas;
        std::vector<ConjuntoTiles> vConjuntoTiles;
        std::vector<CapaTile*> vCapasDeColision;
};

#endif // NIVEL_H
