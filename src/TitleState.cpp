#include "../include/TitleState.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG

TitleState::TitleState()
{
    bg.Open(TITLE_STATE_BACKGROUND);
    mainTheme.Open(TITLE_STATE_MUSIC);
    mainTheme.Play(-1);
    menu.AddMenuOption(TITLE_STATE_MENU_OP1);
    menu.AddMenuOption(TITLE_STATE_MENU_OP2);
    menu.AddMenuOption(TITLE_STATE_MENU_OP3);

    menu.SetDirection(HORIZONTAL, TITLE_STATE_MENU_SPACEMENT);
    menu.SetPosition(TITLE_STATE_MENU_X, TITLE_STATE_MENU_Y, true);
}

void TitleState::Update(float dt)
{
    Input();
    menu.Update(dt);
    switch(menu.GetSelectedOption()){
        case TITLE_START:
            Game::GetInstance().Push(new CharacterState());
            mainTheme.Stop();
            break;
        case TITLE_OPTIONS:
            Game::GetInstance().Push(new OptionsState());
            break;
        case TITLE_QUIT:
            requestQuit = true;
    }
}

void TitleState::Render()
{
    bg.Render( (GAME_WIDTH-bg.GetWidth())/2 );//tempor�rio
    menu.Render();
}

void TitleState::Input(){
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) == true){
        requestQuit = true;
    }

    if(InputManager::GetInstance().KeyPress(SDLK_SPACE) == true){
        Game::GetInstance().Push(new CharacterState());
    }

    if(InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
