#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <SDL_ttf.h>

#include "Game.h"
#include "Rect.h"
#include "Timer.h"

using std::string;
using std::unordered_map;
using std::stringstream;

class Text
{
    public:
        enum TextStyle{
            TEXT_SOLID = 0,
            TEXT_SHADED,
            TEXT_BLENDED
        };
        Text();
        Text(string fontFile, int fontSize, TextStyle style,
             string text, SDL_Color color, int x = 0, int y = 0);
//        Text(string fontFile, int fontSize, TextStyle style,
//             string text, int x = 0, int y = 0);

        ~Text();
        void Render(int cameraX = 0, int cameraY = 0);
        void SetPos(int x , int y, bool centerX = false, bool centerY = false);
        void SetText(string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontSize(int fontSize);
        static void Clear();

        void Initialize(string fontFile, int fontSize, TextStyle style,
                        string text, SDL_Color color, int x = 0, int y = 0);
        void SetColor(SDL_Color* color, int r, int g, int b, int a);
        int GetPosX(){return box.x;};
        int GetPosY(){return box.y;};
        bool IsInside(float x, float y){return box.IsInside(x, y);};
        Timer cronometro;

    protected:
    private:
        void RemakeTexture();
        TTF_Font* font;
        SDL_Texture* texture;
        string fontFile;
        string text;
        TextStyle style;
        int fontSize;
        SDL_Color color;
        Rect box;
        static unordered_map<string, TTF_Font*> assetTable;
};

#endif // TEXT_H

