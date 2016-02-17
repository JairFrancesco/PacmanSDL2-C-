#include "AdministradorTexturas.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>


AdministradorTexturas* AdministradorTexturas::pInstancia=0;

bool AdministradorTexturas::cargar(std::string fileName, std::string id, SDL_Renderer* pRenderizador)
{
    fileName = "res/gfx/"+fileName;
    SDL_Surface* pTempSurface = IMG_Load(fileName.c_str()); /*c_str"genera una secuencia de caracteres finalizada con null,
    con el mismo contenido que el objeto string, y la devuelve como un puntero a un arreglo de char" */
    if(pTempSurface == 0)
    {
        std::cout << IMG_GetError();
        return false;
    }
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderizador, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    // Todo esta bien, entonces agregamos la textura a nuestra lista.
    if(pTexture != 0)
    {
        mapaTexturas[id] = pTexture;
        return true;
    }
    // si se llego aqui significa que, algo salio mal
    return false;
}


void AdministradorTexturas::dibujar(std::string id, int x, int y, int ancho, int alto, SDL_Renderer* pRenderizador, SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = ancho;
    srcRect.h = destRect.h = alto;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(pRenderizador, mapaTexturas[id], &srcRect, &destRect, 0, 0, flip);
}

void AdministradorTexturas::dibujarFrame(std::string id, int x, int y, int ancho, int alto, int actualFila, int actualFrame, SDL_Renderer *pRenderizador, double angle, int alpha,SDL_RendererFlip flip)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = ancho * actualFrame;
    srcRect.y = alto * actualFila;
    srcRect.w = destRect.w = ancho;
    srcRect.h = destRect.h = alto;
    destRect.x = x;
    destRect.y = y;

    SDL_SetTextureAlphaMod(mapaTexturas[id], alpha);
    SDL_RenderCopyEx(pRenderizador, mapaTexturas[id], &srcRect, &destRect, angle, 0, flip);
}

void AdministradorTexturas::dibujarTile(std::string id, int margin, int spacing, int x, int y, int ancho, int altura, int actualFila, int actualFrame, SDL_Renderer* pRenderizador)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + ancho) * actualFrame;
    srcRect.y = margin + (spacing + altura) * actualFila;
    srcRect.w = destRect.w = ancho;
    srcRect.h = destRect.h = altura;
    destRect.x = x;
    destRect.y = y;

    //std::cout<<"Mapa de texturas[ID]: "<<mapaTexturas[id]<<std::endl;
    SDL_RenderCopyEx(pRenderizador, mapaTexturas[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}


void AdministradorTexturas::limpiarMapaTexturas()
{
    mapaTexturas.clear();
}

void AdministradorTexturas::limpiarDelMapaTexturas(std::string id)
{
    mapaTexturas.erase(id);
}
