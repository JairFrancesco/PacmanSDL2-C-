#ifndef CAPAOBJETO_H
#define CAPAOBJETO_H
#include <iostream>
#include <vector>
#include <Capa.h>
#include <Colision.h>
#include <ObjetoJuego.h>



class CapaObjeto: public Capa
{
    public:
        virtual ~CapaObjeto();

        // Pasar un objeto a traves del nivel
        virtual void actualizar(Nivel* pNivel);
        virtual void renderizar();

        // return a pointer to this layers objects, the level parser will fill this
        // retorna un punero a estas capas de objetos,el parseador de nivel llenara esto
        std::vector<ObjetoJuego*>* getObjetosJuego() { return &vObjetosJuego; }
    private:
        // verificar colisiones de objetos de juego
        Colision colision;

        // Una lista de objetos Juego
        std::vector<ObjetoJuego*> vObjetosJuego;
};

#endif // CAPAOBJETO_H

