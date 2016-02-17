#ifndef OBJETOJUEGO_H
#define OBJETOJUEGO_H
#include "CargadorParametros.h"
#include "Vector2D.h"
#include <string>
#include <memory>
#include <iostream>

class ObjetoJuego
{
public:

    // Clase base necesita un constructor virtual
    virtual ~ObjetoJuego() {}

    // load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
    virtual void cargar(std::unique_ptr<CargadorParametros> const &pParametros)=0;

    // dibujar the object
    virtual void dibujar()=0;

    // do actualizar stuff
    virtual void actualizar()=0;

    // remove anything that needs to be deleted
    virtual void limpiar()=0;

    // Objeto ha colisionado?, manejar acorde
    virtual void colisionTile() = 0;
    virtual void colisionEnemigo() = 0;

    // get el tipo del objeto
    virtual std::string tipo() = 0;

    // getters para variables comunes
    Vector2D& getPosicion() { return posicion; }
    Vector2D& getVelocidad() { return velocidad; }

    int getAncho() { return ancho; }
    int getAltura() { return altura; }

    // scroll along with tile map
//    void scroll(float scrollSpeed)
//    {
//        if(type() != std::string("Player")) // player is never scrolled
//        {
//            m_position.setX(m_position.getX() - scrollSpeed);
//        }
//    }

    // esta el objeto actualmente siendo actualizado?
    bool actualizando() { return bActualizando; }

    // esta el objeto muerto?
    bool muerto() { return bMuerto; }

    // esta el objeto haciendo una animacion de muerte?
    bool muriendo() { return bMuriendo; }

    // establecer si actualizar el objeto o no
    void setActualizando(bool actualizando) { bActualizando = actualizando; }

protected:

    // Constructor con lista de inicializacion por defecto
    ObjetoJuego() :  posicion(0,0),
                    velocidad(0,0),
                    aceleracion(0,0),
                    ancho(0),
                    altura(0),
                    filaActual(0),
                    frameActual(0),
                    bActualizando(false),
                    bMuerto(false),
                    bMuriendo(false),
                    angulo(0),
                    alpha(255)
    {
    }

    // variables de movimiento
    Vector2D posicion;
    Vector2D velocidad;
    Vector2D aceleracion;

    // variables de tamaño
    int ancho;
    int altura;

    // variables de animacion
    int filaActual;
    int frameActual;
    int numFrames;
    std::string texturaID;

    // common boolean variables
    bool bActualizando;
    bool bMuerto;
    bool bMuriendo;

    // rotation
    double angulo;

    // blending
    int alpha;
};

#endif // OBJETOJUEGO_H
