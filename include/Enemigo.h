#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <iostream>
#include <ObjetoPacman.h>

class Enemigo : public ObjetoPacman
{
    public:
        virtual std::string tipo() { return "Enemigo"; }
    protected:
        int vidas;
        Enemigo() : ObjetoPacman() {}
        virtual ~Enemigo() {}
};

#endif // ENEMIGO_H
