#ifndef SONIDO_H
#define SONIDO_H

#include <iostream>
#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>

enum tipo_sonido
{
    SOUND_MUSIC = 1,
    SOUND_SFX = 1
};

class Sonido
{
public:

    static Sonido* Instancia()
    {
        if(pInstancia == 0)
        {
            pInstancia = new Sonido();
            return pInstancia;
        }
        return pInstancia;
    }

    bool cargar(std::string fileName, std::string id, tipo_sonido tipo);

    void playSound(std::string id, int loop);
    void playMusic(std::string id, int loop);

private:

    static Sonido* pInstancia;

    std::map<std::string, Mix_Chunk*> m_sfxs;
    std::map<std::string, Mix_Music*> m_music;

    Sonido();
    ~Sonido();

    Sonido(const Sonido&);
	Sonido& operator=(const Sonido&);
};

typedef Sonido AdministradorDeSonidos;

#endif
