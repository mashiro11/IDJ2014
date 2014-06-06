#include "Enemy.h"

Enemy::Enemy(float tileSize, float x, float y, float defesa, float ataque, float vida):
    sp("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/cubngun.png")
{
    this->tileSize = tileSize;
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    this->defesa = defesa;
    this->ataque = ataque;
    this->vida = vida;
    enemyState = MOVENDO;
    enemyPosition = FRENTE;

}

Enemy::~Enemy()
{

}

void Enemy::Update(float dt)
{

}

void Enemy::Render(int cameraX, int cameraY)
{
    sp.Render(cameraX, cameraY);
}

bool Enemy::IsDead()
{
    if(vida <= 0){
        return true;
    }
    return false;
}

bool Enemy::Is(string type)
{
    if(type == "Enemy"){
        return true;
    }
    return false;
}

void Enemy::NotifyCollision(GameObject &other)
{

}
