#include "../include/CharacterState.h"

CharacterState::CharacterState()
{
    bg.Open(CHARACTER_STATE_BACKGROUND_FILE);
    selecao.Open(CHARACTER_STATE_TOSELECT_FILE);
    selecionado.Open(CHARACTER_STATE_SELECTED_FILE);

    instruction.Initialize(CHARACTER_STATE_TYPE_FILE, 55, Text::TEXT_BLENDED, "Escolha");
    instruction.SetColor(255, 0, 0);
    instruction.SetPos(Game::GetInstance().GetWindowWidth()/2,
                 Game::GetInstance().GetWindowHeight()*1/20, true, true);

    inicio.Initialize(CHARACTER_STATE_TYPE_FILE, 50, Text::TEXT_BLENDED, "Jogar");
    inicio.SetColor(255, 0, 0);
    inicio.SetPos(Game::GetInstance().GetWindowWidth()*12/13,
                 Game::GetInstance().GetWindowHeight()*14/15, true, true);

    PopulaArray();
    CriaStatus();
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
        }else if(k == 4){
            offSetX = 650;
            offSetY = 450;
        }else if(k == 5){
            offSetX = 850;
            offSetY = 450;
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
    selecao.Render(50,5);
    selecionado.Render(Game::GetInstance().GetWindowWidth()/2 + 50, 70);
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
                if(selecionadoArray.size() < 6){
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
    Sprite botao("img/penguinface.png");
    Sprite botao2("img/penguinface2.png");
    Sprite botao3("img/penguinface3.png");
    Sprite botao4("img/penguinface4.png");
    Sprite botao5("img/penguinface5.png");
    Sprite botao6("img/penguinface6.png");
    Sprite botao7("img/penguinface7.png");
    Sprite botao8("img/penguinface8.png");

    StillAnimation* botaoAnim = new StillAnimation(150, 80 + 75*characterArray.size(), 0, botao, 50, false);
    characterArray.emplace_back(*botaoAnim);

    StillAnimation* botaoAnim2 = new StillAnimation(330, 80, 0, botao2, 50, false);
    characterArray.emplace_back(*botaoAnim2);

    StillAnimation* botaoAnim3 = new StillAnimation(150, 80 + 75*characterArray.size(), 0, botao3, 50, false);
    characterArray.emplace_back(*botaoAnim3);

    StillAnimation* botaoAnim4 = new StillAnimation(330, 80 + 50*characterArray.size(), 0, botao4, 50, false);
    characterArray.emplace_back(*botaoAnim4);

    StillAnimation* botaoAnim5 = new StillAnimation(150, 80 + 75*characterArray.size(), 0, botao5, 50, false);
    characterArray.emplace_back(*botaoAnim5);

    StillAnimation* botaoAnim6 = new StillAnimation(330, 80 + 60*characterArray.size(), 0, botao6, 50, false);
    characterArray.emplace_back(*botaoAnim6);

    StillAnimation* botaoAnim7 = new StillAnimation(150, 80 + 75*characterArray.size(), 0, botao7, 50, false);
    characterArray.emplace_back(*botaoAnim7);

    StillAnimation* botaoAnim8 = new StillAnimation(330, 80 + 65*characterArray.size(), 0, botao8, 50, false);
    characterArray.emplace_back(*botaoAnim8);

}

void CharacterState::CriaStatus(){

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
    case(6):
        characters.robo.push_back("Batata");
        break;
    case(7):
        characters.robo.push_back("Digglet");
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
    case(4):
        characters.robo.erase(characters.robo.begin() + 4);
        break;
    case(5):
        characters.robo.erase(characters.robo.begin() + 5);
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
    case(6):
        nome = "Batata";
        break;
    case(7):
        nome = "Digglet";
        break;
    }

    for(int i = 0; i < characters.robo.size(); i++){
        if(characters.robo[i] == nome){
            return false;
        }
    }

    return true;
}
