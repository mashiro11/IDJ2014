#include "Piloto.h"

/*Aguardando embarcar, andar, barra de vida do menu nao acompanha mais*/

Piloto::Piloto(Character* robo, string nome, Sprite sprite, bool lider, TileMap* mapRef)
{

    sp = sprite;
    this->speed = speed;
    this->robo = robo;
    this->nome = nome;
    this->lider = lider;
    box.SetRectCenterX(robo->box.RectCenterX());
    box.SetRectCenterY(robo->box.RectCenterY());
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();

    this->defesa = defesa;
    this->range = range;
    this->distance = distance;
    this->coolDown = coolDown;
    this->rotation = 0;
    allyPosition = FRONT;
    charState = REPOUSO;
    menuAberto = false;

}

Piloto::~Piloto()
{

}

bool Piloto::Is(string type)
{
    if(type == "Piloto" || type == "Ally"){
        return true;
    }
    return false;
}

void Piloto::Update(float dt)
{
    if(robo == NULL){
        StateMachine(dt);
        Input();
        vida.Update();
        vida.SetX(box.RectCenterX());
        vida.SetY(box.RectCenterY());
    }else{
        box.SetRectCenterX(robo->box.RectCenterX());
        box.SetRectCenterY(robo->box.RectCenterY());
    }
}

void Piloto::StateMachine(float dt)
{
    switch(charState){
            case MOVENDO:
                if( path.empty() == true){
                    cout << "Path vazio" << endl;
                    charState = REPOUSO;
                    break;
                }else{
                    Andar();
                }
                break;
            case AGUARDANDO_EMBARCAR:
//                Character* alvo = NULL;
//                Encontrar_Robo(alvo);
//                Embarcar(alvo);
                    charState = REPOUSO;
                break;
            case INATIVO:
                break;
            case REPOUSO:
                break;
            case AGUARDANDO_ANDAR:

            //if(InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) == true){
                   MakePath();
            //}
                if(InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON) == true){
                        charState = MOVENDO;
                }

                break;
    }
}

void Piloto::Input()
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
    //verifica se houve evento de clique do mouse
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
        //se o mouse estiver dentro do personagem, o menu é aberto e recebe true se nao existir.
        //se o menu ja existir, recebe falso, pois sera fechado mais para frente.
        if(this->box.IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                              InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                if(menuAberto == false){
                    Camera::Follow(this);
                    Abrir_Menu_Piloto();
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
                   //charState = AGUARDANDO_ANDAR;
                   break;
               case(1):
                   cout << "esse botao pede para embarcar" << endl;
                   charState = AGUARDANDO_EMBARCAR;
                   break;
               }
            }

            //se a flag estiver como falsa, fecha o menu

        }
        if (menuAberto == false){
            Fechar_Menu();
        }
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
                buttonArray[i].SetX(box.RectCenterX() + cos(angulo*M_PI/180)*offSet);
                buttonArray[i].SetY(box.RectCenterY() + sin(angulo*M_PI/180)*offSet);
                buttonArray[i].Render(cameraX,cameraY);
                angulo += 180;
            }
        }else{
            vida.Render(cameraX, cameraY);
        }
    }
}

void Piloto::Embarcar(Character* alvo)
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

void Piloto::Abrir_Menu_Piloto()
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

    Sprite botao2("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/botaoItens.png");
    StillAnimation* botaoAnim2 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao2, 50, false);
    buttonArray.emplace_back(*botaoAnim2);
    angulo += angOffset;
}

void Piloto::Ejetar()
{
    CharacterPosition position = robo->GetCharacterPosition();
    switch(position){
    case(FRONT):
        box.SetRectCenterX(robo->box.RectCenterX());
        box.SetRectCenterY(robo->box.RectCenterY() - 50);
        break;
    case(RIGHT):
        box.SetRectCenterX(robo->box.RectCenterX() - 50);
        box.SetRectCenterY(robo->box.RectCenterY());
        break;
    case(BACK):
        box.SetRectCenterX(robo->box.RectCenterX());
        box.SetRectCenterY(robo->box.RectCenterY() + 50);
        break;
    case(LEFT):
        box.SetRectCenterX(robo->box.RectCenterX() + 50);
        box.SetRectCenterY(robo->box.RectCenterY());
        break;
    }

//    int roboY = robo->GetCurrentX();
//    int roboX = robo->GetCurrentY() + 1;

//    cout << roboY << endl;
//    box.SetRectCenterX( roboX );
//    box.SetRectCenterY( roboY );
//    currentPosition.SetPoint( roboX, roboY );

    robo = NULL;

//    mapReference->At(roboX, roboY).state = ALLY;
//    mapReference->At(roboX, roboY).occuper = this;

}
void Piloto::Encontrar_Robo(Character *alvo)
{

}
