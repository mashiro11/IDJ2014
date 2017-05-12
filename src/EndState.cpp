#include "../include/EndState.h"

EndState::EndState(StateData stateData)
{
    wait = false;
    if(stateData.playerVictory == true){
        bg.Open(BG_WIN);
        music.Open(AUDIO_WIN);
    }else{
        bg.Open(BG_LOSE);
        music.Open(AUDIO_LOSE);
    }
    instruction.Initialize(FONT1, 60, Text::TEXT_BLENDED, "PRESS SPACE TO PLAY AGAIN");
    instruction.SetColor(255, 0, 0);
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
    cronometro.Update(dt);
    if(wait == false){
        if(cronometro.Get() > 12){
                cronometro.Restart();
                wait = true;
        }
    }else{
        if(cronometro.Get() > 2) cronometro.Restart();
    }
}

void EndState::Render()
{
    bg.Render(0,0);
    if(wait == true && cronometro.Get() < 2 && cronometro.Get() > 0.5){
        instruction.Render();
    }
}
