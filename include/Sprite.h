#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "Timer.h"

#include <unordered_map>

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;

class Sprite
{
    public:
        Sprite();
        Sprite(string file, int maxFrameCount = 1, int animationLines = 1, float frameTime = 1);
        //Sprite(Sprite const &other);
        ~Sprite();
        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x = 0, int y = 0, float angle = 0, bool centered = false);
        int GetWidth();
        int GetHeight();
        bool IsOpen() {return (texture == NULL)? true: false;}
        void SetScaleX (float scale);
        void SetScaleY (float scale);
        float GetScaleX ();
        float GetScaleY ();

        void Update (float dt);
        void SetFrame (int frame);
        void SetFrameCount (int frameCount);
        void SetFrameTime (float frameTime);
        int GetFrameCount();
        void SetAnimation(int line, int frameCount);
        void SetSpriteSheet(int animationLines, int maxFrameCount);

        static void Clear();
        static unordered_map<string, SDL_Texture*> assetTable;

    protected:
            /* nada */
    private:
        SDL_Texture* texture;
        SDL_Rect dimensions, clipRect;
        float scaleX;
        float scaleY;
        int maxFrameCount;//guarda o maior numero de frames por animacao da spritesheet
        int frameCount;//guarda o numero de frames da linha de animacao em uso
        int currentLine;//guarda a linha de animacao em uso
        int animationLines;//guarda o total de linhas de animacao
        int currentFrame;
        Timer timeElapsed;
        float frameTime;
};

#endif // SPRITE_H
