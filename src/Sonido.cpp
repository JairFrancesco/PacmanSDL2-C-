#include "Sonido.h"

Sonido* Sonido::pInstancia;

Sonido::Sonido()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024)!= 0)
    {
        std::cout << "No se pudo iniciar mixer:  " << Mix_GetError() << std::endl;
    }

   /*if ( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) ==-1)
    {
        std::cout << "Could not init mixer" << Mix_GetError() << std::endl;
    }*/
}

Sonido::~Sonido()
{;
    Mix_CloseAudio();
}

bool Sonido::cargar(std::string fileName, std::string id, tipo_sonido tipo)
{
    fileName = "res/sfx/" + fileName;
    if(tipo == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if(pMusic == 0)
        {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }

        m_music[id] = pMusic;
        return true;
    }
    else if(tipo == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if(pChunk == 0)
        {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }

        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

void Sonido::playMusic(std::string id, int loop)
{
    Mix_PlayMusic(m_music[id], loop);
}

void Sonido::playSound(std::string id, int loop)
{
    Mix_PlayChannel(-1, m_sfxs[id], loop);
}
