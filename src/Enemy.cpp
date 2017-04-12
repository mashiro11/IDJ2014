#include "../include/Enemy.h"


Enemy::Enemy(float x, float y, TileMap* mapRef, string nome)
{
    sp.Open("img/monster_bright.png");

    sp.SetSpriteSheet(8, 12);
    sp.SetAnimation(0, 3);
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

    //essa linha sera removida
    inputTest = true;

    //para teste
    //Camera::Follow(this);
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
    //cout << "verifiquei input" << endl;
    StateMachine(dt);
    //cout << "passei na maquina de estados" << endl;
    IdentifyOpponent();
    //cout << "oponentes identificados" << endl;
    CloseEnemiesUpdate();
    //cout << "area de alcance atualizada" << endl;
    sp.Update(dt);
    //cout << "animacao atualizada" << endl;
    if(IsDead() == true){
        //cout << this->nome <<": Fui destruido!! Noooooooo.... D: " << endl;
        mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                          mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).state = FREE;
        mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                          mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).occuper = NULL;

    }
    //cout << "fim update do inimigo" << endl;
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
            }else{
                if( timer.Get() > coolDown ){
                        charState = MOVENDO;
                        timer.Restart();
                }else timer.Update(dt);
            }
            break;
        case MOVENDO:
            if(path.empty() == true){
                Pathfinder(6, 18);
                charState = REPOUSO;
            }
            if(path.empty() == false){
                Andar();
            }
            if(closeEnemies.size() > 0 && Centered() == true){
                cout << this->nome << ": Haha! Vau te encher de porrada >=D" << endl;
                charState = ATACANDO;
            }
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

//movimenta o ally pelo mapa.
void Enemy::Andar(){
        Sound soundFX("images/audio/HIT_01.wav");
        //cout << "inicio allyPosition: " << allyPosition << endl;
        if( abs(box.RectCenterX() - mapReference->TileCenter( path.front().x ) ) < 5 &&
            abs(box.RectCenterY() - mapReference->TileCenter( path.front().y ) ) < 5){
                box.SetRectCenterX( mapReference->TileCenter( path.front().x ) );
                box.SetRectCenterY( mapReference->TileCenter( path.front().y ) );
                path.pop();
                //teste de posicionamento de som
                soundFX.Play(0);

        }else{

                Point pastPosition( currentPosition.x, currentPosition.y );
                if( mapReference->TileCenter( path.front().x ) > box.RectCenterX() ){
                    box.SetRectCenterX(box.RectCenterX() + speed);
                    charPosition = RIGHT;
                }else if( mapReference->TileCenter( path.front().x ) < box.RectCenterX() ){
                    box.SetRectCenterX(box.RectCenterX() - speed);
                    charPosition = LEFT;
                }
                if( mapReference->TileCenter( path.front().y ) > box.RectCenterY() ){
                    box.SetRectCenterY(box.RectCenterY() + speed);
                    charPosition = FRONT;
                }else if( mapReference->TileCenter( path.front().y ) < box.RectCenterY() ){
                    box.SetRectCenterY(box.RectCenterY() - speed);
                    charPosition = BACK;
                }

                currentPosition.SetPoint( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                                          mapReference->PixelPositionToMapPosition( box.RectCenterY() ));
                if(pastPosition.x != currentPosition.x ||
                   pastPosition.y != currentPosition.y){
                            mapReference->At(pastPosition.x, pastPosition.y).state = FREE;
                            mapReference->At(pastPosition.x, pastPosition.y).occuper = NULL;

                            mapReference->At(currentPosition.x, currentPosition.y).state = ENEMY;
                            mapReference->At(currentPosition.x, currentPosition.y).occuper = this;
                            //teste de posicionamento de som
                            //soundFX.Play(0);

                            #ifdef DEBUG
                            cout << "pasPosition: " << endl;
                            cout << "mapStateAt( " << pastPosition.x << ", " << pastPosition.y << "): " << mapReference->At(pastPosition.x, pastPosition.y).state << endl;
                            cout << "currentPosition: " << endl;
                            cout << "mapStateAt( " << currentPosition.x << ", " << currentPosition.y << "): " << mapReference->At(currentPosition.x, currentPosition.y).state << endl;
                            #endif // DEBUG
                            if(currentPosition.x - pastPosition.x == 1){
                                RangeAreaUpdate( 1, 0);
                            }else if(currentPosition.x - pastPosition.x == -1){
                                RangeAreaUpdate(-1, 0);
                            }
                            if(currentPosition.y - pastPosition.y == 1){
                                RangeAreaUpdate( 0,  1);
                            }else if(currentPosition.y - pastPosition.y == -1){
                                RangeAreaUpdate( 0, -1);
                            }
                }
                OrientarSprite();
        }
}


