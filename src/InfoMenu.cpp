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
    Reordenar();
    for(int j = 0; j < vidaArray.size(); j++){
        vidaArray[j].Update();
    }
    //se houver um clique em um desses botoes do menu lateral, a camera segue o objeto clicado.
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
        for(int i = 0; i < buttonArray.size(); i++){
            if(buttonArray[i].box.IsInside(InputManager::GetInstance().GetMouseX(),
                                           InputManager::GetInstance().GetMouseY())){
                if(objectArray[i] != NULL){
                    if(objectArray[i]->IsDead() == false){
                        Camera::Follow(objectArray[i]);
                    }
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
    if(objeto->Is("Robo")){
        //cout << objeto->GetNome() << endl;
        if(objeto->GetNome() == "Robotinic"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface.png";
        }else if(objeto->GetNome() == "Roboboy"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface2.png";
        }else if(objeto->GetNome() == "Blitzcrank"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface3.png";
        }else if(objeto->GetNome() == "OptimusPrime"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface4.png";
        }else if(objeto->GetNome() == "Bamboubi"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface5.png";
        }else if(objeto->GetNome() == "Walle"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface6.png";
        }
    }else if(objeto->Is("Piloto")){
        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png";
    }
    #endif
    #ifdef MASHIRO
    if(objeto->Is("Robo")){
        //cout << objeto->GetNome() << endl;
        if(objeto->GetNome() == "Robotinic"){
            caminho = "images/img/penguinface.png";
        }else if(objeto->GetNome() == "Roboboy"){
            caminho = "images/img/penguinface2.png";
        }else if(objeto->GetNome() == "Blitzcrank"){
            caminho = "images/img/penguinface3.png";
        }else if(objeto->GetNome() == "OptimusPrime"){
            caminho = "images/img/penguinface4.png";
        }else if(objeto->GetNome() == "Bamboubi"){
            caminho = "images/img/penguinface5.png";
        }else if(objeto->GetNome() == "Walle"){
            caminho = "images/img/penguinface6.png";
        }
    }else if(objeto->Is("Piloto")){
        caminho = "images/img/alien.png";
    }
    #endif

    Sprite botao(caminho);
    botao.SetScaleX(0.5);
    botao.SetScaleY(0.5);
    StillAnimation* botaoAnim = new StillAnimation(box.x + 30, box.y + 30 + 50*buttonArray.size(), rotation, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);


    BarraVida vida(objeto, 100);

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

void InfoMenu::NotificarMorte(GameObject &objeto)
{
    cout << "MURREU!!" << endl;
    cout << objectArray.size() << endl;
    for(int i = 0; i < objectArray.size(); i++){
        if(&objeto == objectArray[i]){
            cout << "IGUAL" << endl;
            objectArray[i] = NULL;
        }
    }
}

void InfoMenu::Reordenar()
{
//    int j = 0;
//    for(int i = 0; i < objectArray.size(); i++){
//        if(objectArray[i]->Is("Robo")){
//            RefazBotao(objectArray[i], j);
//            vector<Piloto*> pilotos;
//            //recebe os pilotos do robo e refaz os botoes


//        }else if(objectArray[i]->Is("Piloto")){
////            if(objectArray[i])
//            //se o robo for NULL, coloca o piloto no fim do array. Colocar em outro for??
//        }

//    }
}

void InfoMenu::RefazBotao(GameObject* objeto, int index)
{
//    string caminho;
//    if(objeto->GetNome() == "Robotinic"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface.png";
//    }else if(objeto->GetNome() == "Roboboy"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface2.png";
//    }else if(objeto->GetNome() == "Blitzcrank"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface3.png";
//    }else if(objeto->GetNome() == "OptimusPrime"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface4.png";
//    }else if(objeto->GetNome() == "Bamboubi"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface5.png";
//    }else if(objeto->GetNome() == "Walle"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface6.png";
//    }

//    Sprite botao(caminho);
//    botao.SetScaleX(0.5);
//    botao.SetScaleY(0.5);
//    StillAnimation* botaoAnim = new StillAnimation(box.x + 30, box.y + 30 + 50*buttonArray.size(), rotation, botao, 50, false);
    //inserir o botao na posicao index
}
