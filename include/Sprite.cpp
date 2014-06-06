#include "Sprite.h"

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
    frameTime = 1;
}

Sprite::Sprite(string file, int frameCount, float frameTime)
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

    this->frameCount = frameCount;
    this->frameTime = frameTime;

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
    if ( assetTable.find(file) != assetTable.end()){//existe uma textura com esse endereco
            texture = assetTable.find(file)->second;//usa ela própria
    }else{//se não existe ainda
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
    /*quais parametros?*/
    SetClip( dimensions.x , dimensions.y , dimensions.w/frameCount, dimensions.h);
}

void Sprite::SetClip(float x, float y, float w, float h)
{
    /* Seta clipRect com os parâmetros dados. */
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y, float angle)
{
    SDL_Rect dimCopy;
    dimCopy.x = x;
    dimCopy.y = y;
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
    return scaleX * dimensions.w;
}

int Sprite::GetHeight()
{
    return scaleY * dimensions.h;
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
    timeElapsed += dt;
    if(timeElapsed > frameTime){
        ++currentFrame;
        timeElapsed = 0;
    }
    if(currentFrame >= frameCount) currentFrame = 0;
    SetClip(currentFrame * GetWidth()/frameCount, 0, GetWidth()/frameCount, GetHeight());
}

void Sprite::SetFrame (int frame)
{
    currentFrame = frame;
    SetClip(clipRect.x + frame*GetWidth(), clipRect.y, clipRect.w, clipRect.h);
}

void Sprite::SetFrameCount (int frameCount)
{
    this->frameCount = frameCount;
    SetClip(clipRect.x, clipRect.y, GetWidth()/frameCount, clipRect.h);

}

void Sprite::SetFrameTime (float frameTime)
{
    this->frameTime = frameTime;
}

int Sprite::GetFrameCount()
{
    return frameCount;
}
