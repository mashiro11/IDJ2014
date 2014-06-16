#include "CharacterState.h"

CharacterState::CharacterState()
{
    #ifdef ANDRE
    bg.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/title.jpg");
    selecao.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/selecao.png");
    selecionado.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/selecionado.png");
    #endif
    #ifdef MASHIRO
    bg.Open("images/img/title.jpg");
    selecao.Open("images/img/selecao.png");
    selecionado.Open("images/img/selecionado.png");
    #endif

    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;
    #ifdef ANDRE
    instruction.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 55, Text::TEXT_BLENDED, "Escolha", color);
    instruction.SetPos(Game::GetInstance().GetWindowWidth()/2,
                 Game::GetInstance().GetWindowHeight()*1/20, true, true);

    inicio.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 50, Text::TEXT_BLENDED, "Jogar", color);
    inicio.SetPos(Game::GetInstance().GetWindowWidth()*12/13,
                 Game::GetInstance().GetWindowHeight()*14/15, true, true);
    #endif
    #ifdef MASHIRO
    instruction.Initialize("images/font/Call me maybe.ttf", 55, Text::TEXT_BLENDED, "Escolha", color);
    instruction.SetPos(Game::GetInstance().GetWindowWidth()/2,
                 Game::GetInstance().GetWindowHeight()*1/20, true, true);

    inicio.Initialize("images/font/Call me maybe.ttf", 50, Text::TEXT_BLENDED, "Jogar", color);
    inicio.SetPos(Game::GetInstance().GetWindowWidth()*12/13,
                 Game::GetInstance().GetWindowHeight()*14/15, true, true);
    #endif

    PopulaArray();
}

//~CharacterState()
//{
//}

void CharacterState::Update(float dt)
{
    Input();
    int offSetY = 150, offSetX = 650;
    for(int k = 0; k < selecionadoArray.size(); k++){
        if(k == 1){
            offSetX = 850;
            offSetY = 150;
        }else if(k == 2){
            offSetX = 650;
            offSetY = 300;
        }else if(k == 3){
            offSetX = 850;
            offSetY = 300;
        }

        if(k%2 == 0){
            selecionadoArray[k].SetX(offSetX);
            selecionadoArray[k].SetY(offSetY);
        }else{
            selecionadoArray[k].SetX(offSetX);
            selecionadoArray[k].SetY(offSetY);
        }

    }
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
        for(int j = 0; j < selecionadoArray.size(); j++){
            if(selecionadoArray[j].box.IsInside(InputManager::GetInstance().GetMouseX(),
                                           InputManager::GetInstance().GetMouseY())){
                selecionadoArray.erase(selecionadoArray.begin() + j);
                DeletaPersonagem(j);
            }
        }

        if(inicio.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                          InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
            requestDelete = true;
            StageState* state = new StageState(characters);
            Game::GetInstance().Push(state);
        }

        for(int i = 0; i < characterArray.size(); i++){
            if(characterArray[i].box.IsInside(InputManager::GetInstance().GetMouseX(),
                                           InputManager::GetInstance().GetMouseY())){
                if(selecionadoArray.size() < 4){
                    if(NaoDentro(i) == true){
                        InserePersonagem(i);
                        StillAnimation aux = characterArray[i];
                        selecionadoArray.push_back(aux);
                    }
                }
            }
        }


    }
}

void CharacterState::PopulaArray()
{
#ifdef ANDRE
    Sprite botao("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface.png");
    Sprite botao2("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface2.png");
    Sprite botao3("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface3.png");
    Sprite botao4("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface4.png");
    Sprite botao5("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface5.png");
    Sprite botao6("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface6.png");
#endif
#ifdef MASHIRO
    Sprite botao("images/img/penguinface.png");
    Sprite botao2("images/img/penguinface2.png");
    Sprite botao3("images/img/penguinface3.png");
    Sprite botao4("images/img/penguinface4.png");
    Sprite botao5("images/img/penguinface5.png");
    Sprite botao6("images/img/penguinface6.png");
#endif

    StillAnimation* botaoAnim = new StillAnimation(150, 150 + 75*characterArray.size(), 0, botao, 50, false);
    characterArray.emplace_back(*botaoAnim);

    StillAnimation* botaoAnim2 = new StillAnimation(330, 150, 0, botao2, 50, false);
    characterArray.emplace_back(*botaoAnim2);

    StillAnimation* botaoAnim3 = new StillAnimation(150, 150 + 75*characterArray.size(), 0, botao3, 50, false);
    characterArray.emplace_back(*botaoAnim3);

    StillAnimation* botaoAnim4 = new StillAnimation(330, 150 + 50*characterArray.size(), 0, botao4, 50, false);
    characterArray.emplace_back(*botaoAnim4);

    StillAnimation* botaoAnim5 = new StillAnimation(150, 150 + 75*characterArray.size(), 0, botao5, 50, false);
    characterArray.emplace_back(*botaoAnim5);

    StillAnimation* botaoAnim6 = new StillAnimation(330, 150 + 60*characterArray.size(), 0, botao6, 50, false);
    characterArray.emplace_back(*botaoAnim6);

}

void CharacterState::InserePersonagem(int index)
{
    switch(index){
    case(0):
        characters.robo.push_back("Joao");
        break;
    case(1):
        characters.robo.push_back("Joana");
        break;
    case(2):
        characters.robo.push_back("Maria");
        break;
    case(3):
        characters.robo.push_back("Mario");
        break;
    case(4):
        characters.robo.push_back("Jose");
        break;
    case(5):
        characters.robo.push_back("Josea");
        break;
    }

}

void CharacterState::DeletaPersonagem(int index)
{
    switch(index){
    case(0):
        characters.robo.erase(characters.robo.begin());
        break;
    case(1):
        characters.robo.erase(characters.robo.begin() + 1);
        break;
    case(2):
        characters.robo.erase(characters.robo.begin() + 2);
        break;
    case(3):
        characters.robo.erase(characters.robo.begin() + 3);
        break;
    }
}

bool CharacterState::NaoDentro(int index)
{
    string nome;

    switch(index){
    case(0):
        nome = "Joao";
        break;
    case(1):
        nome = "Joana";
        break;
    case(2):
        nome = "Maria";
        break;
    case(3):
        nome = "Mario";
        break;
    case(4):
        nome = "Jose";
        break;
    case(5):
        nome = "Josea";
        break;
    }

    for(int i = 0; i < characters.robo.size(); i++){
        if(characters.robo[i] == nome){
            return false;
        }
    }

    return true;
}
