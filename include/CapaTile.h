#ifndef CAPATILE_H
#define CAPATILE_H

#include <iostream>
#include <vector>
#include <Capa.h>
#include <Nivel.h>
#include <Vector2D.h>

class CapaTile: public Capa
{
    public:
        CapaTile(int magnitudTile, const std::vector<ConjuntoTiles>& vConjuntoTiles);
        virtual ~CapaTile() {}

        virtual void actualizar(Nivel* pNivel);
        virtual void renderizar();

        void setTileIDs(const std::vector<std::vector<int>>& data) { vTileIDs = data; }
        void setMagnitudTile(int tileSize) { magnitudTile = tileSize; }
        void setAnchoMapa(int anchoMapa) { this->anchoMapa = anchoMapa; }


        int getMagnitudTile() { return magnitudTile; }

        const std::vector<std::vector<int>>& getTileIDs() { return vTileIDs; }

        ConjuntoTiles getConjuntoTilesPorID(int tileID);

        const Vector2D getPosicion() { return posicion; }
    private:
        int numColumnas;
        int numFilas;
        int magnitudTile;

        int anchoMapa;

        Vector2D posicion;
        Vector2D velocidad;

        const std::vector<ConjuntoTiles>& vConjuntoTiles;

        std::vector<std::vector<int>> vTileIDs;
};

#endif // CAPATILE_H
