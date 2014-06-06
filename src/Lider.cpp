#include "Lider.h"

Lider* Lider::lider;

Lider::Lider(float x, float y, float defesa, float ataque, int speed, int distance, float hp,
             int coolDown, TileMap* mapRef, int range)
{
    //ver a proporção do personagem em relaçao ao tile do mundopara aplicar na posicao certa
//    sp.SetScaleX((float) 2);
//    sp.SetScaleY((float) 2);

    //SetFrameCount
    //SetFrameTime
    cout << "AKI " << endl;
    vida.Open(this);    
    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(0, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);
    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/robot2iceaxe.png");

    mapReference = mapRef;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX( MapPositionToPixelPosition(x) );
    box.SetRectCenterY( MapPositionToPixelPosition(y) );
 cout << "AKI " << endl;
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

Lider::~Lider(){
    lider = NULL;
}

void Lider::Update(float dt)
{
    UpdateAlly(dt);
    vida.Update();
    vida.SetX(box.RectCenterX());
    vida.SetY(box.RectCenterY());
}

void Lider::Render(int cameraX, int cameraY){
    sp.Render(box.x - cameraX, box.y - cameraY);
    if(menuAberto){
        int offSet = 100;
        int angulo = 90;
        for(int i = 0; i < buttonArray.size(); i++){
            buttonArray[i].SetX(box.RectCenterX() - 52 + cos(angulo*M_PI/180)*offSet);
            buttonArray[i].SetY(box.RectCenterY() - 20 + sin(angulo*M_PI/180)*offSet);
            buttonArray[i].Render(cameraX,cameraY);
            angulo += 72;
        }
    }else{
        vida.Render(cameraX, cameraY);
    }
}

bool Lider::Is(string type){
    if(type == "Lider"){
        return true;
    }
    return false;
}

void Lider::Ejetar()
{
    /*
    cout << "AQUI" << endl;
    cout << "AQUI" << endl;
    cout << "AQUI" << endl;
    cout << "AQUI" << endl;
    cout << "AQUI" << endl;
    cout << "AQUI" << endl;
    cout << "AQUI" << endl;
    pilotoArray.pop_back();
    if(pilotoArray.size() == 0){
        allyState = INATIVO;
    }*/
}

void Lider::Abrir_Menu()
{
    float offSet = 125;
    float angulo = 90;
    float angOffset = 72;

    Sprite botao("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoMover.png");
    StillAnimation* botaoAnim = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);
    angulo += angOffset;

    Sprite botao2("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botao.png");
    StillAnimation* botaoAnim2 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao2, 50, false);
    buttonArray.emplace_back(*botaoAnim2);
    angulo += angOffset;

    Sprite botao3("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoItens.png");
    StillAnimation* botaoAnim3 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao3, 50, false);
    buttonArray.emplace_back(*botaoAnim3);
    angulo += angOffset;

    Sprite botao4("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoEspecial.png");
    StillAnimation* botaoAnim4 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao4, 50, false);
    buttonArray.emplace_back(*botaoAnim4);
    angulo += angOffset;

    Sprite botao5("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoDefender.png");
    StillAnimation* botaoAnim5 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao5, 50, false);
    buttonArray.emplace_back(*botaoAnim5);
}
