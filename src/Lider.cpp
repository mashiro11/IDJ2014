#include "Lider.h"

Lider* Lider::lider;

Lider::Lider(float x, float y, float defesa, float ataque, int speed, int distance, float hp, int coolDown, TileMap* mapRef)
{
//    cout << "inicia construcao do lider" << endl;
    //ver a proporção do personagem em relaçao ao tile do mundopara aplicar na posicao certa
    //sp.SetScaleX((float) 2);
    //sp.SetScaleY((float) 2);
    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(0, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);
    sp.Open("images/img/robot2iceaxe.png");
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();

    mapReference = mapRef;
    box.SetRectCenterX( MapPositionToPixelPosition(x) );
    box.SetRectCenterY( MapPositionToPixelPosition(y) );

    this->defesa = defesa;
    this->ataque = ataque;
    this->hp = hp;
    this->coolDown = coolDown;
    this->speed = speed;
    this->distance = distance;
    this->rotation = 0;
    allyState = REPOUSO;
    menuAberto = false;
//    cout << "finaliza construcao do lider" << endl;
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
        //Sprite* vida = VerificaVida();
//        vida->SetScaleX(0.4);
//        vida->SetScaleY(0.7);
//        vida->Render(box.x - cameraX, box.y - cameraY + 80);
    }
}
