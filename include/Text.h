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
             string text, int x = 0, int y = 0);
//        Text(string fontFile, int fontSize, TextStyle style,
//             string text, int x = 0, int y = 0);

        ~Text();
        void Render(int cameraX = 0, int cameraY = 0);
        void SetPos(int x , int y, bool centerX = false, bool centerY = false);
        void SetText(string text);
        void SetColor(int r = 0, int g = 0, int b = 0, int alpha = 255);
        void SetStyle(TextStyle style);
        void SetFontSize(int fontSize);
        static void Clear();

        void Initialize(string fontFile, int fontSize, TextStyle style,
                        string text, int x = 0, int y = 0);
        void SetColor(SDL_Color* color, int r, int g, int b, int a);
        float GetPosX();
        float GetPosY();
        float GetWidth();
        float GetHeigth();
        string GetText();
        bool IsInside(float x, float y){return box.IsInside(x, y);};
        //Timer cronometro;

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

