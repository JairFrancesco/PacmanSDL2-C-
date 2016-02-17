//Using SDL and standard IO
#include <stdio.h>
#include <iostream>
#include <Juego.h>

using namespace std;

const int FPS=60;
const int DELAY_TIME = 1000.0f / FPS;


int main( int argc, char* args[] )
{
    Uint32 inicioFrame, tiempoFrame;

    std::cout<<"Intentando iniciar el juego";
    if (ElJuego::Instancia()->iniciar("Pacman con SDL2", 300, 10, 640, 704,false))//Si en lugar de 0 colocamos el flag SDL_WINDOW_FULLSCREEN el juego aparecera a pantalla completa
    // 704 = 32*22
    // 640 = 32*20
    {
        std::cout<< "Inicio del juego exitoso!";
        while (ElJuego::Instancia()->running())
        {
            inicioFrame = SDL_GetTicks();
            ElJuego::Instancia()->controlarEventos();
            ElJuego::Instancia()->actualizar();
            ElJuego::Instancia()->render();
            tiempoFrame = SDL_GetTicks() - inicioFrame;
            if (tiempoFrame<DELAY_TIME)
            {
                    SDL_Delay((int)(DELAY_TIME-tiempoFrame));
            }

        }
    }
    else
    {
        std::cout<<"Inicio de juego fallido - "<<SDL_GetError()<<"\n";
        return -1;
    }
    std::cout<<"Cerrando juego...\n";
    ElJuego::Instancia()->limpiar();
    return 0;
}
