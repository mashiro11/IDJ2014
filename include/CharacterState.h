#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H

#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "InputManager.h"
#include "StageState.h"
#include "CharacterData.h"
#include "Robo.h"
#include "Piloto.h"
//#include "BarraStatus.h"
#include "resources_path.h"

class CharacterState:public State{
public:
    CharacterState();
    //~CharacterState();
    void Update(float dt);
    void Render();
    void PopulaArray();
    void InserePersonagem(int index);
    void DeletaPersonagem(int index);
    bool NaoDentro(int index);
    void CriaStatus();

protected:

private:
    //se o robo X estiver no jogo, o stagestate vai olhar no characters e X deve ter true assimilado.
    //O stageState vai iniciar o jogo somente com aqueles escolhidos.
    void Input();
    //unordered_map<string, StillAnimation> characterArray;
    std::vector<StillAnimation> characterArray;
    std::vector<StillAnimation> selecionadoArray;
//    std::vector<BarraStatus> statusArray;
    Sprite bg;
    Sprite selecao;
    Sprite selecionado;
    Music music;
    Text instruction;
    Text inicio;
    CharacterData characters;

};

#endif // CHARACTERSTATE_H
