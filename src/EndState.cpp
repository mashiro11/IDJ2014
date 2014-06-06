#include "EndState.h"

EndState::EndState(StateData stateData)
{
    wait = false;
    if(stateData.playerVictory == true){
        bg.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/win.jpg");
        music.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/audio/endStateWin.ogg");
    }else{
        bg.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/lose.jpg");
        music.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/audio/endStateLose.ogg");
    }
    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;
    instruction.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 60, Text::TEXT_BLENDED, "PRESS SPACE TO PLAY AGAIN", color);
    instruction.SetPos(Game::GetInstance().GetWindowWidth()/2,
                       Game::GetInstance().GetWindowHeight()*5/6,
                       true, true);
    music.Play(-1);
}

void EndState::Update(float dt)
{
    if(InputManager::GetInstance().ShouldQuit() == true ||
       InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true){
        music.Stop();
        requestQuit = true;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE) == true){
        music.Stop();
        requestDelete = true;
    }
    instruction.cronometro.Update(dt);
    if(wait == false){
        if(instruction.cronometro.Get() > 12){
                instruction.cronometro.Restart();
                wait = true;
        }
    }else{
        if(instruction.cronometro.Get() > 2) instruction.cronometro.Restart();
    }
}

void EndState::Render()
{
    bg.Render(0,0);
    if(wait == true && instruction.cronometro.Get() < 2 && instruction.cronometro.Get() > 0.5){
        instruction.Render();
    }
}
