#include "../include/Piloto.h"

Piloto::Piloto(Character* robo, string nome, Sprite sprite, bool lider, TileMap* mapRef)
{
    sp = sprite;
    sp.SetSpriteSheet(1, 1);
    sp.SetAnimation(0, 1);
    sp.SetFrameTime(1);
    this->speed = speed;
    this->robo = robo;
    this->nome = nome;
    this->lider = lider;
    mapReference = mapRef;
    box.SetRectCenterX(robo->box.RectCenterX());
    box.SetRectCenterY(robo->box.RectCenterY());
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    tileNumber = 1;

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
        Input(dt);
        vida.Update();
        vida.SetX(box.RectCenterX());
        vida.SetY(box.RectCenterY());
        if(IsDead() == true){
            cout << this->nome <<": Fui morrido!! gwaa a a a.... D: " << endl;
            mapReference->At( currentPosition.x, currentPosition.y ).state = FREE;
            mapReference->At( currentPosition.x , currentPosition.y ).occuper = NULL;
        }
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
                    cout << endl << "*" << this->nome << " parou*" << endl;
                    charState = REPOUSO;
                    break;
                }else{
                    cout << "*" << this->nome << " esta andando*\r";
                    Andar();
                }
                break;
            case AGUARDANDO_EMBARCAR:
                Ally* alvo;
                alvo = EncontrarRobo();
                if(alvo != NULL){
                    if(Embarcar(alvo) == true){
                        charState = INATIVO;
                    }else{
                        charState = AGUARDANDO_EMBARCAR;
                    }
                }
                if(InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT) == true){
                    charState = REPOUSO;
                }
                break;

            case INATIVO:
                break;
            case REPOUSO:
                break;
            case AGUARDANDO_ANDAR:

            //if(InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON) == true){
                MakePath();
                if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
                        if(ValidPath() == true){
                                charState = MOVENDO;
                        }else{
                                while(path.empty() == false) path.pop();
                                charState = REPOUSO;
                        }
                        barraCooldown.Esvazia();
                }
                break;
    }
}

void Piloto::Input(float dt)
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
                   charState = AGUARDANDO_ANDAR;
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

bool Piloto::Embarcar(Ally* alvo)
{
    if(alvo->Embarcar(this) == true){
        Sound soundFX("images/audio/boom.wav");
        soundFX.Play(0);
        robo = alvo;
        box.SetRectCenterX(robo->box.RectCenterX());
        box.SetRectCenterY(robo->box.RectCenterY());
        return true;
    }else{
        return false;
    }

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
    float offSet = 100;
    float angulo = 0;
    float angOffset = 180;
    Sprite botao(BOTAO_ANDAR);
    Sprite botao2(BOTAO_EMBARCAR);

    StillAnimation* botaoAnim = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);
    angulo += angOffset;


    StillAnimation* botaoAnim2 = new StillAnimation(box.RectCenterX() + cos(angulo*M_PI/180)*offSet,
                                                   box.RectCenterY() + sin(angulo*M_PI/180)*offSet,
                                                   rotation, botao2, 50, false);
    buttonArray.emplace_back(*botaoAnim2);
    angulo += angOffset;
}


bool Piloto::Ejetar()
{

    Sound soundFX("images/audio/boom.wav");
    soundFX.Play(0);

    Ally* robot = (Ally*) robo;
    int pilotoX = robo->GetCurrentX();
    int pilotoY = robo->GetCurrentY();

    CharacterPosition position = robot->GetAllyPosition();
    switch(position){
    case(FRONT):
        pilotoY -= 1;
        break;
    case(RIGHT):
        pilotoX -= 1;
        break;
    case(BACK):
        pilotoY += 1;
        break;
    case(LEFT):
        pilotoX += 1;
        break;
    }

    if(mapReference->At(pilotoX, pilotoY).state == FREE){
        box.SetRectCenterX( mapReference->MapPositionToPixelPosition(pilotoX) );
        box.SetRectCenterY( mapReference->MapPositionToPixelPosition(pilotoY) );
        currentPosition.SetPoint( pilotoX, pilotoY);

        robo = NULL;

        mapReference->At(pilotoX, pilotoY).state = ALLY;
        mapReference->At(pilotoX, pilotoY).occuper = this;
        return true;
    }
    return false;
}

Ally* Piloto::EncontrarRobo()
{
    Ally* alvo = NULL;
    if(InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT) == true){
        int mapX = mapReference->PixelPositionToMapPosition(InputManager::GetInstance().GetMouseX() + Camera::pos.x);
        int mapY = mapReference->PixelPositionToMapPosition(InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        //cout << "MAPX: " << mapX << " | MAPY: " << mapY << endl;
        int pilotoX = mapReference->PixelPositionToMapPosition(box.RectCenterX());
        int pilotoY = mapReference->PixelPositionToMapPosition(box.RectCenterY());
        //cout << "PILOTOX: " << pilotoX << " | PILOTOY: " << pilotoY << endl;

        if( (mapX >= pilotoX - 1) && (mapX <= pilotoX + 1) ){
            if( (mapY >= pilotoY - 1) && (mapY <= pilotoY + 1) ) {
                if(mapReference->At( mapX, mapY ).state == ALLY){
                    if(mapReference->At( mapX, mapY ).occuper->Is("Robo")){
                        Ally* robo = (Ally*) mapReference->At( mapX, mapY ).occuper;
                        alvo = robo;
                    }
                }
            }
        }
    }

    return alvo;
}

void Piloto::Danificar(float dano)
{
    Sprite hit(HIT);
    Game::GetInstance().GetCurrentState().AddObject(new StillAnimation(box.RectCenterX() + 10,
                                                                       box.RectCenterY() - 15, rotation, hit, 0.5, true));
    if(robo == NULL){
        int vidaNova = vida.GetVida();
        vidaNova -= dano - defesa/10;
        if(vidaNova < 0){
            vidaNova = 0;
        }
        vida.SetVida(vidaNova);
    }
}

void Piloto::Morrer()
{
    vida.SetVida(0);
}
