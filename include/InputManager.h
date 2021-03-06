#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#ifdef _WIN32
	#include <SDL.h>
#else
	#include <SDL2/SDL.h>
#endif
#include <unordered_map>
#include <iostream>

#include "Rect.h"
#include "Camera.h"

#define SPACE_KEY          SDLK_SPACE
#define LEFT_ARROW_KEY     SDLK_LEFT
#define RIGHT_ARROW_KEY    SDLK_RIGHT
#define UP_ARROW_KEY       SDLK_UP
#define DOWN_ARROW_KEY     SDLK_DOWN
#define ESCAPE_KEY         SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON  SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT

using std::unordered_map;
using std::cout;
using std::endl;

const int N_MOUSE_BUTTONS = 5;

class InputManager
{
    public:
        void Update ();
        bool KeyPress (int key);
        bool KeyRelease (int key);
        bool IsKeyDown (int key);
        bool MousePress (int button);
        bool MouseRelease (int button);
        bool IsMouseDown (int button);
        int GetMouseX ();
        int GetMouseY ();
        bool IsMouseInside (Rect rect);
        bool ShouldQuit ();
        static InputManager& GetInstance();
    protected:
        /* vazio */
    private:
        InputManager();
        ~InputManager();
        enum InputState
        {
             RELEASED = 0,
             JUST_RELEASED,
             PRESSED,
             JUST_PRESSED
        };
        InputState mouseState[N_MOUSE_BUTTONS];
        unordered_map<int, InputState> keyState;
        bool quitGame;
        int mouseX;
        int mouseY;
};
#endif // INPUTMANAGER_H
