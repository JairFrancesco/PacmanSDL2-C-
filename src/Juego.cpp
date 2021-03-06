#include <iostream>
#include "Juego.h"
#include <AdministradorTexturas.h>
#include <ManejadorEntrada.h>
#include <EstadoMainMenu.h>
#include <FabricaObjetosJuego.h>
#include <BotonMenu.h>
#include <GraficoAnimado.h>
#include <Jugador.h>
#include <Sonido.h>
#include <EstadoGameOver.h>
#include <Fantasma.h>
#include <BolaLuz.h>

Juego* Juego::pInstancia = 0;

Juego::Juego():
    pVentana(0),
    pRenderizador(0),
    bRunning(false),
    pMaquinaEstadoJuego(0),
    vidasJugador(3),
    bNivelCompleto(false),
    bCambiandoEstado(false) {

    // Agregar algunos achivos de nivel al array
    vArchivosNivel.push_back("res/gfx/mapa1.tmx");
    vArchivosNivel.push_back("res/gfx/mapa2.tmx");

    // Iniciar en este nivel
    nivelActual = 1;
}

Juego::~Juego() //debemos limpiar para prevenir perdida de memoria
{
    pRenderizador= 0;
    pVentana = 0;
}

bool Juego::iniciar(const char* titulo, int xpos,int ypos, int ancho, int altura, bool fullScreen)
{
    int flags=0;
    if (fullScreen)
    {
        flags=SDL_WINDOW_FULLSCREEN;
    }

    //Almacenar el ancho y la altura del juego
    anchoJuego = ancho;
    alturaJuego = altura;

    if(fullScreen) { flags = SDL_WINDOW_FULLSCREEN; }

    //Intento para iniciar SDL
    if ((SDL_Init(SDL_INIT_EVERYTHING))==0)
    {
        std::cout<<"SDL se inicio Correctamente\n";
        //Iniciar la ventana
        pVentana = SDL_CreateWindow(titulo, xpos, ypos, ancho, altura, flags);
        if (pVentana!=0) //Ventana se inicio correctamente
        {
            std::cout<<"Creación de ventana exitosa\n";
            pRenderizador = SDL_CreateRenderer(pVentana, -1, SDL_RENDERER_ACCELERATED);
            if (pRenderizador!=0) //Renderizador se inicio correctamente
            {
                std::cout<< "Creacion de renderizador exitosa\n";
                SDL_SetRenderDrawColor(pRenderizador, 0,0,0,255);
            }
            else
            {
                std::cout<<"Inicio de renderizador FALLIDO\n";
                return false; //Inicio de renderizador FALLIDO
            }
        }
        else
        {
            std::cout<<"Fallo el inicio de la ventana\n";
            return false; //Fallo el inicio de la ventana
        }
    }
    else
    {
        std::cout<<"Fallo el inicio de SDL\n";
        return false; //Fallo el inicio de SDL
    }
    std::cout<<"Inicio exitoso!!\n";

    //Agregar efectos de sonido.
    AdministradorDeSonidos::Instancia()->cargar("booster.wav", "booster", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("death.wav", "muerte", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("fruit.wav", "fruta", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("ghost_eat.wav", "fantasmaComido", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("intermission.wav", "intermission", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("intro.wav", "introduccion", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("large_pellet.wav", "comidaGrande", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("munch_a.wav", "munch_a", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("munch_b.wav", "munch_b", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("newgame.wav", "nuevoJuego", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("siren.wav", "sirena", SOUND_SFX);
    AdministradorDeSonidos::Instancia()->cargar("vuln.wav", "vuln", SOUND_SFX);

    AdministradorDeSonidos::Instancia()->playMusic("introduccion", -1);
    //AdministradorDeSonidos::Instancia()->playSound("introduccion", 2);

//
//     registrar los tipos para el juego
    LaFabricaDeObjetosJuego::Instancia()->registrarTipo("BotonMenu", new CreadorBotonMenu());
    LaFabricaDeObjetosJuego::Instancia()->registrarTipo("Jugador", new CreadorJugador());
    LaFabricaDeObjetosJuego::Instancia()->registrarTipo("GraficoAnimado", new CreadorGraficoAnimado());
    LaFabricaDeObjetosJuego::Instancia()->registrarTipo("Fantasma", new CreadorFantasma());
    LaFabricaDeObjetosJuego::Instancia()->registrarTipo("BolaLuz", new CreadorBolaDeLuz());

    // Iniciar el estado Menu
    pMaquinaEstadoJuego = new MaquinaEstadoJuego();
    pMaquinaEstadoJuego->cambiarEstado(new EstadoMainMenu());
    //ManejadorDeEntrada::Instancia()->inicializarJoysticks();


    bRunning=true;//Todo se inicio correctamente
    return true;
}


void Juego::setNivelActual(int nivelActual) {
    this->nivelActual = nivelActual;
//    pMaquinaEstadoJuego->cambiarEstado(new GameOverState());
    bNivelCompleto = false;
}

void Juego::render() {
    SDL_RenderClear(pRenderizador);
    pMaquinaEstadoJuego->renderizar();
    SDL_RenderPresent(pRenderizador);
}

void Juego::actualizar() { this->pMaquinaEstadoJuego->actualizar(); }

void Juego::controlarEventos(){ManejadorDeEntrada::Instancia()->actualizar();}

void Juego::limpiar() {
    std::cout << "Limpiando Juego\n";

    ManejadorDeEntrada::Instancia()->limpiar();

    pMaquinaEstadoJuego->limpiar();

    pMaquinaEstadoJuego = 0;
    delete pMaquinaEstadoJuego;

    AdministradorTexturas::Instancia()->limpiarMapaTexturas();
    SDL_DestroyWindow(pVentana);
    SDL_DestroyRenderer(pRenderizador);
    SDL_Quit();
}


