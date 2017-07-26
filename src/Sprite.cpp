#include "../include/Sprite.h"
#include "Game.h"

//#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG


unordered_map<string, SDL_Texture*> Sprite::assetTable;
Sprite::Sprite(GameObject& associated, string file, int x, int y, int maxFrameCount, int animationLines, float frameTime):
    associated(associated)
{
    texture = NULL;

    frame.h = 0;
    frame.w = 0;
    frame.x = x;
    frame.y = y;

    clipRect.h = 0;
    clipRect.w = 0;
    clipRect.x = 0;
    clipRect.y = 0;

    scaleX = 1;
    scaleY = 1;
    angle = 0;

    this->maxFrameCount = maxFrameCount;
    this->animationLines = animationLines;
    this->frameTime.Set(frameTime);
    currentFrame = 0;
    currentLine = 0;
    cameraRelative = true;

    Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(string file)
{
    path = file;
    if ( assetTable.find(file) != assetTable.end()){//existe uma textura com esse endereco
            texture = assetTable.find(file)->second;//usa ela pr?pria
    }else{
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str() );
        if(texture == NULL){
            cout << SDL_GetError() << endl;
            cout << "Erro em Sprite::Open() ao carregar textura: IMG_LoadTexture() retornou NULL" << endl;
        }
        assetTable.emplace(file, texture);//e adiciona na tabela
    }

    int erro = SDL_QueryTexture(texture, NULL, NULL, &frame.w, &frame.h);
    if(erro){//se houve um erro
        cout << SDL_GetError() << endl;
        cout << "Erro em Sprite::Open(): SDL_QueryTexture() retornou diferente de zero" << endl;
    }
    //cout << "currentFrame: " << currentFrame << endl;
    //cout << "currentLine: " << currentLine << endl;
    SetClip( currentFrame , currentLine , frame.w/maxFrameCount, frame.h/animationLines);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render()
{
    DEBUG_PRINT("file: " << path);
    SDL_Rect frameOnScreen;

    frameOnScreen.w = clipRect.w * scaleX;
    frameOnScreen.h = clipRect.h * scaleY;

    if(cameraRelative == true){
        frameOnScreen.x = frame.x - Camera::pos.x;
        frameOnScreen.y = frame.y - Camera::pos.y;
    }else{
        frameOnScreen.x = frame.x;
        frameOnScreen.y = frame.y;
    }
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &frameOnScreen, angle, NULL, SDL_FLIP_NONE);

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
    return scaleX * frame.w/maxFrameCount;
}

int Sprite::GetHeight()
{
    return scaleY * frame.h/animationLines;
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
    //DEBUG_PRINT("Sprite::Update()-inicio");
    frame.x = associated.box.x;
    frame.y = associated.box.y;
    frameTime.Update(dt);
    if(frameTime.TimeUp()){
        ++currentFrame;
        frameTime.Restart();
    }
    if(currentFrame >= maxFrameCount) currentFrame = 0;
    SetClip(currentFrame * frame.w/maxFrameCount,
            currentLine * frame.h/animationLines,
            frame.w/maxFrameCount,
            frame.h/animationLines);
    //DEBUG_PRINT("Sprite::Update()-fim");
}

void Sprite::SetFrame (int frame)
{
    currentFrame = frame;
    SetClip(frame * GetWidth(), clipRect.y, clipRect.w, clipRect.h);
}

void Sprite::SetFrameCount (int frameCount)
{
    this->maxFrameCount = frameCount;
}

void Sprite::SetFrameTime (float frameTime)
{
    this->frameTime.Set(frameTime);
}

int Sprite::GetFrameCount()
{
    return maxFrameCount;
}

void Sprite::SetAnimation(int line, int frameCount)
{
    currentLine = line;
    this->maxFrameCount = frameCount;
}

void Sprite::SetSpriteSheet(int animationLines, int maxFrameCount)
{
    this->animationLines = animationLines;
    this->maxFrameCount = maxFrameCount;

    this->clipRect.w = frame.w/maxFrameCount;
    this->clipRect.h = frame.h/animationLines;
}

void Sprite::SetPosition(int x, int y){
    frame.x = x;
    frame.y = y;
}


void Sprite::SetCameraRelative(bool cameraRelative){
    this->cameraRelative = cameraRelative;
}

bool Sprite::IsOpen(){
    return (texture != NULL);
}

void Sprite::EarlyUpdate(float dt){};

void Sprite::LateUpdate(float dt){};

bool Sprite::Is(ComponentType type)const{
    return (type == SPRITE);
}

