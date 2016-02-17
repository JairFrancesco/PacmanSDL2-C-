#include "Nivel.h"
#include "AdministradorTexturas.h"
#include "Juego.h"
#include "Capa.h"
#include "CapaTile.h"
#include "math.h"
#include <iostream>

Nivel::Nivel()
{
    //ctor
}
Nivel::~Nivel()
{
    for(int i = 0; i < vCapas.size(); i++)
    {
        delete vCapas[i];
    }

    vCapas.clear();
}

void Nivel::renderizar()
{
    for(int i = 0; i < vCapas.size(); i++)
    {
        vCapas[i]->renderizar();
    }
}

void Nivel::actualizar()
{

    for(int i = 0; i < vCapas.size(); i++)
    {
        vCapas[i]->actualizar(this);
    }
}
