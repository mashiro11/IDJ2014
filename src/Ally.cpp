#include "Ally.h"

//Ally::Ally()
//{
//
//}

void Ally::SetStatus(int vidaMaxima, float ataque, int range, float defesa, int speed, int distance, int coolDown)
{
    vida.Open(this, vidaMaxima);
    this->defesa = defesa;
    this->ataque = ataque;
    this->range = range;
    this->distance = distance;
    this->speed = speed;
    this->coolDown = coolDown;
}

//gerencia as modificacoes e os estados  do ally
void Ally::UpdateAlly(float dt)
{

    StateMachine(dt);
    Input();
    IdentifyOpponent();
    CloseEnemiesUpdate();
    //if(timer.Get() < coolDown) timer.Update(dt);
    sp.Update(dt);
    if(IsDead() == true){
        cout << this->nome <<": Fui destruido!! Noooooooo.... D: " << endl;
        mapReference->At( currentPosition.x, currentPosition.y ).state = FREE;
        mapReference->At( currentPosition.x , currentPosition.y ).occuper = NULL;

    }
}

void Ally::Input()
{
    if(box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                    InputManager::GetInstance().GetMouseY() + Camera::pos.y) == true){
                    if(InputManager::GetInstance().KeyPress(SDLK_d) == true ){
                        vida.SetVida(0);
                    }
                    if(InputManager::GetInstance().KeyPress(SDLK_t) == true ){
                        int vidaNova = vida.GetVida() - 5;
                        vida.SetVida(vidaNova);

                    }
                    if(InputManager::GetInstance().KeyPress(SDLK_h) == true ){
                        int vidaNova = vida.GetVida() + 5;
                        vida.SetVida(vidaNova);
                    }
    }
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
        #ifdef ANDRE
            Sound soundFX("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/audio/boom.wav");
        #endif
        #ifdef MASHIRO
            Sound soundFX("images/audio/boom.wav");
        #endif
        soundFX.Play(0);
        //se o mouse estiver dentro do personagem, o menu é aberto e recebe true se nao existir.
        //se o menu ja existir, recebe falso, pois sera fechado mais para frente.
        if(this->box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                              InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                                            if(menuAberto == false){
                                                Camera::Follow(this);
                                                Abrir_Menu();
                                                menuAberto = true;
                                            }else{
                                                menuAberto = false;
                                            }
        //se o clique for fora do personagem, menu recebe falso para ser fechado mais a frente
        }else{
            menuAberto = false;
        }
        for(int i = 0; i < buttonArray.size(); i++){
            //verifica qual o botao que foi clicado, se algum deles for clicado.
            if(buttonArray[i].box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                           InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                switch(i){
                case(0):
                   cout << "esse botao pede para andar" << endl;
                   charState = AGUARDANDO_ANDAR;
                   break;
               case(1):
                   cout << "esse botao pede para defender" << endl;
                   charState = DEFENDENDO;
                   break;
               case(2):
                   cout << "esse botao pede para usar item" << endl;
                   charState = AGUARDANDO_ITEM;
                   break;
               case(3):
                   cout << "esse botao pede para ejetar" << endl;
                   Ejetar();
                   charState = AGUARDANDO_EMBARCAR;
                   break;
               }
            }
        }
        if (menuAberto == false){
            Fechar_Menu();
        }
    }
}


void Ally::StateMachine(float dt)
{
    switch(charState){
        case MOVENDO:
            if( path.empty() == true){
                cout << endl << "*" << this->nome << " parou*" << endl;
                charState = REPOUSO;
                break;
            }else{
                cout << "*" << this->nome << " esta andando*\r";
                Andar();
            }
            break;

        case DEFENDENDO:
            break;

        case INATIVO:
            break;

        case ATACANDO:
            timer.Update(dt);
            if(timer.Get() > coolDown){
                Atacar();
                timer.Restart();
            }
            if(closeEnemies.size() == 0){
                cout << this-> nome <<": Vencemos! \\o/" << endl;
                charState = REPOUSO;
            }
            break;

        case REPOUSO:
            if(closeEnemies.size() > 0){
                cout << this->nome << ": Inimigos proximos!! Atacaaaaar! >xO" << endl;
                charState = ATACANDO;
            }
            break;
        case AGUARDANDO_ANDAR:

            //if(InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) == true){
            //}
            MakePath();
            if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
                    if(ValidPath() == true){
                            charState = MOVENDO;
                    }else{
                            while(path.empty() == false) path.pop();
                            charState = REPOUSO;
                    }
            }
            break;
    }
}


//verifica se ally esta morto
bool Ally::IsDead(){
    int vidaAtual = vida.GetVida();
    if(vidaAtual <= 0){
        if(Camera::GetFocus() == this) Camera::Unfollow();
        return true;
    }
    return false;
}

bool Ally::Is(string type)
{
    //cout << "Is(" << type << ") == Ally?" << endl;
    if(type == "Ally") return true;
    else return false;
}

