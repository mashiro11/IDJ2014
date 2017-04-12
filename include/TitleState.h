#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "Game.h"
#include "Sprite.h"
#include "StageState.h"
#include "InputManager.h"
#include "Text.h"
#include "OptionsState.h"
#include "CharacterState.h"
#include "Menu.h"

#define TITLE_STATE_BACKGROUND "img/screenSbuttons.png"
#define TITLE_STATE_MUSIC "images/audio/Tema_01.wav"


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
        Music mainTheme;
        Menu menu;
        enum title_options{
            TITLE_START = 0,
            TITLE_OPTIONS,
            TITLE_QUIT
        }TitleOptions;
};


#endif // TITLESTATE_H
