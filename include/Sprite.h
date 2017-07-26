#ifndef SPRITE_H
#define SPRITE_H

#include <iostream>
#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif

#include "Component.h"
#include "Timer.h"
#include <string>
#include <unordered_map>

using std::string;
using std::cout;
using std::endl;
using std::unordered_map;

class Sprite: public Component
{
    public:
        //Sprite();
        Sprite(GameObject& associated, string file, int x = 0, int y = 0, int maxFrameCount = 1, int animationLines = 1, float frameTime = 1);
        //Sprite(Sprite const &other);
        ~Sprite();
        bool Is(ComponentType type) const;


        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void SetScaleX (float scale);
        void SetScaleY (float scale);
        float GetScaleX ();
        float GetScaleY ();
        void SetPosition(int x, int y);

        void EarlyUpdate(float dt);
		void LateUpdate(float dt);

        void Update (float dt);
        void SetFrame (int frame);
        void SetFrameCount (int frameCount);
        void SetFrameTime (float frameTime);
        int GetFrameCount();
        void SetAnimation(int line, int frameCount);
        void SetSpriteSheet(int animationLines, int maxFrameCount);
        void SetCameraRelative(bool cameraRelative);

        static void Clear();
        static unordered_map<string, SDL_Texture*> assetTable;


    protected:
            /* nada */
    private:
        SDL_Texture* texture;
        SDL_Rect frame, clipRect;
        float scaleX;
        float scaleY;
        int maxFrameCount;//guarda o maior numero de frames por animacao da spritesheet
        int currentLine;//guarda a linha de animacao em uso
        int animationLines;//guarda o total de linhas de animacao
        int currentFrame;
        Timer frameTime;
        string path;
        float angle;
        bool cameraRelative;
        GameObject& associated;
};

#endif // SPRITE_H
