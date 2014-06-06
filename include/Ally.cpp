#include "Ally.h"

Ally::Ally()
{

}

//gerencia as modificacoes e os estados  do ally
void Ally::UpdateAlly(float dt)
{

    switch(allyState){
            case MOVENDO:
                if( PixelPositionToMapPosition(box.x, tileSize) == destiny.x &&
                    PixelPositionToMapPosition(box.y, tileSize) == destiny.y){
                    allyState = REPOUSO;
                    break;
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
                if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
                        SetDestiny(PixelPositionToMapPosition( InputManager::GetInstance().GetMouseX() + Camera::pos.x, tileSize ),
                                   PixelPositionToMapPosition( InputManager::GetInstance().GetMouseY() + Camera::pos.y, tileSize ));
                        cout << "destino: " << destiny.x << "x" << destiny.y << endl;
                        allyState = MOVENDO;
                }
                break;
    }

    if(allyState != INATIVO){
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
                                cout << "esse botao pede para ejetar/embarcar" << endl;
                                this->Ejetar();
                                break;
                            case(2):
                                cout << "esse botao pede para usar item" << endl;
                                break;
                            case(3):
                                cout << "esse botao pede para usar especial" << endl;
                                break;
                            case(4):
                                cout << "esse botao pede para defender" << endl;
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


}

Point Ally::MapPosition(int tileWidth, int tileHeight)
{
    return Point( (int)(box.x + Camera::pos.x)/tileWidth,
                  (int)(box.y + Camera::pos.y)/tileHeight);
}

void Ally::MapPositionToPixelPosition(int line, int row, int tileSize)
{
    if(box.w <= tileSize) box.SetRectCenterX(tileSize * line + (tileSize)/2.0 );
    else box.SetRectCenterX(tileSize * (line + 1) );

    if(box.h <= tileSize) box.SetRectCenterY(tileSize * row + (tileSize)/2.0);
    else box.SetRectCenterY(tileSize * (row + 1) );
}

int Ally::PixelPositionToMapPosition(int pixels, int tileSize)
{
    return pixels/tileSize;
}

void Ally::SetDestiny(int line, int row)
{
    //esse é o método que irá conter o pathFinding e validar o caminho de destinho.
    //aqui será feita verificação de caminho possível/impossível.
    destiny.SetPoint(line, row);
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





