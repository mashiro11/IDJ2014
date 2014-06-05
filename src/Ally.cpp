#include "Ally.h"

//gerencia as modificacoes e os estados  do ally
void Ally::Update(float dt)
{
    sp.Update(dt);
    if(timer.Get() < coolDown) timer.Update(dt);
    //verifica se houve evento de clique do mouse
    if(InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON) == true){
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
                            allyState = AGUARDANDO;
                            break;
                        case(1):
                            cout << "esse botao pede para defender" << endl;
                            allyState = DEFENDENDO;
                            break;
                        case(2):
                            cout << "esse botao pede para usar item" << endl;
                            allyState = AGUARDANDO;
                            break;
                        case(3):
                            cout << "esse botao pede para ejetar" << endl;
                            allyState = AGUARDANDO;
                            break;
                        }
            }
        }
        //se a flag estiver como falsa, fecha o menu
        if (menuAberto == false){
            Fechar_Menu();
        }
    }
    switch(allyState){
            case MOVENDO:
                if( path.empty() == true){
                    cout << "Path vazio" << endl;
                    allyState = REPOUSO;
                    break;
                }else{
                    Andar();
                }
                break;

            case DEFENDENDO:
                break;

            case INATIVO:
                break;

            case ATACANDO:
                break;

            case REPOUSO:
                break;
            case AGUARDANDO:
                //if(InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) == true){
                        MakePath(PixelPositionToMapPosition( InputManager::GetInstance().GetMouseX() + Camera::pos.x ),
                                 PixelPositionToMapPosition( InputManager::GetInstance().GetMouseY() + Camera::pos.y ));
                //}
                if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
                        allyState = MOVENDO;
                }
                break;
    }
}

Point Ally::MapPosition()
{
    return Point( (int)(box.x + Camera::pos.x)/mapReference->GetTileSize(),
                  (int)(box.y + Camera::pos.y)/mapReference->GetTileSize());
}

float Ally::TileCenter(int coord)
{
    return coord * mapReference->GetTileSize() + mapReference->GetTileSize()/2;
}

void Ally::MapPositionToPixelPosition(int line, int row)
{
    if(box.w <= mapReference->GetTileSize()) box.SetRectCenterX(mapReference->GetTileSize() * line + mapReference->GetTileSize()/2.0 );
    else box.SetRectCenterX(mapReference->GetTileSize() * (line + 1) );

    if(box.h <= mapReference->GetTileSize()) box.SetRectCenterY(mapReference->GetTileSize() * row + mapReference->GetTileSize()/2.0);
    else box.SetRectCenterY(mapReference->GetTileSize() * (row + 1) );
}

int Ally::PixelPositionToMapPosition(int pixels)
{
    return pixels/mapReference->GetTileSize();
}

void Ally::MakePath(int line, int row)
{
    if(path.size() < distance){
        //esse é o método que irá conter o pathFinding e validar o caminho de destinho.
        //aqui será feita verificação de caminho possível/impossível.
        Point newPoint(line, row);
        //se nao houver esse ponto no caminho, adiciona
        if(newPoint.x != path.back().x ||
           newPoint.y != path.back().y){
                path.push( newPoint );
                cout << "ponto ( " << newPoint.x << ", " << newPoint.y << ") adicionado" << endl;
        }
    }
}

//verifica se ally esta morto
bool Ally::IsDead(){
    if(this->hp <= 0){
        if(Camera::GetFocus() == this) Camera::Unfollow();
        return true;
    }
    return false;
}

