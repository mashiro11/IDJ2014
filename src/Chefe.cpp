#include "../include/Chefe.h"

int  Chefe::chefeMorto = 0;

Chefe::Chefe(float x, float y, TileMap *mapRef, string nome)
{
    sp.Open("img/chefe2resp.png");
    atacando = 0;

    sp.SetSpriteSheet(1, 2);
    sp.SetAnimation(0, 2);
    sp.SetFrameTime(8.0 * 1.0/24.0);
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

Chefe::~Chefe()
{

}

void Chefe::SetStatus(int vidaMaxima, float ataque, int range, float defesa, int speed, int coolDown)
{
    this->defesa = defesa;
    this->ataque = ataque;
    this->vida = vidaMaxima;
    this->range = range;
    this->speed = speed;
    this->coolDown = coolDown;
}

void Chefe::Update(float dt)
{
    Input();
    StateMachine(dt);
    IdentifyOpponent();
    CloseEnemiesUpdate();

    sp.Update(dt);
    if(IsDead() == true){
        chefeMorto = 1;
        cout << this->nome <<": Aaaaaah voces me venceram!!!! >:X " << endl;
        mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                          mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).state = FREE;
        mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                          mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).occuper = NULL;

    }
}

void Chefe::StateMachine(float dt)
{
    switch(charState){
        case REPOUSO:
            if(closeEnemies.size() > 0){
                cout << this->nome << ": Haha! Vou esmaga-los! >=D" << endl;
                charState = ATACANDO;
            }
            break;

        case ATACANDO:
            timer.Update(dt);
            especialTime.Update(dt);
            rangedTime.Update(dt);

            if(timer.Get() > coolDown){
                sp.Open("images/img/chefe2ataque.png");
                sp.SetSpriteSheet(1, 6);
                sp.SetAnimation(0, 6);
                sp.SetFrameTime(2.5 * 1.0/24.0);
                atacando = 1;
                Atacar();
                timer.Restart();
            }

            if(atacando == 1){
                ataqueTime.Update(dt);
                if(ataqueTime.Get() > 6*(2.4 * 1.0/24.0)){
                    sp.Open("images/img/chefe2resp.png");
                    sp.SetSpriteSheet(1, 2);
                    sp.SetAnimation(0, 2);
                    sp.SetFrameTime(5.0 * 1.0/24.0);
                    atacando = 0;
                    ataqueTime.Restart();
                    Atacar();

                }
            }

            if(atacando == 2){
                ataqueTime.Update(dt);
                if(ataqueTime.Get() > 6*(2.4 * 1.0/24.0)){
                    sp.Open("images/img/chefe2resp.png");
                    sp.SetSpriteSheet(1, 2);
                    sp.SetAnimation(0, 2);
                    sp.SetFrameTime(5.0 * 1.0/24.0);
                    especialTime.Restart();
                    ataqueTime.Restart();
                    atacando = 0;
                }
                timer.Restart();
            }

            if(especialTime.Get() > coolDown*3){
                sp.Open("images/img/chefe2rodando.png");
                sp.SetSpriteSheet(1, 2);
                sp.SetAnimation(0, 2);
                sp.SetFrameTime(2.0 * 1.0/24.0);

                Especial();
                atacando = 2;
            }

            if(closeEnemies.empty() == true && atacando == 0){
                cout << this->nome << ": Eu destruo meus inimigos! >:O" << endl;
                charState = REPOUSO;
            }
            break;
    }
}

void Chefe::Input()
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

void Chefe::Especial()
{
    CloseEnemiesUpdate();
    if(closeEnemies.size() > 0){
        for(unordered_map<GameObject*, Point>::iterator aux = closeEnemies.begin(); aux != closeEnemies.end(); aux++){
            Ally* allyTarget = (Ally*) aux->first;
            int posX = mapReference->PixelPositionToMapPosition(allyTarget->box.RectCenterX());
            int posY = mapReference->PixelPositionToMapPosition(allyTarget->box.RectCenterY());
            int chefeX = mapReference->PixelPositionToMapPosition(box.RectCenterX());
            int chefeY = mapReference->PixelPositionToMapPosition(box.RectCenterY());
            int dist = sqrt((chefeY - posY)*(chefeY - posY) + (chefeX - posX)*(chefeX - posX));
            if(dist < 2){
                allyTarget->Danificar( ataque/15 );
            }
        }
    }

}

void Chefe::AtaqueRanged(){
    CloseEnemiesUpdate();
    if(closeEnemies.size() > 0){
        for(unordered_map<GameObject*, Point>::iterator aux = closeEnemies.begin(); aux != closeEnemies.end(); aux++){
            Ally* allyTarget = (Ally*) aux->first;
            int posX = mapReference->PixelPositionToMapPosition(allyTarget->box.RectCenterX());
            int posY = mapReference->PixelPositionToMapPosition(allyTarget->box.RectCenterY());
            int chefeX = mapReference->PixelPositionToMapPosition(box.RectCenterX());
            int chefeY = mapReference->PixelPositionToMapPosition(box.RectCenterY());
            int dist = sqrt((chefeY - posY)*(chefeY - posY) + (chefeX - posX)*(chefeX - posX));
            if(dist > 1){
                Sprite death("img/chefe2ranged.png", 6, 100);
                Game::GetInstance().GetCurrentState().AddObject(new StillAnimation(allyTarget->box.RectCenterX(),
                                                                                   allyTarget->box.RectCenterY(),
                                                                                   rotation, death, 600, true));
                allyTarget->Danificar( ataque/15 );
            }
        }
    }
}

void Chefe::Atacar()
{
    CloseEnemiesUpdate();
    cout << this->nome << ": SINTAM O PODER!! >=O" << endl;
    if(closeEnemies.size() > 0){
        Ally* allyTarget = (Ally*) closeEnemies.begin()->first;
        allyTarget->Danificar( ataque/10 );
        //cout << allyTarget->GetCharacterPosition() << endl;
    }
}

void Chefe::Danificar(float dano)
{
    Sprite hit("img/hit.png");
    Game::GetInstance().GetCurrentState().AddObject(new StillAnimation(box.RectCenterX() + 10,
                                                                       box.RectCenterY() - 25, rotation, hit, 0.5, true));
    this->vida -= dano - defesa/10;
}

bool Chefe::Is(string type)
{
    if(type == "Enemy"){
        return true;
    }
    return false;
}

bool Chefe::IsDead()
{
    if(vida <= 0)return true;
    return false;
}

void Chefe::NotifyCollision(GameObject &other)
{

}


