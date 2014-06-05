#include "InputManager.h"

//InputManager& InputManager::
InputManager::InputManager ()
{
    for(int i = 0; i < N_MOUSE_BUTTONS; i++){
            mouseState[ i ] = RELEASED;//OBS se nao funcionar, arrumar
    }
}

InputManager::~InputManager ()
{
    //dtor
}

InputManager& InputManager::GetInstance ()
{
    static InputManager instance;
    return instance;
}

void InputManager::Update ()
{
    //{union SDL_Event event;
//        identificar pela forma SDL_Event event;
//        if(event.type == X), onde X =
//        SDL_KEYDOWN Pressionamento de tecla
//        SDL_KEYUP Uma tecla foi solta
//        SDL_MOUSEBUTTONDOWN Pressionamento de botão do mouse
//        SDL_MOUSEBUTTONUP Botão do mouse foi solto
//        SDL_QUIT Clique no X, Alt+F4, etc.
//    }

    SDL_GetMouseState(&mouseX, &mouseY);
    quitGame = false;

    SDL_Event event;
    SDL_PollEvent(&event);
    for(int i = 0; i < N_MOUSE_BUTTONS; i++){
        if(mouseState[i] == JUST_RELEASED){
                mouseState[i] = RELEASED;
        }else if(mouseState[i] == JUST_PRESSED){
                mouseState[i] = PRESSED;
        }
    }
    for(unordered_map<int, InputState>::iterator aux = keyState.begin(); aux != keyState.end(); aux++){
        if( aux->second == JUST_RELEASED ){
                aux->second = RELEASED;
        }else if(aux->second == JUST_PRESSED){
                aux->second = PRESSED;
        }
    }
    switch(event.type){
        case(SDL_QUIT):
            quitGame = true;
            /*
             * provavelmente será feito algo mais aqui,
             * para que o jogo encerre de forma adequada
             */
            break;
        case(SDL_KEYDOWN):
                if(keyState[event.key.keysym.sym] == PRESSED) break;
                keyState[event.key.keysym.sym] = JUST_PRESSED;
                break;

        case(SDL_KEYUP):
                keyState[event.key.keysym.sym] = JUST_RELEASED;
                break;

        case(SDL_MOUSEBUTTONDOWN):
                mouseState[event.button.button] = JUST_PRESSED;
                break;

        case(SDL_MOUSEBUTTONUP):
                mouseState[event.button.button] = JUST_RELEASED;
                break;
    }
}

bool InputManager::KeyPress (int key)
{
    //aqui não é o caso de ser criada uma posição em keyState.
    if(keyState.find(key) != keyState.end() && keyState.find(key)->second == JUST_PRESSED) return true;
    return false;
}

bool InputManager::KeyRelease (int key)
{
    if(keyState.find(key) != keyState.end() && keyState.find(key)->second == JUST_RELEASED) return true;
    return false;
}

bool InputManager::IsKeyDown (int key)
{
    if(keyState.find(key) != keyState.end() && keyState.find(key)->second == PRESSED) return true;
    return false;
}

bool InputManager::MousePress (int button)
{
    if(mouseState[button] == JUST_PRESSED) return true;
    return false;
}

bool InputManager::MouseRelease (int button)
{
    if(mouseState[button] == JUST_RELEASED) return true;
    return false;
}

bool InputManager::IsMouseDown (int button)
{
    if(mouseState[button] == PRESSED) return true;
    return false;
}

int InputManager::GetMouseX ()
{
    return mouseX;
}

int InputManager::GetMouseY ()
{
    return mouseY;
}

bool InputManager::IsMouseInside (Rect rect)
{
    if( (mouseX > rect.x - Camera::pos.x) && (mouseX < (rect.x + rect.w) - Camera::pos.x) &&
        (mouseY > rect.y - Camera::pos.y) && (mouseY < (rect.y + rect.h) - Camera::pos.y) ){
            return true;
    }
    return false;
}

bool InputManager::ShouldQuit ()
{
    return quitGame;
}