//movimenta o ally pelo mapa.
void Ally::Andar(){
            if( abs(box.RectCenterX() - TileCenter( path.front().x ) ) < 3 &&
                abs(box.RectCenterY() - TileCenter( path.front().y ) ) < 3){
                    box.SetRectCenterX( TileCenter( path.front().x ) );
                    box.SetRectCenterY( TileCenter( path.front().y ) );
                    path.pop();
            }
            if( TileCenter( path.front().x ) > box.RectCenterX() ){
                box.SetRectCenterX(box.RectCenterX() + speed);
                allyPosition = RIGHT;
            }else if( TileCenter( path.front().x ) < box.RectCenterX() ){
                box.SetRectCenterX(box.RectCenterX() - speed);
                allyPosition = LEFT;
            }

            if( TileCenter( path.front().y ) > box.RectCenterY() ){
                box.SetRectCenterY(box.RectCenterY() + speed);
                allyPosition = FRONT;
            }else if( TileCenter( path.front().y ) < box.RectCenterY() ){
                box.SetRectCenterY(box.RectCenterY() - speed);
                allyPosition = BACK;
            }
            OrientarSprite();
}

void Ally::OrientarSprite()
{
    switch(allyPosition){
        case FRONT:
            sp.SetAnimation(0, 4);
            break;
        case BACK:
            sp.SetAnimation(3, 4);
            break;
        case LEFT:
            sp.SetAnimation(1, 4);
            break;
        case RIGHT:
            sp.SetAnimation(2, 4);
            break;
    }
}

//para a movimentacao do ally caso este encontre um obstaculo pelo caminho.
void Ally::Parar(){

}

//reduz a vida do ally
void Ally::Danificar(float dano){
    this->hp -= dano - defesa/10;
}

//notifica as colisoes de ally
void Ally::NotifyCollision(GameObject &other)
{

}

//retorna true se o tipo passado for Ally
bool Ally::Is(string type){
    if(type == "Ally"){
        return true;
    }
    return false;
}

//anima o personagem com seu ataque basico.
void Ally::Atacar(){

}

//gerencia o ally em seu modo de defesa.
void Ally::Defender(){

}

////abre o menu de personagem
void Ally::Abrir_Menu(){
    float offSet = 125;
    float angulo = 0;
    Sprite botao("images/img/botaoMover.png");
    StillAnimation* botaoAnim = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);
    angulo += 90;
    Sprite botao2("images/img/botaoDefender.png");
    StillAnimation* botaoAnim2 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao2, 50, false);
    buttonArray.emplace_back(*botaoAnim2);
    angulo += 90;
    Sprite botao3("images/img/botaoItens.png");
    StillAnimation* botaoAnim3 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao3, 50, false);
    buttonArray.emplace_back(*botaoAnim3);
    angulo += 90;
    Sprite botao4("images/img/botaoEspecial.png");
    StillAnimation* botaoAnim4 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao4, 50, false);
    buttonArray.emplace_back(*botaoAnim4);
    angulo += 90;
}

int Ally::GetHitPoint()
{
    return hp;
}

//fecha o menu de personagem
void Ally::Fechar_Menu(){
    buttonArray.clear();
}

//coloca um item no vetor de itens do ally
void Ally::Alocar_Item(){

}

void Ally::Usar_Item(){

}

//ejeta o piloto do robo
void Ally::Ejetar(){

}

//embarca um piloto no robo
void Ally::Embarcar(){

}

//gerencia o uso de especial
void Ally::Especial(){

}

Sprite* Ally::VerificaVida(){
    string path;
    if(hp > 90){
        path = "images/img/hpbar100.png";
    }else if(hp > 80){
        path = "images/img/hpbar90.png";
    }else if(hp > 70){
        path = "images/img/hpbar80.png";
    }else if(hp > 60){
        path = "images/img/hpbar70.png";
    }else if(hp > 50){
        path = "images/img/hpbar60.png";
    }else if(hp > 40){
        path = "images/img/hpbar50.png";
    }else if(hp > 30){
        path = "images/img/hpbar40.png";
    }else if(hp > 20){
        path = "images/img/hpbar30.png";
    }else if(hp > 10){
        path = "images/img/hpbar20.png";
    }else if(hp > 0){
        path = "images/img/hpbar10.png";
    }else{
        path = "images/img/hpbar0.png";
    }
    Sprite* vida = new Sprite(path);
    return vida;
}
