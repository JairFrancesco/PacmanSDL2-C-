#include "ManejadorEntrada.h"


ManejadorDeEntrada* ManejadorDeEntrada::pInstancia = 0;

ManejadorEntrada::ManejadorEntrada() :  keyStates(0), bJoysticksInicializados(false), mousePosition(new Vector2D(0,0))
{
    // Crear estados de boton para el mouse
    for(int i = 0; i < 3; i++)
    {
        vMouseButtonStates.push_back(false);
    }
}

ManejadorEntrada::~ManejadorEntrada()
{
    //Borrar cualquier cosa que hayamos creado dinamicamente
    delete keyStates;
    delete mousePosition;

    // Limpiar nuestos arrays
    vJoystickValues.clear();
    vJoysticks.clear();
    vButtonStates.clear();
    vMouseButtonStates.clear();
}

void ManejadorEntrada::limpiar()
{
    // Debemos limpiar nosotros mismos los joysticks que hemos abierto
    if(bJoysticksInicializados)
    {
        for(unsigned int i = 0; i < SDL_NumJoysticks(); i++)
        {
            SDL_JoystickClose(vJoysticks[i]);
        }
    }
}

void ManejadorEntrada::inicializarJoysticks()
{
    // Si un no hemos inicializado el subsistema joystick, lo haremos aqui
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
    {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    // Obtener el numero de Joystick, saltar init si no hay ninguno
    if(SDL_NumJoysticks() > 0)
    {
        for(int i = 0; i < SDL_NumJoysticks(); i++)
        {
            // Crear un nuevo Joystick
            SDL_Joystick* joy = SDL_JoystickOpen(i);

            // si el joystick abrió correctamente necesitamos poblar nuestros arrays
            if(SDL_JoystickOpen(i))
            {
                // Empujar en el array a cerrar mas tarde ?
                vJoysticks.push_back(joy);

                // Crear un par de valores para los ejes, un vector para cada palo
                vJoystickValues.push_back(std::make_pair(new Vector2D(0,0),new Vector2D(0,0)));

                // Crear un array para contener los valores del boton
                std::vector<bool> tempButtons;

                // Llenar el array con un valor falso para cada boton
                for(int j = 0; j <  SDL_JoystickNumButtons(joy); j++)
                {
                    tempButtons.push_back(false);
                }
                // Colocar el array de botones dentro del array de estados de botones
                vButtonStates.push_back(tempButtons);
            }
            else
            {
                // if there was an error initialising a joystick we want to know about it
                // si hubo un error inicializando un joystick, nosotros queremos saber cual.
                std::cout << SDL_GetError();
            }
        }

        // Activar los eventos del Joystick
        SDL_JoystickEventState(SDL_ENABLE);
        bJoysticksInicializados = true;

        std::cout << "Inicializado " << vJoysticks.size() << " joystick(s)";
    }
    else
    {
        bJoysticksInicializados = false;
    }
}


void ManejadorEntrada::reiniciar()
{
    vMouseButtonStates[LEFT] = false;
    vMouseButtonStates[RIGHT] = false;
    vMouseButtonStates[MIDDLE] = false;
}

bool ManejadorEntrada::isKeyDown(SDL_Scancode key) const
{
    if(keyStates != 0)
    {
        if(keyStates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

int ManejadorEntrada::getAxisX(int joy, int stick) const //Get eje x
{
    if(vJoystickValues.size() > 0)
    {
        if(stick == 1)
        {
            return vJoystickValues[joy].first->getX();
        }
        else if(stick == 2)
        {
            return vJoystickValues[joy].second->getX();
        }
    }
    return 0;
}

int ManejadorEntrada::getAxisY(int joy, int stick) const
{
    if(vJoystickValues.size() > 0)
    {
        if(stick == 1)
        {
            return vJoystickValues[joy].first->getY();
        }
        else if(stick == 2)
        {
            return vJoystickValues[joy].second->getY();
        }
    }
    return 0;
}

bool ManejadorEntrada::getButtonState(int joy, int buttonNumber) const
{
    return vButtonStates[joy][buttonNumber];
}

bool ManejadorEntrada::getMouseButtonState(int buttonNumber) const
{
    return vMouseButtonStates[buttonNumber];
}

Vector2D* ManejadorEntrada::getMousePosition() const
{
    return mousePosition;

}

void ManejadorEntrada::actualizar()
{
    SDL_Event evento;
    while(SDL_PollEvent(&evento))
    {
        switch (evento.type)
        {
            case SDL_QUIT:
                ElJuego::Instancia()->salir();
                break;

            case SDL_JOYAXISMOTION:
                onJoystickAxisMove(evento);
                break;

            case SDL_JOYBUTTONDOWN:
                onJoystickButtonDown(evento);
                break;

            case SDL_JOYBUTTONUP:
                onJoystickButtonUp(evento);
                break;

            case SDL_MOUSEMOTION:
                onMouseMove(evento);
                break;

            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown(evento);
                break;

            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp(evento);
                break;

            case SDL_KEYDOWN:
                onKeyDown();
                break;

            case SDL_KEYUP:
                onKeyUp();
                break;

            default:
                break;
        }
    }
}


void ManejadorEntrada::onKeyDown()
{
    keyStates = SDL_GetKeyboardState(0);
}

void ManejadorEntrada::onKeyUp()
{
    keyStates = SDL_GetKeyboardState(0);
}

void ManejadorEntrada::onMouseMove(SDL_Event &evento)
{
    mousePosition->setX(evento.motion.x);
    mousePosition->setY(evento.motion.y);
}

void ManejadorEntrada::onMouseButtonDown(SDL_Event &evento)
{
    if(evento.button.button == SDL_BUTTON_LEFT)
    {
        vMouseButtonStates[LEFT] = true;
    }

    if(evento.button.button == SDL_BUTTON_MIDDLE)
    {
        vMouseButtonStates[MIDDLE] = true;
    }

    if(evento.button.button == SDL_BUTTON_RIGHT)
    {
        vMouseButtonStates[RIGHT] = true;
    }
}

void ManejadorEntrada::onMouseButtonUp(SDL_Event &evento)
{
    if(evento.button.button == SDL_BUTTON_LEFT)
    {
        vMouseButtonStates[LEFT] = false;
    }

    if(evento.button.button == SDL_BUTTON_MIDDLE)
    {
        vMouseButtonStates[MIDDLE] = false;
    }

    if(evento.button.button == SDL_BUTTON_RIGHT)
    {
        vMouseButtonStates[RIGHT] = false;
    }
}

void ManejadorEntrada::onJoystickAxisMove(SDL_Event &evento)
{
    int whichOne = evento.jaxis.which;

    // Stick izquierdo, mover a la derecha o a la izquierda
    if(evento.jaxis.axis == 0)
    {
        if (evento.jaxis.value > joystickDeadZone)
        {
            vJoystickValues[whichOne].first->setX(1);
        }
        else if(evento.jaxis.value < -joystickDeadZone)
        {
            vJoystickValues[whichOne].first->setX(-1);
        }
        else
        {
            vJoystickValues[whichOne].first->setX(0);
        }
    }

    // Stick izquierdo, subir o bajar
    if(evento.jaxis.axis == 1)
    {
        if (evento.jaxis.value > joystickDeadZone)
        {
            vJoystickValues[whichOne].first->setY(1);
        }
        else if(evento.jaxis.value < -joystickDeadZone)
        {
            vJoystickValues[whichOne].first->setY(-1);
        }
        else
        {
            vJoystickValues[whichOne].first->setY(0);
        }
    }

    // Stick derecho, mover a la derecha o a la izquierda
    if(evento.jaxis.axis == 3)
    {
        if (evento.jaxis.value > joystickDeadZone)
        {
            vJoystickValues[whichOne].second->setX(1);
        }
        else if(evento.jaxis.value < -joystickDeadZone)
        {
            vJoystickValues[whichOne].second->setX(-1);
        }
        else
        {
            vJoystickValues[whichOne].second->setX(0);
        }
    }

    // stick derecho, mover arriba o abajo
    if(evento.jaxis.axis == 4)
    {
        if (evento.jaxis.value > joystickDeadZone)
        {
            vJoystickValues[whichOne].second->setY(1);
        }
        else if(evento.jaxis.value < -joystickDeadZone)
        {
            vJoystickValues[whichOne].second->setY(-1);
        }
        else
        {
            vJoystickValues[whichOne].second->setY(0);
        }
    }
}

void ManejadorEntrada::onJoystickButtonDown(SDL_Event &evento)
{
    int whichOne = evento.jaxis.which;

    vButtonStates[whichOne][evento.jbutton.button] = true;
}

void ManejadorEntrada::onJoystickButtonUp(SDL_Event &evento)
{
    int whichOne = evento.jaxis.which;

    vButtonStates[whichOne][evento.jbutton.button] = false;
}
