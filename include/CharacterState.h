#ifndef CHARACTERSTATE_H
#define CHARACTERSTATE_H
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "InputManager.h"
#include "StageState.h"

class CharacterState:public State{
public:
    CharacterState();
    //~CharacterState();
    void Update(float dt);
    void Render();
    void PopulaArray();

protected:

private:
    //se o robo X estiver no jogo, o stagestate vai olhar no characters e X deve ter true assimilado.
    //O stageState vai iniciar o jogo somente com aqueles escolhidos.
    void Input();
    //unordered_map<string, StillAnimation> characterArray;
    std::vector<StillAnimation> characterArray;
    std::vector<StillAnimation> selecionadoArray;
    /*
     * characters[0] = Lider
     * characters[1] = Robo
     * */
    //static std::vector<string, bool> charactersInGame;
    static std::vector<bool> charactersInGame;
    Sprite bg;
    Sprite selecao;
    Sprite selecionado;
    Music music;
    Text instruction;
    Text inicio;
};

#endif // CHARACTERSTATE_H
