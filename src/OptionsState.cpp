#include "OptionsState.h"

OptionsState::OptionsState()
{
#ifdef ANDRE
    bg.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/title.jpg");
#endif
#ifdef MASHIRO
    bg.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/title.jpg");
#endif
    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;

#ifdef ANDRE
    voltar.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Voltar", color);
#endif
#ifdef MASHIRO
    voltar.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Voltar", color);
#endif
    voltar.SetPos(150, 500, true, true);
}

void OptionsState::Render(){
    bg.Render(0,0);
    voltar.Render(0,0);
}

void OptionsState::Update(float dt){
    Input();
}

void OptionsState::Input(){

    if(InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(voltar.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                    InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            requestDelete = true;

        }
    }
}
