#include "Enemy.h"


Enemy::Enemy(float x, float y, TileMap* mapRef, string nome)
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
    charState = REPOUSO;
    this->nome = nome;

#ifdef ANDRE
    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/robotRosa.png");
#endif
#ifdef MASHIRO
    sp.Open("images/img/roboRosa.png");
#endif

    mapReference = mapRef;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    this->defesa = defesa;
    this->ataque = ataque;
    this->vida = vida;
    enemyState = MOVENDO;
    enemyPosition = FRENTE;

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
    switch(charState){
        case REPOUSO:
            cout << "Inimigo em repouso" << endl;
            break;
        case ANDANDO:
            cout << "Inimigo andando" << endl;
            break;
        case ATACANDO:
            cout << "Inimigo atacando" << endl;
            break;
        case ():
            break;
//        case ():
//            break;
//        case ():
//            break;

    }
}
