#include "Jugador.h"
#include <memory>
#include <Sonido.h>
#include <ManejadorEntrada.h>
#include <Juego.h>
#include <Nivel.h> //Observacion, solo para probar la colision con los tiles

Jugador::Jugador(): ObjetoPacman(),
bInmune(false),
//tiempoInmune(200),
tiempoInmune(200),
contadorInmune(0)
{
}

void Jugador::colisionEnemigo() {
    //si el jugador no esta inmune entonces configurar a muriendo y cambiar los valores para
    // animacion muerto tile sheet
   if(!bInmune && !ElJuego::Instancia()->getNivelCompleto()) {
       frameActual = 0;
       texturaID = "muriendo";
       numFrames = 5;
       ancho = 32;
       altura = 32;
       bMuriendo = true;

   }
   Sonido::Instancia()->playMusic("muerte", 1);


    //velocidad.setX(1);
}

void Jugador::colisionTile()
{
    colisiono = true;
    velocidad.setX(0);
    velocidad.setY(0);
//    this->actualizar();
}

void Jugador::noColisionTile()
{
    colisiono = false;
    //this->actualizar();
}

void Jugador::cargar(std::unique_ptr<CargadorParametros> const &pParametros) {
    ObjetoPacman::cargar(std::move(pParametros));    // inherited load function

    // can set up the players inherited values here
    // set up bullets
    //bulletFiringSpeed = 13;
    velocidadMovimiento = 3;
    velocidad.setX(velocidadMovimiento);
    //bulletCounter = bulletFiringSpeed;      // we want to be able to fire instantly

    tiempoMuriendo = 100;                          // time it takes for death explosion
}


// player has no special drawing requirements
void Jugador::dibujar() { ObjetoPacman::dibujar(); }

void Jugador::manejarAnimacion() {
    // si el jugador es invulnerable podemos FLASH su alfa para que la gente sepa
    if(bInmune) {
        // invulnerabilidad está terminado, establece valores de nuevo
        if(contadorInmune == tiempoInmune) {
            bInmune = false;
            contadorInmune = 0;
            alpha = 255;
        }
        else { // De lo contrario, el flash de la alfa se prende y apaga
            if(alpha == 255) {
                alpha = 0;
            } else {
                alpha = 255;
            }
        }

        contadorInmune++;        // incrementar nuestro contador
    }

    //  si el jugador no está muerto, entonces podemos cambiar el ángulo con la velocidad
    //  para dar la impresión de un jugador(pacman) en movimiento
    if(!bMuerto) {
        if(velocidad.getX() < 0) {
            angulo = -180.0;
        } else if(velocidad.getX() > 0) {
            angulo = 0.0;
        } else if (velocidad.getY()<0)
        {
            angulo = -90.0;
        } else if (velocidad.getY()>0)
        {
            angulo = 90.0;
        }
        else {
            angulo = 0.0;
        }
    }

    // our standard animation code - for helicopter propellors
    frameActual = int(((SDL_GetTicks() / (100)) % numFrames));
}


void Jugador::actualizar() {
    if(ElJuego::Instancia()->getNivelCompleto()) {
        if(posicion.getX() >= ElJuego::Instancia()->getAnchoJuego()) {
            ElJuego::Instancia()->setNivelActual(
                ElJuego::Instancia()->getNivelActual() + 1);
        } else {
            velocidad.setY(0);
            velocidad.setX(3);
            //ObjetoPacman::actualizar();
            manejarAnimacion();
        }
    } else {
        // if the player is not doing its death animation then update it normally
        if(!bMuriendo) {
            // reset velocity

//            velocidad.setX(0);
//            velocidad.setY(0);
////
            if (!colisiono)
                manejarEntrada();
                // get input
                // do normal position += velocity update
                ObjetoPacman::actualizar();
                // update the animation
                manejarAnimacion();

        } else {// si el jugador esta haciendo animacion de muerte
            frameActual = int(((SDL_GetTicks() / (100)) % numFrames));

            // si la animacion de muerte se ha completado
            // resucitar al jugador
            if(contadorMuriendo == tiempoMuriendo) { resucitar(); }
            contadorMuriendo++;
        }
    }
}


