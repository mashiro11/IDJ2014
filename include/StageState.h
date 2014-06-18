//colocar vetor dos personagens
#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Game.h"
#include "State.h"
#include "Sprite.h"
#include "BlockTileSet.h"
#include "TileMap.h"
#include "Music.h"
#include "StateData.h"
#include "EndState.h"
#include "Text.h"
#include "Lider.h"
#include "InfoMenu.h"
#include "Robo.h"
#include "Piloto.h"
#include "CharacterData.h"
#include "Enemy.h"

using std::find;

class StageState : public State
{
    public:
        StageState(CharacterData characters);
        void InicializaPersonagens(CharacterData characters, InfoMenu *infoMenu);
        ~StageState();
        void Update(float dt);
        void Render();

        void AddObject(int mouseX, int mouseY);//funcao adicionada por causa das faces

    protected:
    private:
        InfoMenu* infoMenu;
        void Input();
        Sprite bg;
        BlockTileSet tileSet;
        TileMap tileMap;
        Music backGroundMusic;
        Text chessPosition;
};

#endif // STAGESTATE_H
