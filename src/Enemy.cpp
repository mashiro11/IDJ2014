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
    mapReference->At(x, y).state = ENEMY;
    mapReference->At(x, y).occuper = this;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX( mapReference->MapPositionToPixelPosition(x) );
    box.SetRectCenterY( mapReference->MapPositionToPixelPosition(y) );
    currentPosition.SetPoint(x, y);
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
    this->coolDown = coolDown;
}


Enemy::~Enemy()
{
}

void Enemy::Update(float dt)
{
    Input();
    StateMachine(dt);
    IdentifyOpponent();
    CloseEnemiesUpdate();
    sp.Update(dt);
    if(IsDead() == true){
        cout << this->nome <<": Fui destruido!! Noooooooo.... D: " << endl;
        mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                          mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).state = FREE;
        mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                          mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).occuper = NULL;

    }
}

void Enemy::Input()
{
    if(box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                    InputManager::GetInstance().GetMouseY() + Camera::pos.y) == true){
                    if(InputManager::GetInstance().KeyPress(SDLK_d) == true ){
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
    if(vida <= 0)return true;
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

void Enemy::StateMachine(float dt)
{
    switch(charState){
        case REPOUSO:
            if(closeEnemies.size() > 0){
                cout << this->nome << ": Haha! Vau te encher de porrada >=D" << endl;
                charState = ATACANDO;
            }
            break;
        case MOVENDO:
            cout << "*" <<this->nome <<" esta andando*" << endl;
            break;
        case ATACANDO:
            timer.Update(dt);
            if(timer.Get() > coolDown){
                Atacar();
                timer.Restart();
            }
            if(closeEnemies.empty() == true){
                cout << this->nome << ": Chutamos a bunda deles! >xD" << endl;
                charState = REPOUSO;
            }
            break;
//        case ():
//            break;
//        case ():
//            break;
//        case ():
//            break;
    }
}

void Enemy::Atacar()
{
    cout << this->nome << ": TOMA ISSO!! >=O" << endl;
    if(closeEnemies.size() > 0){
        Ally* allyTarget = (Ally*) closeEnemies.begin()->first;
        allyTarget->Danificar( ataque );
    }
}

void Enemy::Danificar(float dano)
{
    this->vida -= dano - defesa/10;
}
