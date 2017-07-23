#include "../include/Game.h"

const int INDEX  = -1;
Game* Game::instance = 0;
Game::Game(string title, int width, int height)
{
    srand(time(NULL));
    frameStart = SDL_GetTicks();
    this->width = width;
    this->height = height;
    wait = false;

    if (instance == NULL) instance = this;

    //SDL_Init retorna diferente de zero caso haja um erro.
    int erro = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
    if(erro != 0){
        cout << endl << "Problema no construtor de Game: SDL_Init() retornou diferente de zero" << endl;
        cout << SDL_GetError() << endl;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0){
        cout << endl << "Problema no construtor de Game: IMG_Init() retornou zero" << endl;
        cout << SDL_GetError() << endl;
    }

    if( Mix_Init( MIX_INIT_OGG | MIX_INIT_MP3 ) <= 0){
            cout << endl << "Problema no construtor de Game: Mix_Init() retornou diferente de zero" << endl;
            cout << SDL_GetError() << endl;
    }

    //Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
    if( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
            cout << endl << "Problema no construtor de Game: Mix_OpenAudio() retornou menor que zero" << endl;
            cout << SDL_GetError() << endl;
    }

    if( TTF_Init() != 0 ){
            cout << endl << "Problema no construtor de Game: TTF_Init() retornou diferente de zero" << endl;
            cout << SDL_GetError() << endl;
    }

    //SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if(window == NULL){
        cout << endl << "Problema no construtor de Game: SDL_CreateWindow() retornou NULL" << endl;
        cout << SDL_GetError() << endl;
    }

    //SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags)
    renderer = SDL_CreateRenderer(window, INDEX, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        cout << endl << "Problema no construtor de Game: SDL_CreateRenderer() retornou NULL" << endl;
        cout << SDL_GetError() << endl;
    }
    storedState = NULL;
}

Game::~Game()
{
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    Mix_Quit();
//    TTF_Quit();
    SDL_DestroyWindow(window);
}

Game& Game::GetInstance()
{
    return *instance;
}

void Game::Push(State* state)
{
    storedState = state;
}

void Game::Run()
{
    stateStack.push( storedState );
    storedState = NULL;
    while(stateStack.size() > 0){
        dt = CalculateDeltaTime();
        InputManager::GetInstance().Update();

        if( stateStack.top()->RequestedQuit() == true ){
            break;
        }
        if( stateStack.top()->RequestedDelete() == true ){
            stateStack.pop();
        }
        if(storedState != NULL){
            stateStack.push( storedState );
            storedState = NULL;
        }
        if(stateStack.empty() == false){
            stateStack.top()->Update(dt);
            stateStack.top()->Render();
            SDL_RenderPresent(renderer);
        }
    }
}

float Game::CalculateDeltaTime()
{
    int pastFrameStart = frameStart;
    frameStart  = SDL_GetTicks();
    return (float)(frameStart - pastFrameStart)/1000;
}

float Game::GetDeltaTime()
{
    return dt;
}

int Game::GetWindowWidth()
{
    return width;
}


int Game::GetWindowHeight()
{
    return height;
}

SDL_Renderer* Game::GetRenderer()
{
    return renderer;
}

State& Game::GetCurrentState()
{
    return *GetInstance().stateStack.top();
}
