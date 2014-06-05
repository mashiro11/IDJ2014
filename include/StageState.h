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

class StageState : public State
{
    public:
        StageState();
        ~StageState();
        void Update(float dt);
        void Render();

        void AddObject(int mouseX, int mouseY);//funcao adicionada por causa das faces

    protected:
    private:
        void Input();
        Sprite bg;
        BlockTileSet tileSet;
        TileMap tileMap;
        Music backGroundMusic;
        Text chessPosition;
        //Ally personagem;
};

#endif // STAGESTATE_H
