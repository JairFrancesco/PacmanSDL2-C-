#ifndef CAPA_H
#define CAPA_H

class Nivel;

class Capa
{
    public:
        virtual ~Capa() {}
        virtual void renderizar() = 0;
        virtual void actualizar(Nivel* pNivel) = 0;
};

#endif // CAPA_H