//movimenta o ally pelo mapa.
void Ally::Andar(){
        #ifdef ANDRE
            Sound soundFX("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/audio/boom.wav");
        #endif
        #ifdef MASHIRO
            Sound soundFX("images/audio/boom.wav");
        #endif
        //cout << "inicio allyPosition: " << allyPosition << endl;
        if( abs(box.RectCenterX() - mapReference->TileCenter( path.front().x ) ) < 5 &&
            abs(box.RectCenterY() - mapReference->TileCenter( path.front().y ) ) < 5){
                box.SetRectCenterX( mapReference->TileCenter( path.front().x ) );
                box.SetRectCenterY( mapReference->TileCenter( path.front().y ) );
                path.pop();
                soundFX.Play(0);
        }else{
        Point pastPosition( currentPosition.x, currentPosition.y );
        if( mapReference->TileCenter( path.front().x ) > box.RectCenterX() ){
            box.SetRectCenterX(box.RectCenterX() + speed);
            allyPosition = RIGHT;
        }else if( mapReference->TileCenter( path.front().x ) < box.RectCenterX() ){
            box.SetRectCenterX(box.RectCenterX() - speed);
            allyPosition = LEFT;
        }
        if( mapReference->TileCenter( path.front().y ) > box.RectCenterY() ){
            box.SetRectCenterY(box.RectCenterY() + speed);
            allyPosition = FRONT;
        }else if( mapReference->TileCenter( path.front().y ) < box.RectCenterY() ){
            box.SetRectCenterY(box.RectCenterY() - speed);
            allyPosition = BACK;
        }
        currentPosition.SetPoint( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                                  mapReference->PixelPositionToMapPosition( box.RectCenterY() ));
                if(pastPosition.x != currentPosition.x ||
                   pastPosition.y != currentPosition.y){
                            mapReference->At(pastPosition.x, pastPosition.y).state = FREE;
                            mapReference->At(pastPosition.x, pastPosition.y).occuper = NULL;

                            mapReference->At(currentPosition.x, currentPosition.y).state = ALLY;
                            mapReference->At(currentPosition.x, currentPosition.y).occuper = this;
                            soundFX.Play(0);

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

//para a movimentacao do ally caso este encontre um obstaculo pelo caminho.
void Ally::Parar(){

}

//reduz a vida do ally
void Ally::Danificar(float dano)
{
    int vidaNova = vida.GetVida();
    vidaNova -= dano - defesa/10;
    vida.SetVida(vidaNova);
}

//notifica as colisoes de ally
void Ally::NotifyCollision(GameObject &other)
{

}

//anima o personagem com seu ataque basico.
void Ally::Atacar()
{
    if(closeEnemies.size() > 0){
        cout << this->nome <<": Yaah! >=O" << endl;
        Enemy* enemyTarget = (Enemy*) closeEnemies.begin()->first;
        enemyTarget->Danificar( ataque );
        #ifdef ANDRE
            Sound soundFX("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/audio/boom.wav");
        #endif
        #ifdef MASHIRO
            Sound soundFX("images/audio/boom.wav");
        #endif
    }
}

//gerencia o ally em seu modo de defesa.
void Ally::Defender()
{
    charState = DEFENDENDO;
}

//abre o menu de personagem


//fecha o menu de personagem
void Ally::Fechar_Menu()
{
    buttonArray.clear();
}

//coloca um item no vetor de itens do ally
void Ally::Alocar_Item()
{

}

void Ally::Usar_Item()
{

}



//gerencia o uso de especial
void Ally::Especial()
{

}

void Ally::MakePath(/*int line, int row*/)
{
    int line = mapReference->PixelPositionToMapPosition( InputManager::GetInstance().GetMouseX() + Camera::pos.x );
    int row =  mapReference->PixelPositionToMapPosition( InputManager::GetInstance().GetMouseY() + Camera::pos.y );
    if(path.size() < distance && //ainda pode andar E
       line < mapReference->GetHeight() && //está dentro das linhas do mapa E
       row < mapReference->GetWidth()){ //está dentro das colunas do mapa

        if(mapReference->At(line, row).state == FREE ||
           mapReference->At(line, row).state == ALLY){
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


bool Ally::ValidPath()
{
    if(mapReference->At(path.back().x, path.back().y).state == FREE ) return true;
    else return false;
}

void Ally::OrientarSprite()
{
    switch(allyPosition){
        case FRONT:
            //cout << "Fica de frente" << endl;
            sp.SetAnimation(0, 4);
            break;
        case BACK:
            //cout << "Fica de costas" << endl;
            sp.SetAnimation(3, 4);
            break;
        case LEFT:
            //cout << "Fica pra esquerda" << endl;
            sp.SetAnimation(1, 4);
            break;
        case RIGHT:
            //cout << "Fica pra direita" << endl;
            sp.SetAnimation(2, 4);
            break;
    }
}

void Ally::Abrir_Menu(){
    float offSet = 125;
    float angulo = 0;
#ifdef ANDRE
    Sprite botao("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoMover.png");
    Sprite botao2("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoDefender.png");
    Sprite botao3("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoItens.png");
    Sprite botao4("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoEspecial.png");
#endif
#ifdef MASHIRO
    Sprite botao("images/img/botaoMover.png");
    Sprite botao2("images/img/botaoDefender.png");
    Sprite botao3("images/img/botaoItens.png");
    Sprite botao4("images/img/botaoEspecial.png");
#endif
    StillAnimation* botaoAnim = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);
    angulo += 90;

    StillAnimation* botaoAnim2 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao2, 50, false);
    buttonArray.emplace_back(*botaoAnim2);
    angulo += 90;

    StillAnimation* botaoAnim3 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao3, 50, false);
    buttonArray.emplace_back(*botaoAnim3);
    angulo += 90;

    StillAnimation* botaoAnim4 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao4, 50, false);
    buttonArray.emplace_back(*botaoAnim4);
    angulo += 90;
}

bool Ally::IsLider()
{
    return lider;
}

string Ally::GetNome()
{
    return this->nome;
}

bool Ally::AreaRespiro()
{
//    if((box.RectCenterX() > 500 && box.RectCenterX() < 770) && (box.RectCenterY() > 100 && box.RectCenterY() < 300)){
//        return true;
//    }

    return false;
}

bool Ally::AreaMapa()
{
    if(box.RectCenterX() > 730){
        return false;
    }

    return true;
}

int Ally::GetVida()
{
    return this->vida.GetVida();
}

