#include "Enemy.h"


Enemy::Enemy(float x, float y, TileMap* mapRef, string nome)
{
    #ifdef ANDRE
        sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/robotRosa.png");
    #endif
    #ifdef MASHIRO
        sp.Open("images/img/roboRosa.png");
    #endif

    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(0, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);
    charPosition = FRONT;

    mapReference = mapRef;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX( mapReference->MapPositionToPixelPosition(x) );
    box.SetRectCenterY( mapReference->MapPositionToPixelPosition(y) );
    this->vida = vida;
    charState = REPOUSO;
    this->nome = nome;
}

void Enemy::SetStatus(int vidaMaxima, float ataque, int range, float defesa, int speed, int coolDown)
{
    this->defesa = defesa;
    this->ataque = ataque;
    this->vida = vidaMaxima;
    this->range = range;
    this->speed = speed;
//    this->coolDown = coolDown;
}


Enemy::~Enemy()
{

}

void Enemy::Update(float dt)
{
    Input();
    IdentifyOpponent();
    sp.Update(dt);
}

void Enemy::Input()
{
    if(box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                    InputManager::GetInstance().GetMouseY() + Camera::pos.y) == true){
                    if(InputManager::GetInstance().KeyPress(SDLK_d) == true ){
                        cout << "Minha vida era: " << vida << endl;
                        cout << "Levei destroy! IsDead: " << IsDead() << endl;
                        vida = 0;
                    }
                    if(InputManager::GetInstance().KeyPress(SDLK_t) == true ){
                        vida -= 5;
                    }
                    if(InputManager::GetInstance().KeyPress(SDLK_h) == true ){
                        vida += 5;
                    }
    }
}

bool Enemy::IsDead()
{
    if(vida <= 0) return true;
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

void StateMachine()
{
//    switch(charState){
//        case REPOUSO:
//            cout << "Inimigo em repouso" << endl;
//            break;
//        case ANDANDO:
//            cout << "Inimigo andando" << endl;
//            break;
//        case ATACANDO:
//            cout << "Inimigo atacando" << endl;
//            break;
//        case ():
//            break;
//        case ():
//            break;
//        case ():
//            break;
//    }
}
