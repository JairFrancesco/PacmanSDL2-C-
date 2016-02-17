#ifndef CARGADORPARAMETROS_H
#define CARGADORPARAMETROS_H


#include <string>

class CargadorParametros
{
public:

    CargadorParametros(int x, int y, int ancho, int altura, std::string texturaID, int numFrames,
                 int callbackID = 0, int velocidadAnimacion = 0) :
    x(x),
    y(y),
    ancho(ancho),
    altura(altura),
    texturaID(texturaID),
    numFrames(numFrames),
    callbackID(callbackID),
    velocidadAnimacion(velocidadAnimacion)
    {

    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getAncho() const { return ancho; }
    int getAltura() const { return altura; }
    std::string getTexturaID() const { return texturaID; }
    int getNumFrames() const { return numFrames; }
    int getCallbackID() const { return callbackID; }
    int getVelocidadAnimacion() const { return velocidadAnimacion; }

private:

    int x;
    int y;

    int ancho;
    int altura;

    int callbackID;
    int velocidadAnimacion;

    std::string texturaID;

    int numFrames;
};

#endif // CARGADORPARAMETROS_H
