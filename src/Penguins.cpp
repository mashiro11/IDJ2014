#include "Penguins.h"


const int maxMoveSpeed = 300;
const int acceleration = 5;
const int curveSpeed = 5;
const int playerHP = 100;
const int bulletSpeed = 400;
const int bulletDistance = 1000;
const int damageTaken = 10;

Penguins* Penguins::player;
Penguins::Penguins(float x, float y):
    bodySp("images/img/penguindad.png", 1, 1),
    cannonSp("images/img/cubngun.png", 1, 1)
{
    player = this;

    box.w = bodySp.GetWidth();
    box.h = bodySp.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
    cout << "Box: " << box.x << "x" << box.y << endl;
    cout << "BoxCenter: " << box.RectCenterX() << "x" << box.RectCenterY() << endl;
    rotation = 0;
    cannonAngle = 0;

    linearSpeed = 0;
    speed.x = 0;
    speed.y = 0;
    hp = playerHP;
}

Penguins::~Penguins()
{
//    GameBase::GetInstance().AddObject(new StillAnimation(box.RectCenterX(),
//                                                         box.RectCenterY(),
//                                                         rotation,
//                                                         Sprite("images/img/penguindeath.png", 5, (float)1 / (24/5) ),
//                                                         (float)5 * 1 / (24/5),
//                                                         true) );
    player = NULL;
}

void Penguins::Update (float dt)
{
    if(InputManager::GetInstance().IsKeyDown(SDLK_w) == true){
        if(linearSpeed < maxMoveSpeed)
        linearSpeed += acceleration;
    }else if(linearSpeed > 0){
        linearSpeed -= acceleration;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_s) == true){
        if(linearSpeed > 0)
        linearSpeed -= acceleration;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_d) == true){
        if(rotation > 360) rotation -= 360;
        rotation += curveSpeed;
    }
    if(InputManager::GetInstance().IsKeyDown(SDLK_a) == true){
        if(rotation < -360) rotation += 360;
        rotation -= curveSpeed;
    }
    if(InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT) == true){
        Shoot();
    }


    speed.x = cos(rotation * M_PI/180) * linearSpeed * dt;
    speed.y = sin(rotation * M_PI/180) * linearSpeed * dt;
    box.x += speed.x;
    box.y += speed.y;
}

void Penguins::Render (int cameraX, int cameraY)
{
    bodySp.Render(box.x - cameraX, box.y - cameraY, rotation);

    Point atual(box.RectCenterX(), box.RectCenterY());
    Point mouse(InputManager::GetInstance().GetMouseX(),
                InputManager::GetInstance().GetMouseY());

    cannonAngle = atan2( mouse.y - atual.y + cameraY, mouse.x - atual.x + cameraX) * 180/M_PI;
    cannonSp.Render(box.x - cameraX,
                    box.y +( bodySp.GetHeight() - cannonSp.GetHeight() )/2 - cameraY,
                    cannonAngle);
}

bool Penguins::IsDead ()
{
    if(hp <= 0 ) return true;
    return false;
}

void Penguins::NotifyCollision(GameObject& other)
{
    if(other.Is("Bullet")){
        hp -= damageTaken;
    }
    if(IsDead() == true){
            Sprite sp("images/img/penguindeath.png", 5, (float) 1 / (25/5) );
            Game::GetInstance().GetCurrentState().AddObject(new StillAnimation(box.RectCenterX(),
                                                                 box.RectCenterY(),
                                                                 rotation,
                                                                 sp,
                                                                 (float) 5 * 1 / (25/5),
                                                                 true) );
            Sound soundFX("images/audio/boom.wav");
            soundFX.Play(0);
    }
}

bool Penguins::Is(string type)
{
    if(type == "Penguins") return true;
    return false;
}


void Penguins::Shoot ()
{
    //Aqui deve ser construido o sprite para a bullet usar.
    //O construtor de cópia deve estar funcionando
    Game::GetInstance().GetCurrentState().AddObject(new Bullet(box.RectCenterX() + box.w * cos(cannonAngle * M_PI/180),
                                                 box.RectCenterY() + box.w * sin(cannonAngle * M_PI/180),
                                                 cannonAngle,
                                                 bulletSpeed,
                                                 bulletDistance,
                                                 Sprite("images/img/penguinshot.png", 4, (float) 1/(24/4)),
                                                 false )
                                      );
}

int Penguins::GetHitPoint()
{
    return hp;
}
