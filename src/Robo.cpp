#include "Robo.h"

Robo::Robo(float tileSize, float x, float y, float defesa, float ataque, float vidaMaxima, int coolDown,
           int range, int distance, int speed)
{
    //ver a proporзгo do personagem em relaзao ao tile do mundopara aplicar na posicao certa
//    sp.SetScaleX((float) 2);
//    sp.SetScaleY((float) 2);
    this->tileSize = tileSize;
    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface.png");
    vida.Open(this);
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);

    MapPositionToPixelPosition(x, y, tileSize);
    this->defesa = defesa;
    this->ataque = ataque;
    this->vidaMaxima = vidaMaxima;
    this->range = range;
    this->distance = distance;
    vidaAtual = vidaMaxima;
    this->coolDown = coolDown;
    this->rotation = 0;
    allyPosition = FRENTE;
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
            buttonArray[i].SetX(box.RectCenterX() - 52 + cos(angulo*M_PI/180)*offSet);
            buttonArray[i].SetY(box.RectCenterY() - 20 + sin(angulo*M_PI/180)*offSet);
            buttonArray[i].Render(cameraX,cameraY);
            angulo += 72;
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
    Piloto* piloto = pilotoArray.back();
    piloto->Ejetar();
    pilotoArray.pop_back();
    if(pilotoArray.size() == 0){
        allyState = INATIVO;
    }
}

void Robo::InserePiloto(Piloto *piloto)
{
    pilotoArray.push_back(piloto);
}

void Robo::Abrir_Menu()
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
