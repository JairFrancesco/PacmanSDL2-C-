#include "CapaTile.h"
#include "AdministradorTexturas.h"
#include "Juego.h"

CapaTile::CapaTile(int magnitudTile, const std::vector<ConjuntoTiles>& vConjuntoTiles) : magnitudTile(magnitudTile), vConjuntoTiles(vConjuntoTiles), posicion(0,0), velocidad(0,0)
{
    numColumnas = (ElJuego::Instancia()->getAnchoJuego() / magnitudTile) + 1;
    numFilas = (ElJuego::Instancia()->getAlturaJuego() / magnitudTile);
}

void CapaTile::actualizar(Nivel* pNivel)
{
//    if(posicion.getX() < ((anchoMapa * magnitudTile) - ElJuego::Instancia()->getAnchoJuego()) - magnitudTile)
//    {
//        //velocidad.setX(ElJuego::Instancia()->getScrollSpeed());
////        posicion += velocidad;
//
//    }
//    else
//    {
//     //   velocidad.setX(0);
//    }
}

void CapaTile::renderizar()
{
    int x, y, x2, y2 = 0;

    x = posicion.getX() / magnitudTile;
    y = posicion.getY() / magnitudTile;

    x2 = int(posicion.getX()) % magnitudTile;
    y2 = int(posicion.getY()) % magnitudTile;

    for(int i = 0; i < numFilas; i++)
    {
        for(int j = 0; j < numColumnas; j++)
        {
            int id = vTileIDs[i + y][j + x];

            if(id == 0)
            {
                continue;
            }

            ConjuntoTiles ConjuntoTiles = getConjuntoTilesPorID(id);

            id--;

            AdministradorDeTexturas::Instancia()->dibujarTile(ConjuntoTiles.nombre,
            ConjuntoTiles.margen, ConjuntoTiles.espaciado, (j * magnitudTile) - x2, (i * magnitudTile) - y2,
            magnitudTile, magnitudTile, (id - (ConjuntoTiles.primerGridID - 1)) / ConjuntoTiles.numColumnas,
            (id - (ConjuntoTiles.primerGridID - 1)) % ConjuntoTiles.numColumnas, ElJuego::Instancia()->getRenderizador());
        }
    }
}

ConjuntoTiles CapaTile::getConjuntoTilesPorID(int tileID)
{
//    cout<<"Tile ID: "<<tileID<<endl;
    for(int i = 0; i < vConjuntoTiles.size(); i++)
    {
        if( i + 1 <= vConjuntoTiles.size() - 1)
        {
            if(tileID >= vConjuntoTiles[i].primerGridID && tileID < vConjuntoTiles[i + 1].primerGridID)
            {
                return vConjuntoTiles[i];
            }
        }
        else
        {
            return vConjuntoTiles[i];
        }
    }

    std::cout << "No se encuentra conjunto de tiles, volviendo vacio el conjunto de tiles";
    ConjuntoTiles t;
    return t;
}
