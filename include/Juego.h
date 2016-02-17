#ifndef JUEGO_H
#define JUEGO_H
#include <vector>
#include <MaquinaEstadoJuego.h>
#include <SDL2/SDL.h>

class Juego
{
    public:
        //Funciones miembro
        bool iniciar(const char* titulo, int xpos,int ypos, int ancho, int altura, bool fullScreen);
        void render();
        void actualizar();
        void controlarEventos();
        void limpiar();

        static Juego* Instancia()
        {
            if(pInstancia == 0)
            {
                pInstancia = new Juego();
                return pInstancia;
            }
            return pInstancia;
        }

        SDL_Renderer* getRenderizador() const { return pRenderizador; }
        SDL_Window* getVentana() const {return this->pVentana;}
        MaquinaEstadoJuego* getMaquinaEstadoJuego() {return pMaquinaEstadoJuego;}

        void setVidasJugador(int vidas) {vidasJugador=vidas;}
        int getVidasJugador() {return vidasJugador;}

        void setNivelActual(int nivelActual);
        const int getNivelActual() {return nivelActual;}

        void setNivelSiguiente(int nivelSiguiente) {this->nivelSiguiente=nivelSiguiente;}
        const int getNivelSiguiente() {return nivelSiguiente;}

        void setNivelCompleto(bool nivelCompleto) {this->bNivelCompleto = nivelCompleto;}
        const bool getNivelCompleto(){return this->bNivelCompleto;}

        bool running() {return bRunning;}

        void salir() { bRunning = false;}

        int getAnchoJuego() const {return this->anchoJuego;}
        int getAlturaJuego() const {return this->alturaJuego;}
        //float getVelocidadScroll {return velocidadScroll;}

        bool getCambiandoEstado() {return bCambiandoEstado;}
        void setCambiandoEstado(bool ce) { this->bCambiandoEstado = ce;}

        std::vector<std::string> getArchivosNivel() {return this->vArchivosNivel;}

    private:
        //Campos
        static Juego* pInstancia;
        MaquinaEstadoJuego* pMaquinaEstadoJuego;
        SDL_Window* pVentana;
        SDL_Renderer* pRenderizador;

        int anchoJuego;
        int alturaJuego;
        //float velocidadScroll

        int vidasJugador;

        int nivelActual;
        int nivelSiguiente;
        bool bNivelCompleto;
        bool bRunning;
        bool bCambiandoEstado;
        std::vector<std::string> vArchivosNivel;

        //Funciones Miembro
        Juego();
        ~Juego();
        Juego(const Juego&);
        Juego& operator=(const Juego&);

};

typedef Juego ElJuego;

#endif // JUEGO_H
