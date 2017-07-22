//colocar vetor dos personagens
#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "Robo.h"
#include "resources_path.h"
#define STAGE_TILE_W_H               64

using std::find;

class StageState : public State
{
    public:
        //StageState(CharacterData characters);
        StageState();
        //void InicializaPersonagens(CharacterData characters, InfoMenu *infoMenu);
        ~StageState();
        void Update(float dt);
        void Render();

    protected:
    private:
        void Input(float dt);
        Sprite bg;
        Music backGroundMusic;
        Timer vitoriaTime;
};

#endif // STAGESTATE_H
