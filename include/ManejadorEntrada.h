#ifndef MANEJADORENTRADA_H
#define MANEJADORENTRADA_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <Vector2D.h>
#include <Juego.h>


enum botones_mouse
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

class ManejadorEntrada
{
    public:
        static ManejadorEntrada* Instancia()
        {
            if (pInstancia==0)
            {
                pInstancia = new ManejadorEntrada();
            }
            return pInstancia;
        }
        //Iniciar Joysticks
        void inicializarJoysticks();
        bool joysticksInicializados() { return bJoysticksInicializados; }

        void reiniciar();

        //Actualizar y limpiar el manejador de entradas
        void actualizar();
        void limpiar();

        //Eventos de teclado
        bool isKeyDown(SDL_Scancode key) const;

        //Eventos de Joystick
        int getAxisX(int joy, int stick) const;
        int getAxisY(int joy, int stick) const;
        bool getButtonState(int joy, int buttonNumber) const;

        //Eventos de Mouse
        bool getMouseButtonState(int buttonNumber) const;
        Vector2D* getMousePosition() const;


    protected:
    private:

        ManejadorEntrada();
        ~ManejadorEntrada();
        ManejadorEntrada(const ManejadorEntrada&);
        ManejadorEntrada& operator=(const ManejadorEntrada&);

        //Funciones privadas para manejar diferentes tipos de eventos
        //eventos para manejar teclado

        void onKeyDown();
        void onKeyUp();
        void limpiarKeyStates(){keyStates = 0;};

        //Manejar eventos del mouse
        void onMouseMove(SDL_Event& evento);
        void onMouseButtonDown(SDL_Event& evento);
        void onMouseButtonUp(SDL_Event& evento);

        //Manejar eventos de Joystick
        void onJoystickAxisMove(SDL_Event& evento);
        void onJoystickButtonDown(SDL_Event& evento);
        void onJoystickButtonUp(SDL_Event& evento);

        //Variables miembro
        //Teclado
        const Uint8* keyStates;

        //Joystick
        std::vector<std::pair<Vector2D*, Vector2D*> > vJoystickValues;
        std::vector<SDL_Joystick*> vJoysticks;
        std::vector<std::vector<bool> > vButtonStates;
        bool bJoysticksInicializados;
        static const int joystickDeadZone = 10000;

        //Mouse
        std::vector<bool> vMouseButtonStates;
        Vector2D* mousePosition;

        //Unica Instancia
        static ManejadorEntrada* pInstancia;


};

typedef ManejadorEntrada ManejadorDeEntrada;
#endif // MANEJADORENTRADA_H