void Jugador::resucitar() {
    ElJuego::Instancia()->setVidasJugador(ElJuego::Instancia()->getVidasJugador() - 1);

    posicion.setX(70);
    posicion.setY(400);
    bMuriendo = false;

    texturaID = "jugador";

    frameActual = 0;
    numFrames = 2;
    ancho = 24;
    altura = 24;

    contadorMuriendo = 0;
    bInmune = true;
}

void Jugador::limpiar() { ObjetoPacman::limpiar(); }

void Jugador::manejarEntrada() {
    if(!bMuerto) {
        // manejar teclas
        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_UP)
            && posicion.getY() > 0)
        {
            velocidad.setY(-velocidadMovimiento);
            velocidad.setX(0);
        }
        else if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_DOWN)
            && (posicion.getY() + altura) < ElJuego::Instancia()->getAlturaJuego() - 10)
        {
            velocidad.setY(velocidadMovimiento);
            velocidad.setX(0);
        }

        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_LEFT) && posicion.getX() > 0)
        {
            velocidad.setX(-velocidadMovimiento);
            velocidad.setY(0);
        }
        else if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_RIGHT)
        && (posicion.getX() + ancho) < ElJuego::Instancia()->getAnchoJuego())
        {
            velocidad.setX(velocidadMovimiento);
            velocidad.setY(0);
        }

//
//        if(ManejadorDeEntrada::Instancia()->isKeyDown(SDL_SCANCODE_SPACE)) {
//            if(m_bulletCounter == m_bulletFiringSpeed) {
//                TheSoundManager::Instance()->playSound("shoot", 0);
//                TheBulletHandler::Instance()->addPlayerBullet(
//                m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
//                m_bulletCounter = 0;
//            }
//
//            m_bulletCounter++;
//        } else { m_bulletCounter = m_bulletFiringSpeed; }
        // */

        /* manejando joysticks */
        //comprobarJoysticks
        if( SDL_NumJoysticks() < 1 ) {
            //printf( "Peligro: No hay Joysticks conectados!\n" );
        } else {
            if(ManejadorDeEntrada::Instancia()->joysticksInicializados()) {
//                if(ManejadorDeEntrada::Instancia()->getButtonState(0, 2)) {
//                    if(m_bulletCounter == m_bulletFiringSpeed)
//                    {
//                        TheSoundManager::Instance()->playSound("shoot", 0);
//                        TheBulletHandler::Instance()->addPlayerBullet(
//                                m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
//                        m_bulletCounter = 0;
//                    }
//
//                    m_bulletCounter++;
//                } else { m_bulletCounter = m_bulletFiringSpeed; }

                if((ManejadorDeEntrada::Instancia()->getAxisX(0, 1) > 0
                    && (posicion.getX() + ancho) < ElJuego::Instancia()->getAnchoJuego())
                    || (ManejadorDeEntrada::Instancia()->getAxisX(0, 1) < 0 && posicion.getX() > 0)) {
                    velocidad.setX(velocidadMovimiento * ManejadorDeEntrada::Instancia()->getAxisX(0, 1));
                }

                if((ManejadorDeEntrada::Instancia()->getAxisY(0, 1) > 0
                    && (posicion.getY() + altura) < ElJuego::Instancia()->getAlturaJuego() - 10 )
                    || (ManejadorDeEntrada::Instancia()->getAxisY(0, 1) < 0 && posicion.getY() > 0)) {
                    velocidad.setY(velocidadMovimiento * ManejadorDeEntrada::Instancia()->getAxisY(0, 1));
                }
            }
        }
    }
}
