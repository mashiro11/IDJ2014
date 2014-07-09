#include "BarraVida.h"

BarraVida::BarraVida(GameObject* objeto, int vidaMax)
{
    #ifdef ANDRE
    vida.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/barraVida.png");
    moldura.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/barraVidaMold.png");
    #endif
    #ifdef MASHIRO
    vida.Open("images/img/barraVida.png");
    moldura.Open("images/img/barraVidaMold.png");
    #endif

    vidaMaxima = vidaAtual = vidaMax;
    this->objeto = objeto;
    box.w = vida.GetWidth();
    box.h = vida.GetHeight();
    box.SetRectCenterX(objeto->box.RectCenterX());
    box.SetRectCenterY(objeto->box.RectCenterY());
}

void BarraVida::Open(GameObject *alvo, int vidaMax)
{
    #ifdef ANDRE
    vida.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/barraVida.png");
    moldura.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/barraVidaMold.png");
    #endif
    #ifdef MASHIRO
    vida.Open("images/img/barraVida.png");
    moldura.Open("images/img/barraVidaMold.png");
    #endif;

    vidaMaxima = vidaAtual = vidaMax;
    this->objeto = alvo;
    box.w = vida.GetWidth();
    box.h = vida.GetHeight();
    box.SetRectCenterX(objeto->box.RectCenterX());
    box.SetRectCenterY(objeto->box.RectCenterY());
}

void BarraVida::Update()
{
    //Nessas buscas que a barra de vida faz, dá erro quando o personagem morre!!
    float porCento = 100*vidaAtual/vidaMaxima;
    if(porCento > 100) porCento = 100;
    vida.SetClip(0, 0, box.w*porCento/100, box.h);
}

bool BarraVida::IsDead()
{
    if(vidaAtual <= 0) return true;
    return false;
}

void BarraVida::Render(int cameraX, int cameraY)
{
    vida.Render(box.x - cameraX, box.y - cameraY + 65);
    moldura.Render(box.x - cameraX, box.y - cameraY + 65);
}


void BarraVida::SetX(float x){
    box.SetRectCenterX(x);
}

void BarraVida::SetY(float y){
    box.SetRectCenterY(y);
}

void BarraVida::SetVida(int vidaNova)
{
    if(vidaNova > vidaMaxima){
        vidaAtual = vidaMaxima;
    }else{
        vidaAtual = vidaNova;
    }
}

int BarraVida::GetVida()
{
    return vidaAtual;
}

float BarraVida::GetPorcentagemVida()
{
    return 100*vidaAtual/vidaMaxima;
}

bool BarraVida::IsFull(){
    if(vidaAtual/vidaMaxima == 1){
        return true;
    }
    return false;
}
