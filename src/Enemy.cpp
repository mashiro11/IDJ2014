#include "Enemy.h"

Enemy::Enemy(float x, float y, TileMap* mapRef)
{
    //ver a proporção do personagem em relaçao ao tile do mundopara aplicar na posicao certa
    //sp.SetScaleX((float) 2);
    //sp.SetScaleY((float) 2);

    //SetFrameCount
    //SetFrameTime

    //vida.Open(this);
    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(0, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);
    charPosition = FRONT;

#ifdef ANDRE
    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/robotRosa.png");
#endif
#ifdef MASHIRO
    sp.Open("images/img/roboRosa.png");
#endif

    mapReference = mapRef;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX( mapReference->MapPositionToPixelPosition(x) );
    box.SetRectCenterY( mapReference->MapPositionToPixelPosition(y) );

    mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                      mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).state = ENEMY;
    //enemyState = AGUARDANDO;
    vida = 5;
}

Enemy::~Enemy()
{

}

void Enemy::Update(float dt)
{
    sp.Update(dt);
}

//void Enemy::Render(int cameraX, int cameraY)
//{
//    sp.Render(box.x - cameraX, box.y - cameraY);
//}

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
