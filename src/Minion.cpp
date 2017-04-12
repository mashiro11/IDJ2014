#include "../include/Minion.h"

const int translationSpeed = 70;
const int bulletSpeed = 200;
const int bulletDistance = 1000;
Minion::Minion(GameObject* minionCenter, float angleOffset) : sp("images/img/minion.png")
{
    center = minionCenter;

    float circX = cos(angleOffset * M_PI/180)*100 + center->box.RectCenterX();
    float circY = sin(angleOffset * M_PI/180)*100 + center->box.RectCenterY();

    box.SetRectCenterX(circX);
    box.SetRectCenterY(circY);

    box.w = sp.GetWidth();
    box.h = sp.GetHeight();
    rotation = angleOffset;

    scale = 1;
    scaleSign = 1;
}

//Minion::~Minion()
//{
//    //dtor
//}

void Minion::Update(float dt)
{
    //Inflate(0.8, 1);
    rotation -= dt*translationSpeed;
    if(rotation < -360) rotation += 360;
    box.SetRectCenterX(center->box.RectCenterX() + 100*cos( rotation * M_PI/180) );
    box.SetRectCenterY(center->box.RectCenterY() + 100*sin( rotation * M_PI/180) );
}

void Minion::Render(int cameraX, int cameraY)
{
    sp.Render(box.x - cameraX, box.y - cameraY, rotation);
}

bool Minion::IsDead()
{
    return false;
}

void Minion::NotifyCollision(GameObject& other)
{

}

bool Minion::Is(string type)
{
    if(type == "Minion") return true;
    return false;
}


void Minion::Shoot(float x, float y)
{
    Point atual(this->box.RectCenterX(), this->box.RectCenterY());
    Point alvo(x,y);
    double angulo = atan2(  alvo.y - atual.y, alvo.x - atual.x ) * 180/M_PI;

    //Aqui deve ser construido o sprite para a bullet usar.
    //O construtor de cópia deve estar funcionando
    Game::GetInstance().GetCurrentState().AddObject(new Bullet(box.RectCenterX() + box.w * cos(angulo * M_PI/180),
                                                    box.RectCenterY() + box.w * sin(angulo * M_PI/180),
                                                    angulo,
                                                    bulletSpeed,
                                                    bulletDistance,
                                                    Sprite("images/img/minionbullet.png", 3, (float) 1/(24/3)),
                                                    true )
                                                    );
}

int Minion::GetHitPoint()
{
    return 0;
}

void Minion::Inflate(float minInflate, float maxInflate)
{
    if(sp.GetScaleX() > maxInflate){
            scaleSign *= -1;
        }else if(sp.GetScaleX() < minInflate){
            scaleSign *= -1;
        }
        scale += scaleSign*0.001;
        sp.SetScaleX(scale);
        sp.SetScaleY(scale);
}
