#ifndef ADMINISTRADORTEXTURAS_H
#define ADMINISTRADORTEXTURAS_H

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>

class AdministradorTexturas
{
    public:
        //(Clave, valor)

        static AdministradorTexturas* Instancia()
        {
            if(pInstancia == 0)
            {
                pInstancia = new AdministradorTexturas();
                return pInstancia;
            }

            return pInstancia;
        }
        bool cargar(std::string filename, std::string id, SDL_Renderer* pRenderizador);
        void limpiarMapaTexturas();
        void limpiarDelMapaTexturas(std::string id);

        // draw
        void dibujar(std::string id, int x, int y, int ancho, int altura, SDL_Renderer* pRenderizador, SDL_RendererFlip flip = SDL_FLIP_NONE);

        // drawframe
        void dibujarFrame(std::string id, int x, int y, int ancho, int altura, int actualFila, int actualFrame,
        SDL_Renderer* pRenderizador, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void dibujarTile(std::string id, int margin, int spacing, int x, int y, int ancho, int alto, int actualFila, int actualFrame, SDL_Renderer *pRenderizador);

        std::map<std::string, SDL_Texture*> getMapaTexturas() {return mapaTexturas;}

    protected:
    private:

        AdministradorTexturas(){};
        ~AdministradorTexturas(){};
        AdministradorTexturas(const AdministradorTexturas&);
        AdministradorTexturas& operator=(const AdministradorTexturas&);

        std::map<std::string, SDL_Texture*> mapaTexturas;
        static AdministradorTexturas* pInstancia;

};

typedef AdministradorTexturas AdministradorDeTexturas;//asignar un nombre alternativo a tipos existentes,
#endif // ADMINISTRADORTEXTURAS_H
