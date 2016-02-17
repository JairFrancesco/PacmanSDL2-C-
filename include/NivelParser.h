#ifndef NIVELPARSER_H
#define NIVELPARSER_H
#include <iostream>
#include <vector>
#include "tinyxml.h"


class Nivel;
struct ConjuntoTiles;
class Capa;
class CapaTile;

class NivelParser
{
    public:
        Nivel* parseNivel(const char* estadoArchivo);
        virtual ~NivelParser(){};
    private:
        void parseTexturas(TiXmlElement* pTexturaRaiz);
        void parseConjuntoTiles(TiXmlElement* pConjuntoTileRaiz, std::vector<ConjuntoTiles>* pConjuntoTiles);
        void parseCapaObjeto(TiXmlElement* pElementoObjeto, std::vector<Capa*> *pCapas, Nivel* pNivel);
        void parseCapaTile(TiXmlElement* pElementoTile, std::vector<Capa*> *pCapas,
        const std::vector<ConjuntoTiles>* pConjuntosTile, std::vector<CapaTile*> *pCapasColision);

        int magnitudTile;
        int ancho;
        int altura;
};


#endif // NIVELPARSER_H
