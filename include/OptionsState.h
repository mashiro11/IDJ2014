#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include "StageState.h"
#include "Text.h"

class OptionsState: public State{
public:
    OptionsState();
    ~OptionsState(){};
    void Update(float dt);
    void Render();

private:
    void Input();
    Sprite bg;
    Text voltar;
};

#endif // OPTIONSSTATE_H
