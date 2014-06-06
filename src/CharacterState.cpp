#include "CharacterState.h"

CharacterState::CharacterState()
{
    bg.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/title.jpg");
    selecao.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/selecao.png");
    selecionado.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/selecionado.png");

    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;
    instruction.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 55, Text::TEXT_BLENDED, "Escolha", color);
    instruction.SetPos(Game::GetInstance().GetWindowWidth()/2,
                 Game::GetInstance().GetWindowHeight()*1/20, true, true);

    inicio.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 50, Text::TEXT_BLENDED, "Jogar", color);
    inicio.SetPos(Game::GetInstance().GetWindowWidth()*12/13,
                 Game::GetInstance().GetWindowHeight()*14/15, true, true);

    PopulaArray();
}

//~CharacterState()
//{
//}

void CharacterState::Update(float dt)
{
    Input();
}

void CharacterState::Render()
{
    bg.Render(0,0);
    selecao.Render(50,70);
    selecionado.Render(bg.GetWidth()/2 + 50, 70);
    instruction.Render(0,0);
    inicio.Render(0,0);

    for(int i = 0; i < characterArray.size(); i++){
        characterArray[i].Render(0,0);
    }

    for(int j = 0; j < selecionadoArray.size(); j++){
        selecionadoArray[j].Render(0,0);
    }
}

void CharacterState::Input()
{
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY) == true){
        requestDelete = true;
    }

    if(InputManager::GetInstance().ShouldQuit()){
        requestQuit = true;
    }

    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        if(inicio.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                          InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            requestDelete = true;
            StageState* state = new StageState();
            Game::GetInstance().Push(state);
        }
        for(int i = 0; i < characterArray.size(); i++){
            if(characterArray[i].box.IsInside(InputManager::GetInstance().GetMouseX(),
                                           InputManager::GetInstance().GetMouseY())){
                if(selecionadoArray.size() < 6){
                    StillAnimation aux = characterArray[i];
                    aux.SetX(characterArray[i].box.RectCenterX() + 520);
                    aux.SetY(characterArray[i].box.RectCenterY());
                    selecionadoArray.push_back(aux);
                    cout << "Adicionou" << endl;
                }
            }
        }


    }
}

void CharacterState::PopulaArray()
{
    Sprite botao("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface.png");
    StillAnimation* botaoAnim = new StillAnimation(150, 150 + 75*characterArray.size(), 0, botao, 50, false);
    characterArray.emplace_back(*botaoAnim);


    //objectArray.emplace_back(objeto);
}
