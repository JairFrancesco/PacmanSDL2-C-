#ifndef COLISION_H
#define COLISION_H
#include <vector>
#include "Vector2D.h"
#include <iostream>
#include <SDL2/SDL.h>

const static int buffer = 4;
/*Con el valor de buffer, se necesitan accesos más directos antes de que se registrarán como una colisión.
Aquí la memoria intermedia se ajusta a 4; esto tomará un cuarto fuera de cada lado del rectángulo.
*/

static bool RectRect(SDL_Rect* A, SDL_Rect* B)
{
    int aHBuf = A->h / buffer;
    int aWBuf = A->w / buffer;

    int bHBuf = B->h / buffer;
    int bWBuf = B->w / buffer;

    // if the bottom of A is less than the top of B - no collision
    if((A->y + A->h) - aHBuf <= B->y + bHBuf)  { return false; }

    // if the top of A is more than the bottom of B = no collision
    if(A->y + aHBuf >= (B->y + B->h) - bHBuf)  { return false; }

    // if the right of A is less than the left of B - no collision
    if((A->x + A->w) - aWBuf <= B->x +  bWBuf) { return false; }

    // if the left of A is more than the right of B - no collision
    if(A->x + aWBuf >= (B->x + B->w) - bWBuf)  { return false; }

    // otherwise there has been a collision
    return true;
}


class Jugador;
class ObjetoJuego;
class CapaTile;

class Colision
{
public:

//    void checkPlayerEnemyBulletCollision(Player* pPlayer);
//
    void verificarColisionJugadorEnemigo(Jugador* pJugador, const std::vector<ObjetoJuego*> &objetos);
    void verificarColisionEnemigoTile(const std::vector<ObjetoJuego*> &vObjetosJuego, const std::vector<CapaTile*>& capasDeColision);
//    void checkEnemyPlayerBulletCollision(const std::vector<GameObject*>& objects);
    void verificarColisionJugadorTile(Jugador* pJugador, const std::vector<CapaTile*>& capasDeColision);
};



#endif // COLISION_H
