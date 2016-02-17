#include <zlib.h>
#include <string>
#include "NivelParser.h"
#include "AdministradorTexturas.h"
#include "Juego.h"
#include "CapaObjeto.h"
#include "CapaTile.h"
#include "FabricaObjetosJuego.h"
#include "base64.h"
#include "Nivel.h"

Nivel* NivelParser::parseNivel(const char *nivelArchivo)
{
////    // crear un documento tinyXML y cargar el mapa xml
    TiXmlDocument nivelDocument;
    nivelDocument.LoadFile(nivelArchivo);

    // crear el objeto nivel
    Nivel* pNivel = new Nivel();

    // get el nodo raiz y desplegar algunos valores
    TiXmlElement* pRoot = nivelDocument.RootElement();

    std::cout << "Loading level:\n" << "Version: " << pRoot->Attribute("version") << "\n";
    std::cout << "Width:" << pRoot->Attribute("width") << " - Height:" << pRoot->Attribute("height") << "\n";
    std::cout << "Tile Width:" << pRoot->Attribute("tilewidth") << " - Tile Height:" << pRoot->Attribute("tileheight") << "\n";

    pRoot->Attribute("tilewidth", &magnitudTile);
    pRoot->Attribute("width", &ancho);
    pRoot->Attribute("height", &altura);

    //sabemos que propiedades es el primer hijo de raiz
    TiXmlElement* pProperties = pRoot->FirstChildElement();

    //  Debemos analizar las texturas necesarias para este nivel, que se han añadido a las propiedades
    for(TiXmlElement* e = pProperties->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("property"))
        {
            parseTexturas(e);
        }
    }

    // ahora debemos parsear los conjutos de tiles
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("tileset"))
        {
            parseConjuntoTiles(e, pNivel->getConjuntoTiles());
        }
    }

    // parsear las capas de objetos
    for(TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("objectgroup") || e->Value() == std::string("layer"))
        {
            if(e->FirstChildElement()->Value() == std::string("object"))
            {
                parseCapaObjeto(e, pNivel->getCapas(), pNivel);
            }
            else if(e->FirstChildElement()->Value() == std::string("data") ||
                    (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
            {
                parseCapaTile(e, pNivel->getCapas(), pNivel->getConjuntoTiles(), pNivel->getCapasDeColision());
            }
        }
    }

    return pNivel;
}


