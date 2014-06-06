#include "TitleState.h"

TitleState::TitleState()
{
#ifdef ANDRE
    bg.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/title.jpg");
#endif
#ifdef MASHIRO
    bg.Open("images/img/title.jpg");
#endif
    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;
#ifdef ANDRE
    start.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 90, Text::TEXT_BLENDED, "Jogar", color);
    options.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Opcoes", color);
    quit.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Sair", color);
#endif
#ifdef MASHIRO
    start.Initialize("images/font/Call me maybe.ttf", 90, Text::TEXT_BLENDED, "Jogar", color);
    options.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Opcoes", color);
    quit.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Sair", color);
#endif
    start.SetPos(Game::GetInstance().GetWindowWidth()/2,
                 Game::GetInstance().GetWindowHeight()*1/3, true, true);

    options.SetPos(Game::GetInstance().GetWindowWidth()/2,
                   Game::GetInstance().GetWindowHeight()*1/2, true, true);

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
        CharacterState* state = new CharacterState();
        Game::GetInstance().Push(state);
    }

    if(InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(start.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                          InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            //CharacterState* state = new CharacterState();
            CharacterState* state = new CharacterState();
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
