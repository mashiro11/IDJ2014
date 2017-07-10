#include "../include/Sprite.h"
#include "Game.h"

//#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG


unordered_map<string, SDL_Texture*> Sprite::assetTable;
Sprite::Sprite()
{
    texture = NULL;

    dimensions.h = 0;
    dimensions.w = 0;
    dimensions.x = 0;
    dimensions.y = 0;

    clipRect.h = 0;
    clipRect.w = 0;
    clipRect.x = 0;
    clipRect.y = 0;

    scaleX = 1;
    scaleY = 1;

    frameCount = 1;
    maxFrameCount = 1;
    animationLines = 1;
    currentLine = 0;
    currentFrame = 0;
    frameTime = 1;
}

Sprite::Sprite(string file, int maxFrameCount, int animationLines, float frameTime)
{
    texture = NULL;

    dimensions.h = 0;
    dimensions.w = 0;
    dimensions.x = 0;
    dimensions.y = 0;

    clipRect.h = 0;
    clipRect.w = 0;
    clipRect.x = 0;
    clipRect.y = 0;

    scaleX = 1;
    scaleY = 1;

    this->maxFrameCount = maxFrameCount;
    this->animationLines = animationLines; //alterar depois
    this->frameTime = frameTime;
    currentFrame = 0;
    frameCount = 1;
    currentLine = 0;

    Open(file);
}

//Sprite::Sprite(Sprite const &other)
//{
//    texture = other.texture;
//    dimensions.x = 0;
//    dimensions.y = 0;
//    dimensions.w = GetWidth();
//    dimensions.h = GetHeight();
//
//    //SetClip(0 ,0 ,GetWidth() ,GetHeight() );
//
//    scaleX = other.scaleX;
//    scaleY = other.scaleY;
//    frameCount = other.frameCount;
//    currentFrame = other.currentFrame;
//    timeElapsed = other.timeElapsed;
//    frameTime = other.frameTime;
//}

Sprite::~Sprite()
{
    //Clear();
}

void Sprite::Open(string file)
{
    path = file;
    if ( assetTable.find(file) != assetTable.end()){//existe uma textura com esse endereco
            texture = assetTable.find(file)->second;//usa ela pr?pria
    }else{//se n?o existe ainda
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str() );//carrega
        if(texture == NULL){
            cout << SDL_GetError() << endl;
            cout << "Erro em Sprite::Open() ao carregar textura: IMG_LoadTexture() retornou NULL" << endl;
        }
        assetTable.emplace(file, texture);//e adiciona na tabela
        #ifdef DEBUG
        cout << "Sprite: " << file << " carregado - ";
        cout << "SpriteTableSize: " << assetTable.size() << endl;
        #endif // DEBUG
    }

    int erro = SDL_QueryTexture(texture, NULL, NULL, &dimensions.w, &dimensions.h);
    if(erro){//se houve um erro
        cout << SDL_GetError() << endl;
        cout << "Erro em Sprite::Open(): SDL_QueryTexture() retornou diferente de zero" << endl;
    }
    //cout << "currentFrame: " << currentFrame << endl;
    //cout << "currentLine: " << currentLine << endl;
    SetClip( currentFrame , currentLine , dimensions.w/maxFrameCount, dimensions.h/animationLines);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, float angle, bool centered)
{
    SDL_Rect dimCopy;
    dimCopy.x = x ;//+ clipRect.w * scaleX;
    dimCopy.y = y ;//+ clipRect.y * scaleY;
    dimCopy.w = clipRect.w * scaleX;
    dimCopy.h = clipRect.h * scaleY;
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dimCopy,
                     angle, NULL, SDL_FLIP_NONE);
}

void Sprite::Clear()
{
    for( unordered_map<string, SDL_Texture*>::iterator aux = assetTable.begin(); aux != assetTable.end(); aux++){
        SDL_DestroyTexture(aux->second);
    }
    assetTable.clear();
}

int Sprite::GetWidth()
{
    return scaleX * dimensions.w/maxFrameCount;
}

int Sprite::GetHeight()
{
    return scaleY * dimensions.h/animationLines;
}

void Sprite::SetScaleX (float scale)
{
    scaleX = scale;
}

void Sprite::SetScaleY (float scale)
{
    scaleY = scale;
}

float Sprite::GetScaleX()
{
    return scaleX;
}

float Sprite::GetScaleY()
{
    return scaleY;
}

void Sprite::Update (float dt)
{
    timeElapsed.Update(dt);
    if(timeElapsed.Get() > frameTime){
        ++currentFrame;
        timeElapsed.Restart();
    }
    if(currentFrame >= frameCount) currentFrame = 0;
    SetClip(currentFrame * dimensions.w/maxFrameCount,
            currentLine * dimensions.h/animationLines,
            dimensions.w/maxFrameCount,
            dimensions.h/animationLines);
}

void Sprite::SetFrame (int frame)
{
    currentFrame = frame;
    SetClip(frame * GetWidth(), clipRect.y, clipRect.w, clipRect.h);
}

void Sprite::SetFrameCount (int frameCount)
{
    this->frameCount = frameCount;
    //SetClip(clipRect.x, clipRect.y, GetWidth()/frameCount, clipRect.h);
}

void Sprite::SetFrameTime (float frameTime)
{
    this->frameTime = frameTime;
}

int Sprite::GetFrameCount()
{
    return frameCount;
}

void Sprite::SetAnimation(int line, int frameCount)
{
    currentLine = line;
    this->frameCount = frameCount;
    SetClip(0, currentLine * dimensions.h/animationLines, clipRect.w, clipRect.h);
}

void Sprite::SetSpriteSheet(int animationLines, int maxFrameCount)
{
    this->animationLines = animationLines;
    this->maxFrameCount = maxFrameCount;

    this->clipRect.w = dimensions.w/maxFrameCount;
    this->clipRect.h = dimensions.h/animationLines;
}
