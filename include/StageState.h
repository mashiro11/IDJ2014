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
#include "Chefe.h"

#define STAGE_BACKGROUND_FILE        "img/ocean.jpg"
#define STAGE_TILESET_FILE           "img/tileSet.jpg"
#define STAGE_TILE_W_H               64
#define STAGE_TILEMAP_FILE           "images/map/tileMap20x20.txt"
#define STAGE_BACKGROUND_MUSIC_FILE  "images/audio/Tema_Boss_01.wav"
#define STAGE_FONT_FILE              "images/font/Call me maybe.ttf"

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
        void Input(float dt);
        Sprite bg;
        BlockTileSet tileSet;
        TileMap tileMap;
        Music backGroundMusic;
        Text chessPosition;
        int tileNumber;
        Timer vitoriaTime;
        bool showDebug;
};

#endif // STAGESTATE_H
