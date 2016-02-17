#ifndef ESTADOPARSER_H
#define ESTADOPARSER_H

#include <iostream>
#include <vector>
#include <tinyxml.h>

using namespace std;

class ObjetoJuego;

class EstadoParser
{
    public:
        bool parseEstado(const char* archivoEstado, string estadoID, vector<ObjetoJuego*> *pObjetos, vector<string> *pTexturasIDs);
    private:
        void parseObjetos(TiXmlElement* pEstadoRaiz, vector<ObjetoJuego*> *pObjetos);
        void parseTexturas(TiXmlElement* pEstadoRaiz, vector<string> *pTexturasIDs);
};

#endif // ESTADOPARSER_H