void Enemy::Atacar()
{
    cout << this->nome << ": TOMA ISSO!! >=O" << endl;
    if(closeEnemies.size() > 0){
        Ally* allyTarget = (Ally*) closeEnemies.begin()->first;
        allyTarget->Danificar( ataque );
    }
    Sound soundFX("images/audio/boom.wav");
    soundFX.Play(0);

}

void Enemy::Danificar(float dano)
{
    Sprite hit("img/hit.png");
    Game::GetInstance().GetCurrentState().AddObject(new StillAnimation(box.RectCenterX() + 10,
                                                                       box.RectCenterY() - 25, rotation, hit, 0.5, true));
    this->vida -= dano - defesa/10;
}



void Enemy::OrientarSprite()
{
    switch(charPosition){
        case FRONT:
            //cout << "Fica de frente" << endl;
            sp.SetAnimation(0, 3);
            break;
        case BACK:
            //cout << "Fica de costas" << endl;
            sp.SetAnimation(3, 3);
            break;
        case LEFT:
            //cout << "Fica pra esquerda" << endl;
            sp.SetAnimation(1, 3);
            break;
        case RIGHT:
            //cout << "Fica pra direita" << endl;
            sp.SetAnimation(2, 3);
            break;
    }
}

void Enemy::MakePath(/*int line, int row*/)
{
    //A forma de encontrar os pontos vai ser via A* (pathfinder)
    //ao contrário do if() de montagem do path,
    //o caminho será montado via loop e CHECADO a cada iteraçao,
    //só precisando ser reconstruido CASO o caminho apresente algum problema
    int line = mapReference->PixelPositionToMapPosition( InputManager::GetInstance().GetMouseX() + Camera::pos.x );
    int row =  mapReference->PixelPositionToMapPosition( InputManager::GetInstance().GetMouseY() + Camera::pos.y );

    if(path.size() < distance && //ainda pode andar E
       line < mapReference->GetHeight() && //está dentro das linhas do mapa E
       row < mapReference->GetWidth()){ //está dentro das colunas do mapa

        if(mapReference->At(line, row).state == FREE ||
           mapReference->At(line, row).state == ENEMY){
           //cout << "ponto ( " << line << ", " << row << ") adicionado" << endl;
           //cout << "mapStateAt( " << line << ", " << row << "): " << mapReference->At(line, row).state << endl;

           //se a lista de pontos estiver vazia ou
           //se o novo ponto for vizinho do ponto anterior
           Point newPoint(line, row);

           if( path.empty() == true){
               path.push( newPoint );
               //cout << "ponto ( " << newPoint.x << ", " << newPoint.y << ") adicionado" << endl;
           }else if( (newPoint.x == path.back().x && abs(newPoint.y - path.back().y) == 1) ||
                     (newPoint.y == path.back().y && abs(newPoint.x - path.back().x) == 1) ){
               //se o novo ponto for diferente do ponto anterior
               if(newPoint.x != path.back().x ||
                  newPoint.y != path.back().y){
                    //cout << "ENTREEEEEI" << endl;
                    path.push( newPoint );
                    //cout << "ponto ( " << newPoint.x << ", " << newPoint.y << ") adicionado" << endl;
                }
            }
        }
    }
}

bool Enemy::ValidPath()
{
    if(mapReference->At(path.back().x, path.back().y).state == FREE ) return true;
    else return false;
}
