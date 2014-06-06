#include "Piloto.h"

Piloto::Piloto(float tileSize, float defesa, float vidaMaxima, int coolDown,
               int range, int distance, GameObject* robo, int speed)
{

    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png");
    vida.Open(this);
    this->speed = speed;
    this->robo = robo;
    this->tileSize = tileSize;
    box.SetRectCenterX(robo->box.RectCenterX());
    box.SetRectCenterY(robo->box.RectCenterY());
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    MapPositionToPixelPosition(box.x, box.y, tileSize);

    this->defesa = defesa;
    this->vidaMaxima = vidaMaxima;
    this->range = range;
    this->distance = distance;
    vidaAtual = vidaMaxima;
    this->coolDown = coolDown;
    this->rotation = 0;
    allyPosition = FRENTE;
    allyState = REPOUSO;
    menuAberto = false;
}

Piloto::~Piloto()
{

}

bool Piloto::Is(string type)
{
    if(type == "Piloto"){
        return true;
    }
    return false;
}

void Piloto::Update(float dt)
{
    if(robo == NULL){
        switch(allyState){
                case MOVENDO:
                    if( PixelPositionToMapPosition(box.x, tileSize) == destiny.x &&
                        PixelPositionToMapPosition(box.y, tileSize) == destiny.y){
                        allyState = REPOUSO;
                        break;
                    }
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
                case AGUARDANDO_EMBARCAR:
                    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
                        //tem que ser aliado, robo ou lider, ter espaco e estar proximo.
                        allyState = REPOUSO;
                        //this->Embarcar(alvo);
                    }

                    break;
        }
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

        vida.Update();
        vida.SetX(box.RectCenterX());
        vida.SetY(box.RectCenterY());
    }else{
        box.SetRectCenterX(robo->box.RectCenterX());
        box.SetRectCenterY(robo->box.RectCenterY());
    }
}

void Piloto::Render(int cameraX, int cameraY)
{
    if(robo == NULL){
        sp.Render(box.x - cameraX, box.y - cameraY);
        if(menuAberto){
            int offSet = 100;
            int angulo = 0;
            for(int i = 0; i < buttonArray.size(); i++){
                buttonArray[i].SetX(box.RectCenterX() - 52 + cos(angulo*M_PI/180)*offSet);
                buttonArray[i].SetY(box.RectCenterY() - 20 + sin(angulo*M_PI/180)*offSet);
                buttonArray[i].Render(cameraX,cameraY);
                angulo += 180;
            }
        }else{
            vida.Render(cameraX, cameraY);
        }
    }
}

void Piloto::Embarcar(GameObject* alvo)
{
    robo = alvo;
    box.SetRectCenterX(robo->box.RectCenterX());
    box.SetRectCenterY(robo->box.RectCenterY());
}

void Piloto::SetX(float x)
{
    box.SetRectCenterX(x);
}

void Piloto::SetY(float y)
{
    box.SetRectCenterY(y);
}

void Piloto::Abrir_Menu()
{
    float offSet = 125;
    float angulo = 0;
    float angOffset = 180;

    Sprite botao("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoMover.png");
    StillAnimation* botaoAnim = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);
    angulo += angOffset;

    Sprite botao2("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botao.png");
    StillAnimation* botaoAnim2 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao2, 50, false);
    buttonArray.emplace_back(*botaoAnim2);
    angulo += angOffset;
}

void Piloto::Ejetar()
{
    box.SetRectCenterX(robo->box.RectCenterX());
    box.SetRectCenterY(robo->box.RectCenterY() + 100);
    robo = NULL;
}
