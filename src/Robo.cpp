#include "Robo.h"

Robo::Robo(float x, float y, float defesa, float ataque, int speed, int distance, float vidaMaxima,
           int coolDown, TileMap* mapRef, int range)
{
    //ver a proporзгo do personagem em relaзao ao tile do mundopara aplicar na posicao certa
//    sp.SetScaleX((float) 2);
//    sp.SetScaleY((float) 2);
    vida.Open(this);
    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(0, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);
#ifdef ANDRE
    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/robot2iceaxe.png");
#endif
#ifdef MASHIRO
    sp.Open("images/img/robot2iceaxe.png");
#endif

    mapReference = mapRef;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX( MapPositionToPixelPosition(x) );
    box.SetRectCenterY( MapPositionToPixelPosition(y) );

    this->defesa = defesa;
    this->ataque = ataque;
    this->vidaMaxima = vidaMaxima;
    this->vidaAtual = vidaMaxima;
    this->range = range;
    this->distance = distance;
    this->speed = speed;
    this->rotation = 0;
    this->coolDown = coolDown;
    this->rotation = 0;

    allyPosition = FRONT;
    allyState = REPOUSO;
    menuAberto = false;
}

Robo::~Robo(){

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
    if(type == "Robo"){
        return true;
    }
    return false;
}

void Robo::Ejetar()
{
//    Piloto* piloto = pilotoArray.back();
//    piloto->Ejetar();
//    pilotoArray.pop_back();
//    if(pilotoArray.size() == 0){
//        allyState = INATIVO;
//    }
}

//void Robo::InserePiloto(Piloto *piloto)
//{
//    pilotoArray.push_back(piloto);
//}


