#include "Alien.h"

const int translationSpeed = 60;
const int alienSpeed = 150;
const int coolDownTime = 5;
const int shootInterval = 2;
//const int shootTime = shootInterval + 0.5;
const int shootsPerWalk = 8;
const int damageTaken = 100;
const int AlienHP = 100;

int Alien::alienCount;
Alien::Alien(float x, float y, int nMinions) : sp("images/img/alien.png")
{
    ++alienCount;
    shootCounter = 0;
    alienState = RESTING;
    box.w = sp.GetWidth();
    box.h = sp.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
    rotation = 0;

    speed.x = 0;
    speed.y = 0;
    hp = AlienHP;
    for(int i = 0; i < nMinions; i++){
            minionArray.emplace_back(Minion( this,  i*360/nMinions));
    }


    /*
    Inicializando atributos adicionados
    */
    scale = 1;
    scaleSign = -1;
}

Alien::~Alien()
{
    --alienCount;
    //dtor
}

void Alien::Update(float dt)
{
    switch(alienState){
        case RESTING:
            shootCooldown.Update(dt);
            if(shootCooldown.Get() > coolDownTime){
                alienState = MOVING;
                shootCooldown.Restart();
            }
            break;
        case MOVING:
            shootCooldown.Update(dt);

            Point playerPosition;
            //pega a posicao do player
            if(Penguins::player != NULL){
                    playerPosition.SetPoint(Penguins::player->box.RectCenterX(),
                                            Penguins::player->box.RectCenterY());
            }else{
                playerPosition.SetPoint((float)512, (float)300);
                //Camera::Follow(this);
            }
            //coloca posicao do player na fila de caminhada
            taskQueue.emplace(playerPosition);

            //se a fila nao estiver vazia
            if(taskQueue.empty() != true ){
                    //pega a posicao atual do alien
                    Point atual(box.RectCenterX(), box.RectCenterY());

                    //e mede distancia ao ponto da fila
                    float distancia = taskQueue.front().distancia(atual);

                    //se for nao desprezivel
                    if(distancia > 3){
                            //anda
                            speed.x = abs( (atual.x - taskQueue.front().x) ) / distancia;//arrumar a speed para ser constante
                            speed.y = abs( (atual.y - taskQueue.front().y) ) / distancia;
                            speed.x *= Game::GetInstance().GetDeltaTime()*alienSpeed;
                            speed.y *= Game::GetInstance().GetDeltaTime()*alienSpeed;
                            if(taskQueue.front().x > box.RectCenterX()){
                                box.x += speed.x;
                            }
                            else{
                                box.x -= speed.x;
                            }
                            if(taskQueue.front().y > box.RectCenterY()){
                                box.y += speed.y;
                            }
                            else{
                                box.y -= speed.y;
                            }
                    }else{
                            taskQueue.pop();
                    }
            }
            //se deu o tempo de intervalo de tiros
            shootTimer.Update(dt);
            if( shootTimer.Get() > shootInterval){
                    //procura o minion mais proximo
                    int maisProximo = 0, menor = INFINITY;
                    for(int i = 0; i < minionArray.size(); i++){
                            //cout << "Distancia: " << minionArray[i].box.distancia(playerPosition) << "                      " << endl;
                            if(menor > minionArray[i].box.distancia(playerPosition)){
                                    menor = minionArray[i].box.distancia(playerPosition);
                                    maisProximo = i;
                            }
                    }
                    //atira
                    minionArray[maisProximo].Shoot(playerPosition.x, playerPosition.y);
                    shootTimer.Restart();
            }
            if(shootCooldown.Get() >= coolDownTime*3){
                while(taskQueue.size() != 0 ) taskQueue.pop();
                shootCounter = 0;
                shootCooldown.Restart();
                alienState = RESTING;
            }
            break;
    }
    //Inflate(1, 1.2);
    rotation += dt*translationSpeed;
    if(rotation > 360) rotation -= 360;
    for(int i = 0; i < minionArray.size(); i++){
        minionArray[i].Update( Game::GetInstance().GetDeltaTime() );
    }
}

void Alien::Render(int cameraX, int cameraY)
{
    sp.Render(box.x - cameraX, box.y - cameraY, rotation);
    for(int i = 0; i - minionArray.size(); i++){
          minionArray[i].Render(cameraX, cameraY);
    }
}

bool Alien::IsDead()
{
    if(hp <= 0) return true;
    else return false;
}

void Alien::NotifyCollision(GameObject& other)
{
    if(other.Is("Bullet")){
            if( ( (Bullet&) other).targetsPlayer == false){
                    cout << "Alien levou tiro" << endl;
                    hp -= damageTaken;
            }
    }
    if(IsDead() == true){
            Sprite sp("images/img/aliendeath.png", 4, (float) 1 / (25/4) );
            Game::GetInstance().GetCurrentState().AddObject(new StillAnimation(box.RectCenterX(),
                                                                 box.RectCenterY(),
                                                                 rotation,
                                                                 sp,
                                                                 (float) 4 * 1 / (25/4),
                                                                 true) );
            Sound soundFX("images/audio/boom.wav");
            soundFX.Play(0);
    }
}

bool Alien::Is(string type)
{
    if(type == "Alien") return true;
    return false;
}

int Alien::GetHitPoint()
{
    return hp;
}

void Alien::Inflate(float minInflate, float maxInflate)
{
    if(sp.GetScaleX() < minInflate){
        scaleSign *= -1;
    }else if(sp.GetScaleX() > maxInflate){
        scaleSign *= -1;
    }
    scale += scaleSign*0.001;
    sp.SetScaleX(scale);
    sp.SetScaleY(scale);
}
