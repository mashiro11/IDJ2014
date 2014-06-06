#include "InfoMenu.h"
#include <sstream>

//problema aqui e que recebe gameobject e precisamos da vida, que pertence aos filhos de gameobject

InfoMenu::InfoMenu(float x, float y, GameObject* objeto):
    sp("images/img/win.jpg"),
    cronometro()
{
    box.x = x;
    box.y = y;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    sp.SetScaleX(0.25);

    SDL_Color color;
    color.r =   0;
    color.b =   0;
    color.g =   0;
    color.a = 255;

    texto.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_SOLID, "Inicio", color);
    texto.SetPos(x + 75, y + 550, true, true);

    if(objeto->Is("Ally") == true){
        //cria uma animacao para o botao no menu lateral
        Sprite botao("images/img/minion.png");
        botao.SetScaleX(0.5);
        botao.SetScaleY(0.5);
        StillAnimation* botaoAnim = new StillAnimation(box.x + 30, box.y + 30, rotation, botao, 50, false);
        buttonArray.emplace_back(*botaoAnim);

        //cria a barra de vida correspondente
        Sprite vida("images/img/hpbar100.png");
        vida.SetScaleX(0.4);
        vida.SetScaleY(0.4);
        StillAnimation* vidaAnim = new StillAnimation(box.x + 130, box.y + 30, rotation, vida, 50, false);
        buttonArray.emplace_back(*vidaAnim);
        objectArray.emplace_back(objeto);
    }
}

void InfoMenu::Update(float dt){
    //se houver um clique em um desses botoes do menu lateral, a camera segue o objeto clicado.
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
        for(int i = 0; i < buttonArray.size(); i++){
            if(buttonArray[i].box.IsInside(InputManager::GetInstance().GetMouseX(),
                                           InputManager::GetInstance().GetMouseY())){
                if(objectArray[i/2]->IsDead() == false){
                    Camera::Follow(objectArray[i/2]);
                }
            }
        }
    }

    cronometro.Update(dt);
    float tempo = cronometro.Get();
    stringstream ss;
    ss << floorf((tempo) * 100) / 100;;
    texto.SetText(ss.str());
}

void InfoMenu::Render(int cameraX, int cameraY){

    sp.Render(box.x, box.y);
    texto.Render(0,0);
    for(int i = 0; i < buttonArray.size(); i++){
        buttonArray[i].Render(0,0);
    }
}

void InfoMenu::InsereBotao(GameObject* objeto){
    if(objeto->Is("Ally")){
        Sprite botao("images/img/minion.png");
        botao.SetScaleX(0.5);
        botao.SetScaleY(0.5);
        StillAnimation* botaoAnim = new StillAnimation(box.x + 30, box.y + 30 + 70*buttonArray.size()/2, rotation, botao, 50, false);
        buttonArray.emplace_back(*botaoAnim);

        Sprite vida("images/img/hpbar100.png");
        vida.SetScaleX(0.4);
        vida.SetScaleY(0.4);
        StillAnimation* vidaAnim = new StillAnimation(box.x + 130, box.y + 70*buttonArray.size()/2, rotation, vida, 50, false);
        buttonArray.emplace_back(*vidaAnim);
        objectArray.emplace_back(objeto);
    }
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

int InfoMenu::GetHitPoint(){

}
