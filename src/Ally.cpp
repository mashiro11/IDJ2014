#include "Ally.h"

Ally::Ally()
{

}

//gerencia as modificacoes e os estados  do ally
void Ally::UpdateAlly(float dt)
{
    if(allyState != INATIVO){
        if(timer.Get() < coolDown) timer.Update(dt);
        //verifica se houve evento de clique do mouse
        if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
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
                       allyState = AGUARDANDO_ANDAR;
                       break;
                   case(1):
                       cout << "esse botao pede para defender" << endl;
                       allyState = DEFENDENDO;
                       break;
                   case(2):
                       cout << "esse botao pede para usar item" << endl;
                       allyState = AGUARDANDO_ITEM;
                       break;
                   case(3):
                       cout << "esse botao pede para ejetar" << endl;
                       allyState = AGUARDANDO_EMBARCAR;
                       break;
                   }
                }
            }
            //se a flag estiver como falsa, fecha o menu
            if (menuAberto == false){
                Fechar_Menu();
            }
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
            case AGUARDANDO_ANDAR:
            //if(InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) == true){

                   MakePath(PixelPositionToMapPosition( InputManager::GetInstance().GetMouseX() + Camera::pos.x ),
                                 PixelPositionToMapPosition( InputManager::GetInstance().GetMouseY() + Camera::pos.y ));
                //}
                 //  cout << "HOU" << endl;
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

float Ally::MapPositionToPixelPosition(int coord)
{
    return mapReference->GetTileSize() * coord + mapReference->GetTileSize()/2.0;
}

int Ally::PixelPositionToMapPosition(int pixels)
{
    return pixels/mapReference->GetTileSize();
}

//verifica se ally esta morto
bool Ally::IsDead(){
    if(this->vidaAtual <= 0){
        if(Camera::GetFocus() == this) Camera::Unfollow();
        return true;
    }
    return false;
}

//movimenta o ally pelo mapa.
void Ally::Andar(){
            //cout << "inicio allyPosition: " << allyPosition << endl;
            if( abs(box.RectCenterX() - TileCenter( path.front().x ) ) < 0.5 &&
                abs(box.RectCenterY() - TileCenter( path.front().y ) ) < 0.5){
                    box.SetRectCenterX( TileCenter( path.front().x ) );
                    box.SetRectCenterY( TileCenter( path.front().y ) );
                    path.pop();
            }else{
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
            }
            OrientarSprite();
}

//para a movimentacao do ally caso este encontre um obstaculo pelo caminho.
void Ally::Parar(){

}

//reduz a vida do ally
void Ally::Danificar(float dano){
    this->vidaAtual -= dano - defesa/10;
}

//notifica as colisoes de ally
void Ally::NotifyCollision(GameObject &other)
{

}

//anima o personagem com seu ataque basico.
void Ally::Atacar(){

}

//gerencia o ally em seu modo de defesa.
void Ally::Defender(){

}

//abre o menu de personagem


//fecha o menu de personagem
void Ally::Fechar_Menu(){
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

void Ally::MakePath(int line, int row)
{
    if(path.size() < distance){
        //se a posicao no mapa é acessivel
        if(mapReference->At(line, row).state == FREE ||
           mapReference->At(line, row).state == ALLY){
                    //cout << "ponto ( " << line << ", " << row << ") adicionado" << endl;
                    //cout << "mapStateAt( " << line << ", " << row << "): " << mapReference->At(line, row).state << endl;

                    //se a lista de pontos estiver vazia ou
                    //se o novo ponto for vizinho do ponto anterior
                    Point newPoint(line, row);
                    if( path.empty() == true ||
                       (newPoint.x == path.back().x && abs(newPoint.y - path.back().y) == 1) ||
                       (newPoint.y == path.back().y && abs(newPoint.x - path.back().x) == 1) ){

                            //se o novo ponto for diferente do ponto anterior
                            if(newPoint.x != path.back().x ||
                               newPoint.y != path.back().y){
                                    path.push( newPoint );
                                    cout << "ponto ( " << newPoint.x << ", " << newPoint.y << ") adicionado" << endl;
                            }
                    }
        }
    }
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




