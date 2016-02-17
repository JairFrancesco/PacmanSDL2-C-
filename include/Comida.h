#ifndef COMIDA_H
#define COMIDA_H

#include <iostream>
#include <ObjetoPacman.h>


class Comida : public ObjetoPacman
{
    public:
        virtual std::string tipo() {return "Comida";}
    protected:
        Comida() : ObjetoPacman(){}
        virtual ~Comida(){}
};

#endif // COMIDA_H
