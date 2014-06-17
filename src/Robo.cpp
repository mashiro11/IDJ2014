#include "Robo.h"

Robo::Robo(float x, float y, TileMap* mapRef, bool lider, Sprite sprite, string nome)
{
    //ver a proporзгo do personagem em relaзao ao tile do mundopara aplicar na posicao certa
//    sp.SetScaleX((float) 2);
//    sp.SetScaleY((float) 2);
    sp = sprite;
    vida.Open(this);
    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(0, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);

    this->lider = lider;
    this->nome = nome;

    mapReference = mapRef;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX( mapReference->MapPositionToPixelPosition(x) );
    box.SetRectCenterY( mapReference->MapPositionToPixelPosition(y) );
    currentPosition.SetPoint( x, y );

    this->rotation = 0;

    allyPosition = FRONT;
    charState = REPOUSO;
    menuAberto = false;
    //cout << "(" << x << ", " << y << ")" << endl;
    mapReference->At(x, y).state = ALLY;
    mapReference->At(x, y).occuper = this;
}

Robo::~Robo()
{
     mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                      mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).state = FREE;
}

void Robo::Update(float dt)
{

    UpdateAlly(dt);
    vida.Update();
    vida.SetX(box.RectCenterX());
    vida.SetY(box.RectCenterY());
}

void Robo::Render(int cameraX, int cameraY){
    sp.Render(box.x - cameraX, box.y - cameraY);
    if(menuAberto){
        int offSet = 100;
        int angulo = 90;
        for(int i = 0; i < buttonArray.size(); i++){
            buttonArray[i].SetX(box.RectCenterX() + cos(angulo*M_PI/180)*offSet);
            buttonArray[i].SetY(box.RectCenterY() - 20 + sin(angulo*M_PI/180)*offSet);
            buttonArray[i].Render(cameraX,cameraY);
            angulo += 90;
        }
    }else{
        vida.Render(cameraX, cameraY);
    }
}

bool Robo::Is(string type){
    if(type == "Robo" || type == "Ally"){
        return true;
    }
    return false;
}

void Robo::Ejetar()
{
    Piloto* piloto = pilotoArray.back();
    piloto->Ejetar();
    pilotoArray.pop_back();
    if(pilotoArray.size() == 0){
        charState = INATIVO;
    }
}

void Robo::InserePiloto(Piloto *piloto)
{
    pilotoArray.push_back(piloto);
}


