#include "EstadoParser.h"
#include <Juego.h>
#include <CargadorParametros.h>
#include <FabricaObjetosJuego.h>
#include <AdministradorTexturas.h>

bool EstadoParser::parseEstado(const char* archivoEstado, string estadoID,
vector<ObjetoJuego*> *pObjetos, vector<string> *pTexturasIds)
{
    //Crear el documento XML
    TiXmlDocument xmlDoc;

    //Cargar el archivo Estado
    /*
    std::cout - Regular output (console output)
    std::cerr - Error output (console error)
    std::clog - Nobody cares (console log)
    */
    if (!xmlDoc.LoadFile(archivoEstado))
    {
        cerr<< xmlDoc.ErrorDesc()<<"\n";
        return false;
    }
    //Obtiene el elemento Raiz(Root)
    TiXmlElement* pRaiz = xmlDoc.RootElement(); //Estados

    //Pre declara los estados del nodo raiz
    TiXmlElement* pEstadoRaiz = 0;

    //obtener el nodo raíz de este estado y asignarlo a pEstadoRaiz
    for(TiXmlElement* e = pRaiz->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == estadoID)
        {
            pEstadoRaiz = e;
        }
    }

    //Predeclara la raiz textura
    TiXmlElement* pTexturaRaiz = 0;
    //Obtener la raiz(root) de los elementos textura
    for(TiXmlElement* e = pEstadoRaiz->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == string("TEXTURES"))
        {
        pTexturaRaiz = e;
        }
    }

    //Ahora parsear las texturas
    parseTexturas(pTexturaRaiz, pTexturasIds);

    //Pre declarar los objetos del nodo raiz
    TiXmlElement* pObjetoRaiz = 0;

    //Obtiene el nodo raiz y lo asigna a pObjetoRaiz
    for(TiXmlElement* e = pEstadoRaiz->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if(e->Value() == string("OBJECTS"))
        {
        pObjetoRaiz = e;
        }
    }

    // Ahora parsear los objetos
    parseObjetos(pObjetoRaiz, pObjetos);
    return true;
}

void EstadoParser::parseTexturas(TiXmlElement* pEstadoRaiz, vector<string> *pTexturasIDs)
{
    for(TiXmlElement* e = pEstadoRaiz->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
        string nombreArchivoAtributo = e->Attribute("filename");
        string idAtributo = e->Attribute("ID");
        pTexturasIDs->push_back(idAtributo); // poner dentro de la lista
        AdministradorDeTexturas::Instancia()->cargar(nombreArchivoAtributo,idAtributo, ElJuego::Instancia()->getRenderizador());
    }
}

void EstadoParser::parseObjetos(TiXmlElement *pEstadoRaiz, std::vector<ObjetoJuego *> *pObjetos)
{
    for(TiXmlElement* e = pEstadoRaiz->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
    int x, y, ancho, altura, numFrames, callbackID, velocidadAnimacion;
    string texturaID;
    e->Attribute("x", &x);
    e->Attribute("y", &y);
    e->Attribute("width",&ancho);
    e->Attribute("height", &altura);
    e->Attribute("numFrames", &numFrames);
    e->Attribute("callbackID", &callbackID);
    e->Attribute("animSpeed", &velocidadAnimacion);
    texturaID = e->Attribute("textureID");
    ObjetoJuego* pObjetoJuego = LaFabricaDeObjetosJuego::Instancia()->crear(e->Attribute("type"));
    pObjetoJuego->cargar(unique_ptr<CargadorParametros>
    (new CargadorParametros(x,y,ancho,altura,texturaID,numFrames,callbackID, velocidadAnimacion)));
    pObjetos->push_back(pObjetoJuego);
    }

}
