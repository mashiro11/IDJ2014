#include "Lider.h"

Lider* Lider::lider;

Lider::Lider(float x, float y, float defesa, float ataque, int speed, int distance, float hp, int coolDown, TileMap* mapRef)
{
    //ver a proporção do personagem em relaçao ao tile do mundopara aplicar na posicao certa
    //sp.SetScaleX((float) 3);
    //sp.SetScaleY((float) 3);
    //sp.SetClip(0,0, sp.GetWidth(), 64);
    //sp.SetFrameCount(4);
    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(FRONT, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);
    sp.Open("images/img/robot2iceaxe.png");
    mapReference = mapRef;
    box.h = sp.GetHeight();
    cout << "box.h: " << box.h << endl;
    box.w = sp.GetWidth();
    cout << "box.w: " << box.w << endl;
    MapPositionToPixelPosition(x, y);
    this->defesa = defesa;
    this->ataque = ataque;
    this->hp = hp;
    this->coolDown = coolDown;
    this->speed = speed;
    this->distance = distance;
    this->rotation = 0;
    allyState = REPOUSO;
    menuAberto = false;
}

Lider::~Lider(){
    lider = NULL;
}

void Lider::Render(int cameraX, int cameraY){
    sp.Render(box.x - cameraX, box.y - cameraY);
    if(menuAberto){
        int offSet = 100;
        int angulo = 0;
        for(int i = 0; i < buttonArray.size(); i++){
            buttonArray[i].SetX(box.RectCenterX() - 52 + cos(angulo*M_PI/180)*offSet);
            buttonArray[i].SetY(box.RectCenterY() - 20 + sin(angulo*M_PI/180)*offSet);
            buttonArray[i].Render(cameraX,cameraY);
            angulo += 90;
        }
    }else{
        Sprite* vida = VerificaVida();
        vida->SetScaleX(0.4);
        vida->SetScaleY(0.7);
        vida->Render(box.x - cameraX, box.y - cameraY + 80);
    }
}
