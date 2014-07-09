#include "Bullet.h"

const int collisionDelay = 5;

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite, bool targetsPlayer):
    sp(sprite)
{
    box.w = sp.GetWidth();
    box.h = sp.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
    rotation = angle;
    this->speed.x = cos(angle * M_PI/180)*speed;
    this->speed.y = sin(angle * M_PI/180)*speed;
    distanceLeft = maxDistance;
    this->targetsPlayer = targetsPlayer;
}
//
//Bullet::~Bullet()
//{
//    //dtor
//}

void Bullet::Update(float dt)
{
    box.x += speed.x*dt;
    box.y += speed.y*dt;
    distanceLeft -= sqrt( speed.x*dt * speed.x*dt + speed.y*dt * speed.y*dt);
    sp.Update(dt);
}

void Bullet::Render(int cameraX, int cameraY)
{
    sp.Render(box.x - cameraX, box.y - cameraY , rotation);
}

bool Bullet::IsDead()
{
    if(distanceLeft <= 0) return true;
    return false;
}

void Bullet::NotifyCollision(GameObject& other)
{
//    if( (other.Is("Alien") && targetsPlayer == false) || other.Is("Penguins")){
//        distanceLeft = 0;
//    }
}

bool Bullet::Is(string type)
{
    if(type == "Bullet") return true;
    return false;
}