void NivelParser::parseTexturas(TiXmlElement* pTextureRoot)
{
    std::cout << "adding texture " << pTextureRoot->Attribute("value") << " with ID " << pTextureRoot->Attribute("name") << std::endl;
    AdministradorDeTexturas::Instancia()->cargar(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"), ElJuego::Instancia()->getRenderizador());
}

void NivelParser::parseConjuntoTiles(TiXmlElement* pTilesetRoot, std::vector<ConjuntoTiles>* pConjuntoTiles)
{
	std::string assetsTag = "";
    // primero Añadir el conjunto de tiles al administrador de texturas
    std::cout << "adding texture " << pTilesetRoot->FirstChildElement()->Attribute("source") << " with ID " << pTilesetRoot->Attribute("name") << std::endl;
	AdministradorDeTexturas::Instancia()->cargar(assetsTag.append(pTilesetRoot->FirstChildElement()->Attribute("source")), pTilesetRoot->Attribute("name"), ElJuego::Instancia()->getRenderizador());

    // Crear un objeto conjunto de tiles
    ConjuntoTiles conjuntoTiles;
    pTilesetRoot->FirstChildElement()->Attribute("width", &conjuntoTiles.ancho);
    pTilesetRoot->FirstChildElement()->Attribute("height", &conjuntoTiles.altura);
    pTilesetRoot->Attribute("firstgid", &conjuntoTiles.primerGridID);
    pTilesetRoot->Attribute("tilewidth", &conjuntoTiles.anchoTile);
    pTilesetRoot->Attribute("tileheight", &conjuntoTiles.alturaTile);
    pTilesetRoot->Attribute("spacing", &conjuntoTiles.espaciado);
    pTilesetRoot->Attribute("margin", &conjuntoTiles.margen);
    conjuntoTiles.nombre = pTilesetRoot->Attribute("name");

    conjuntoTiles.numColumnas = conjuntoTiles.ancho / (conjuntoTiles.anchoTile + conjuntoTiles.espaciado);

    pConjuntoTiles->push_back(conjuntoTiles);
}

void NivelParser::parseCapaObjeto(TiXmlElement* pObjectElement, std::vector<Capa*> *pCapas, Nivel* pNivel)
{
    // crear una capa objeto
    CapaObjeto* pCapaObjeto = new CapaObjeto();

    for(TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("object"))
        {
            int x, y, ancho, altura, numFrames, callbackID = 0, velocidadAnimacion = 0;
            std::string texturaID;
            std::string tipo;

            // get the initial node values type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);

            tipo = e->Attribute("type");
            ObjetoJuego* pObjetoJuego = LaFabricaDeObjetosJuego::Instancia()->crear(tipo);

            // obtener los valores de las propiedades
            for(TiXmlElement* properties = e->FirstChildElement(); properties != NULL; properties = properties->NextSiblingElement())
            {
                if(properties->Value() == std::string("properties"))
                {
                    for(TiXmlElement* property = properties->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
                    {
                        if(property->Value() == std::string("property"))
                        {
                            if(property->Attribute("name") == std::string("numFrames"))
                            {
                                property->Attribute("value", &numFrames);
                            }
                            else if(property->Attribute("name") == std::string("textureHeight"))
                            {
                                property->Attribute("value", &altura);
                            }
                            else if(property->Attribute("name") == std::string("textureID"))
                            {
                                texturaID = property->Attribute("value");
                            }
                            else if(property->Attribute("name") == std::string("textureWidth"))
                            {
                                property->Attribute("value", &ancho);
                            }
                            else if(property->Attribute("name") == std::string("callbackID"))
                            {
                                property->Attribute("value", &callbackID);
                            }
                            else if(e->Attribute("name") == std::string("animSpeed"))
                            {
                                property->Attribute("value", &velocidadAnimacion);
                            }
                        }
                    }
                }
            }
            //int x, int y, int width, int height, std::string textureID, int numFrames, void()
            pObjetoJuego->cargar(std::unique_ptr<CargadorParametros>(new CargadorParametros(x, y, ancho, altura, texturaID, numFrames,callbackID, velocidadAnimacion)));

            if(tipo == "Jugador")
            {
                pNivel->setJugador(dynamic_cast<Jugador*>(pObjetoJuego));
            }

            pCapaObjeto->getObjetosJuego()->push_back(pObjetoJuego);
        }
    }
    pCapas->push_back(pCapaObjeto);
}


void NivelParser::parseCapaTile(TiXmlElement* pTileElement, std::vector<Capa*> *pCapas, const std::vector<ConjuntoTiles>* pConjuntoTiles, std::vector<CapaTile*> *pCapasDeColision)
{
    CapaTile* pCapaTile = new CapaTile(magnitudTile, *pConjuntoTiles);

    bool collidable = false;

    // tile data
    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    TiXmlElement* pDataNode;

    for(TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("properties"))
        {
            for(TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                if(property->Value() == std::string("property"))
                {
                    if(property->Attribute("name") == std::string("collidable"))
                    {
                        collidable = true;
                    }
                }
            }
        }

        if(e->Value() == std::string("data"))
        {
            pDataNode = e;
        }
    }

    for(TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t);
    }

    // uncompress zlib compression
    uLongf sizeofids = ancho * altura * sizeof(int);
    std::vector<int> ids(ancho * altura);
    uncompress((Bytef*)&ids[0], &sizeofids,(const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> filaCapa(ancho);

    for(int j = 0; j < altura; j++)
    {
        data.push_back(filaCapa);
    }

    for(int rows = 0; rows < altura; rows++)
    {
        for(int cols = 0; cols < ancho; cols++)
        {
            data[rows][cols] = ids[rows * ancho + cols];
        }
    }

    pCapaTile->setTileIDs(data);

    //imprimir para corroborar errores
    //cout<<data.size();
    for ( int i = 0; i < data.size(); i++ )
    {
       for ( int j = 0; j < data[i].size(); j++ )
       {
          std::cout << data[i][j] << ' ';
       }
       std::cout << std::endl;
    }

    pCapaTile->setAnchoMapa(ancho);

    if(collidable)
    {
        pCapasDeColision->push_back(pCapaTile);
    }

    pCapas->push_back(pCapaTile);
}
