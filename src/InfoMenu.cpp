#include "InfoMenu.h"
#include <sstream>

InfoMenu::InfoMenu(float x, float y):
    cronometro()
{
    #ifdef ANDRE
    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/win.jpg");
    #endif
    #ifdef MASHIRO
    sp.Open("images/img/win.jpg");
    #endif

    box.x = x;
    box.y = y;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    sp.SetScaleX(0.25);
    minutos = 0;

    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;
    #ifdef ANDRE
    texto.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 60,Text::TEXT_SOLID, "Inicio", color);
    #endif
    #ifdef MASHIRO
    texto.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_SOLID, "Inicio", color);
    #endif
    texto.SetPos(x + 75, y + 550, true, true);
}

void InfoMenu::Update(float dt){
    for(int j = 0; j < vidaArray.size(); j++){
        vidaArray[j].Update();
    }
    //se houver um clique em um desses botoes do menu lateral, a camera segue o objeto clicado.
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
        for(int i = 0; i < buttonArray.size(); i++){
            if(buttonArray[i].box.IsInside(InputManager::GetInstance().GetMouseX(),
                                           InputManager::GetInstance().GetMouseY())){
                if(objectArray[i/2]->IsDead() == false){
                    Camera::Follow(objectArray[i]);
                }
            }
        }
    }

    cronometro.Update(dt - 0.003);
    float tempo = cronometro.Get();
    stringstream ss;
    if(tempo >= 60){
        minutos ++;
        cronometro.Restart();
    }

    ss << minutos << " ";
    ss << floorf((tempo) * 100) / 100;;
    texto.SetText(ss.str());
}

void InfoMenu::Render(int cameraX, int cameraY){

    sp.Render(box.x, box.y);
    texto.Render(0,0);
    for(int i = 0; i < buttonArray.size(); i++){
        buttonArray[i].Render(0,0);
    }
    for(int j = 0; j < vidaArray.size(); j++){
        vidaArray[j].Render(0,0);
    }
}

void InfoMenu::InsereBotao(GameObject* objeto){
    string caminho;
    #ifdef ANDRE
    if(objeto->Is("Lider")){
        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/minion.png";
    }else if(objeto->Is("Robo")){
        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface.png";
    }else if(objeto->Is("Piloto")){
        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png";
    }
    #endif
    #ifdef MASHIRO
    if(objeto->Is("Lider")){
        caminho = "images/img/minion.png";
    }else if(objeto->Is("Robo")){
        caminho = "images/img/penguinface.png";
    }else if(objeto->Is("Piloto")){
        caminho = "images/img/alien.png";
    }
    #endif

    Sprite botao(caminho);
    botao.SetScaleX(0.5);
    botao.SetScaleY(0.5);
    StillAnimation* botaoAnim = new StillAnimation(box.x + 30, box.y + 30 + 75*buttonArray.size(), rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);

    BarraVida vida(objeto);

    vida.SetX(botaoAnim->box.RectCenterX() + 100);
    vida.SetY(botaoAnim->box.RectCenterY() - 60);
    vidaArray.emplace_back(vida);

    objectArray.emplace_back(objeto);
}

bool InfoMenu::IsDead(){
    return false;
}

void InfoMenu::NotifyCollision(GameObject &other){

}

bool InfoMenu::Is(string type){
    if(type == "InfoMenu"){
        return true;
    }
    return false;
}


