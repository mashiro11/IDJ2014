#ifndef TITLESTATE_H
#define TITLESTATE_H


#include "State.h"
#include "Game.h"
#include "Sprite.h"
#include "StageState.h"
#include "InputManager.h"
#include "Text.h"
#include "OptionsState.h"


class TitleState : public State
{
    public:
        TitleState();
        //~TitleState();
        void Update(float dt);
        void Render();

    protected:
    private:
        void Input();
        Sprite bg;
        Text start;
        Text options;
        Text quit;
};


#endif // TITLESTATE_H
