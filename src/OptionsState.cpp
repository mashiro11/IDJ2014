#include "../include/OptionsState.h"

OptionsState::OptionsState()
{
    bg.Open("img/title.jpg");
    voltar.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_BLENDED, "Voltar");
    voltar.SetColor(255, 0, 0);
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

    if( InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true ){
            requestDelete = true;
    }

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(voltar.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                    InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            requestDelete = true;

        }
    }
}
