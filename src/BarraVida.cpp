#include "BarraVida.h"

BarraVida::BarraVida(GameObject* objeto):
    vida("images/img/barraVida.png"),
    moldura("images/img/barraVidaMold.png")
{
    this->objeto = objeto;
    box.w = vida.GetWidth();
    box.h = vida.GetHeight();
    box.SetRectCenterX(objeto->box.RectCenterX());
    box.SetRectCenterY(objeto->box.RectCenterY());


}

void BarraVida::Open(GameObject *alvo)
{
    vida.Open("images/img/barraVida.png");
    moldura.Open("images/img/barraVidaMold.png");
    this->objeto = alvo;

    box.w = vida.GetWidth();
    box.h = vida.GetHeight();
    box.SetRectCenterX(objeto->box.RectCenterX());
    box.SetRectCenterY(objeto->box.RectCenterY());
}

void BarraVida::Update()
{
    int max = objeto->GetLife();
    int atual = objeto->GetHitPoint();
    float porCento = 100*atual/max - 50;

    if(porCento == 100){

    }else if(porCento >= 95){
        vida.SetClip(0, 0, box.w*0.95, box.h);
    }else if(porCento >= 90){
        vida.SetClip(0, 0, box.w*0.9, box.h);
    }else if(porCento >= 85){
        vida.SetClip(0, 0, box.w*0.85, box.h);
    }else if(porCento >= 80){
        vida.SetClip(0, 0, box.w*0.8, box.h);
    }else if(porCento >= 75){
        vida.SetClip(0, 0, box.w*0.75, box.h);
    }else if(porCento >= 70){
        vida.SetClip(0, 0, box.w*0.7, box.h);
    }else if(porCento >= 65){
        vida.SetClip(0, 0, box.w*0.65, box.h);
    }else if(porCento >= 60){
        vida.SetClip(0, 0, box.w*0.6, box.h);
    }else if(porCento >= 55){
        vida.SetClip(0, 0, box.w*0.55, box.h);
    }else if(porCento >= 50){
        vida.SetClip(0, 0, box.w*0.5, box.h);
    }else if(porCento >= 45){
        vida.SetClip(0, 0, box.w*0.45, box.h);
    }else if(porCento >= 40){
        vida.SetClip(0, 0, box.w*0.4, box.h);
    }else if(porCento >= 35){
        vida.SetClip(0, 0, box.w*035., box.h);
    }else if(porCento >= 30){
        vida.SetClip(0, 0, box.w*0.3, box.h);
    }else if(porCento >= 25){
        vida.SetClip(0, 0, box.w*0.25, box.h);
    }else if(porCento >= 20){
        vida.SetClip(0, 0, box.w*0.2, box.h);
    }else if(porCento >= 15){
        vida.SetClip(0, 0, box.w*0.15, box.h);
    }else if(porCento >= 10){
        vida.SetClip(0, 0, box.w*0.1, box.h);
    }else if(porCento >= 5){
        vida.SetClip(0, 0, box.w*0.5, box.h);
    }else if(porCento <= 0){
        vida.SetClip(0, 0, box.w*0.0, box.h);
    }
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
