#ifndef GAME_H
#define GAME_H

//#define DEBUG
#define ANDRE
//#define MASHIRO

#include <iostream>
#include <vector>
#include <memory>
#include <time.h>
//#include <stdlib.h>
#include <stack>


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include "State.h"

/* SDL_image.h
 *
 * Biblioteca responsável por facilitar/permitir carregamento
 * de imagens de extensões .jpg, .gif, .png, com ou sem canal alfa.
 */

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;
using std::stack;

class State;
class Game
{
    public:
        Game(string title, int width, int height);
        ~Game();

        SDL_Renderer* GetRenderer();
        static Game& GetInstance();
        static State& GetCurrentState();

        void Push(State* state);

        void Run();
        int GetWindowWidth();//implementar
        int GetWindowHeight();//implementar

        float GetDeltaTime();//vai ser util?

    protected:
        /* vazio */
    private:
        int width;
        int height;
        int frameStart;
        float dt;
        float CalculateDeltaTime();

        static Game* instance;

        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        //stack<unique_ptr<State>> stateStack;
        stack<State*> stateStack;

        bool wait;
};
#endif // GAME_H
