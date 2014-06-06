#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"//modificado GameBase -> Game (T4)
#include <unordered_map>

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;

class Sprite
{
    public:
        Sprite();
        Sprite(string file, int frameCount = 1, float frameTime = 1);
        //Sprite(Sprite const &other);
        ~Sprite();
        void Open(string file);
        void SetClip(float x, float y, float w, float h);
        void Render(int x, int y, float angle = 0);
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

        static void Clear();
        static unordered_map<string, SDL_Texture*> assetTable;

    protected:
            /* nada */
    private:
        SDL_Texture* texture;
        SDL_Rect dimensions, clipRect;
        float scaleX;
        float scaleY;
        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;
};

#endif // SPRITE_H
