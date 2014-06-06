#include "TitleState.h"

TitleState::TitleState():
    bg("images/img/title.jpg")
{
    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;
    start.Initialize("images/font/Call me maybe.ttf", 90, Text::TEXT_BLENDED, "Jogar", color);
    start.SetPos(Game::GetInstance().GetWindowWidth()/2,
                 Game::GetInstance().GetWindowHeight()*1/3, true, true);

    options.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Opcoes", color);
    options.SetPos(Game::GetInstance().GetWindowWidth()/2,
                   Game::GetInstance().GetWindowHeight()*1/2, true, true);

    quit.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Sair", color);
    quit.SetPos(Game::GetInstance().GetWindowWidth()/2,
                Game::GetInstance().GetWindowHeight()*2/3, true, true);
}

void TitleState::Update(float dt)
{
    Input();
    start.cronometro.Update(dt);
    if( start.cronometro.Get() > 2 ) start.cronometro.Restart();
}

void TitleState::Render()
{
    bg.Render(0,0);
    if(start.cronometro.Get() < 2 && start.cronometro.Get() > 0.5){
            start.Render();
            options.Render();
            quit.Render();
    }
}

void TitleState::Input(){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) == true){
        requestQuit = true;
    }

    if(InputManager::GetInstance().KeyPress(SDLK_SPACE) == true){
        StageState* state = new StageState();
        Game::GetInstance().Push(state);
    }

    if(InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(start.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                          InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            StageState* state = new StageState();
            Game::GetInstance().Push(state);

        }else if(options.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                  InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            OptionsState* state = new OptionsState();
            Game::GetInstance().Push(state);

        }else if(quit.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                               InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            requestQuit = true;
        }

    }
}
