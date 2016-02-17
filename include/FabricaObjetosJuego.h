#ifndef FABRICAOBJETOSJUEGO_H
#define FABRICAOBJETOSJUEGO_H

#include <string>
#include <iostream>
#include <map>
#include <ObjetoJuego.h>

class CreadorBase
{
public:
    virtual ObjetoJuego* crearObjetoJuego() const = 0;
    virtual ~CreadorBase() {}
};


class FabricaObjetosJuego
{
    public:
        static FabricaObjetosJuego* Instancia()
        {
            if(pInstancia == 0)
            {
                pInstancia = new FabricaObjetosJuego();
            }

            return pInstancia;
        }
        bool registrarTipo(std::string tipoID, CreadorBase* pCreador)
        {
            std::map<std::string, CreadorBase*>::iterator it = vCreadores.find(tipoID);

            // If el tipo ya esta registrado, no hacer nada
            if(it != vCreadores.end())
            {
                delete pCreador;
            }
            vCreadores[tipoID] = pCreador;
            return true;
        }

        ObjetoJuego* crear(std::string tipoID)
        {
            std::map<std::string, CreadorBase*>::iterator it = vCreadores.find(tipoID);
            if(it == vCreadores.end())
            {
                std::cout << "No se pudo encontrar el tipo: " << tipoID << "\n";
                return NULL;
            }

            CreadorBase* pCreador = (*it).second;
            return pCreador->crearObjetoJuego();
        }


    protected:
    private:
        FabricaObjetosJuego(){};
        ~FabricaObjetosJuego(){};
        std::map<std::string, CreadorBase*> vCreadores;
        static FabricaObjetosJuego* pInstancia;
};

typedef FabricaObjetosJuego LaFabricaDeObjetosJuego;

#endif // FABRICAOBJETOSJUEGO_H
