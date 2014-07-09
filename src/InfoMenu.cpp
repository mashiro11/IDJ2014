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
    texto.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 60,Text::TEXT_SOLID, "0", color);
    #endif
    #ifdef MASHIRO
    texto.Initialize("images/font/Call me maybe.ttf", 60,Text::TEXT_SOLID, "Inicio", color);
    #endif
    texto.SetPos(x + 75, y + 550, true, true);
}

void InfoMenu::Update(float dt){

    for(int i = 0; i < vidaArray.size(); i++){
        if(objectArray[i] != NULL){
            float porCento = objectArray[i]->GetPorcentagemVida();
            vidaArray[i].SetVida(porCento);
            vidaArray[i].SetX(buttonArray[i].box.RectCenterX() + 120);
            vidaArray[i].SetY(buttonArray[i].box.RectCenterY());
        }
    }

    //se houver um clique em um desses botoes do menu lateral, a camera segue o objeto clicado.
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON) == true){
        for(int i = 0; i < buttonArray.size(); i++){
            if(buttonArray[i].box.IsInside(InputManager::GetInstance().GetMouseX(),
                                           InputManager::GetInstance().GetMouseY())){
                if(objectArray[i] != NULL){
                        Camera::Follow(objectArray[i]);
                }
            }
        }
    }
    GerenciaCronometro(dt);
}

void InfoMenu::GerenciaCronometro(float dt)
{
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

void InfoMenu::InsereBotao(Ally* objeto){
    string caminho;
    #ifdef ANDRE
    if(objeto->Is("Robo")){
        if(objeto->GetNome() == "Robotinic"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboPrataIcone.png";
        }else if(objeto->GetNome() == "Roboboy"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboRosaIcone.png";
        }else if(objeto->GetNome() == "Blitzcrank"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboVerdeIcone.png";
        }else if(objeto->GetNome() == "OptimusPrime"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboPretoIcone.png";
        }else if(objeto->GetNome() == "Bamboubi"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboAmareloIcone.png";
        }else if(objeto->GetNome() == "Walle"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboAzulIcone.png";
        }else if(objeto->GetNome() == "Gurren"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboVermelhoIcone.png";
        }else if(objeto->GetNome() == "ApoloBR"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboMarromIcone.png";
        }
    }else if(objeto->Is("Piloto")){
        if(objeto->GetNome() == "Joao"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinfaceIcone.png";
        }else if(objeto->GetNome() == "Joana"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface2Icone.png";
        }else if(objeto->GetNome() == "Jose"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface5Icone.png";
        }else if(objeto->GetNome() == "Josea"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface6Icone.png";
        }else if(objeto->GetNome() == "Mario"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface4Icone.png";
        }else if(objeto->GetNome() == "Maria"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface3Icone.png";
        }else if(objeto->GetNome() == "Batata"){
             caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface7Icone.png";
        }else if(objeto->GetNome() == "Digglet"){
            caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/penguinface8Icone.png";
        }
    }
    #endif
    #ifdef MASHIRO
    if(objeto->Is("Robo")){
        if(objeto->GetNome() == "Robotinic"){
            caminho = "images/img/roboPrataIcone.png";
        }else if(objeto->GetNome() == "Roboboy"){
            caminho = "images/img/roboRosaIcone.png";
        }else if(objeto->GetNome() == "Blitzcrank"){
            caminho = "images/img/roboVerdeIcone.png";
        }else if(objeto->GetNome() == "OptimusPrime"){
            caminho = "images/img/roboPretoIcone.png";
        }else if(objeto->GetNome() == "Bamboubi"){
            caminho = "images/img/roboAmareloIcone.png";
        }else if(objeto->GetNome() == "Walle"){
            caminho = "images/img/roboAzulIcone.png";
        }else if(objeto->GetNome() == "Gurren"){
            caminho = "images/img/roboVermelhoIcone.png";
        }else if(objeto->GetNome() == "ApoloBR"){
            caminho = "images/img/roboMarromIcone.png";
        }
    }else if(objeto->Is("Piloto")){
        if(objeto->GetNome() == "Joao"){
            caminho = "images/img/penguinfaceIcone.png";
        }else if(objeto->GetNome() == "Joana"){
            caminho = "images/img/penguinface2Icone.png";
        }else if(objeto->GetNome() == "Jose"){
            caminho = "images/img/penguinface5Icone.png";
        }else if(objeto->GetNome() == "Josea"){
            caminho = "images/img/penguinface6Icone.png";
        }else if(objeto->GetNome() == "Mario"){
            caminho = "images/img/penguinface4Icone.png";
        }else if(objeto->GetNome() == "Maria"){
            caminho = "images/img/penguinface3Icone.png";
        }else if(objeto->GetNome() == "Batata"){
            caminho = "images/img/penguinface7Icone.png";
        }else if(objeto->GetNome() == "Digglet"){
            caminho = "images/img/penguinface8Icone.png";
   }
    }
    #endif

    Sprite botao(caminho);
    StillAnimation* botaoAnim = new StillAnimation(box.x + 40, box.y + 30 + 40*buttonArray.size(), 0, botao, 50, false);
    buttonArray.emplace_back(*botaoAnim);

    BarraVidaMenu vidaMenu(0,0);

    vidaArray.emplace_back(vidaMenu);

    objectArray.emplace_back(objeto);
}

bool InfoMenu::IsDead()
{
    return false;
}

void InfoMenu::NotificarMorte(string nome)
{
    for(int i = 0; i < objectArray.size(); i++){
       if(objectArray[i] != NULL){
           if(objectArray[i]->GetNome() == nome){
               vidaArray[i].SetVida(0);
               objectArray[i] = NULL;
           }
        }
    }
}

void InfoMenu::Reordenar()
{
//    int j = 0;
//    for(int i = 0; i < objectArray.size(); i++){
//        if(objectArray[i]->Is("Robo")){
//            RefazBotao(objectArray[i], j);
//            //vector<Piloto*> pilotos;
//            //recebe os pilotos do robo e refaz os botoes
//            i++;

//        }else if(objectArray[i]->Is("Piloto")){
////            if(objectArray[i])
//            //se o robo for NULL, coloca o piloto no fim do array. Colocar em outro for??
//        }

//    }
}

void InfoMenu::RefazBotao(Ally* objeto, int index)
{
//    string caminho;
//    if(objeto->GetNome() == "Robotinic"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboPrataIcone.png";
//    }else if(objeto->GetNome() == "Roboboy"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboRosaIcone.png";
//    }else if(objeto->GetNome() == "Blitzcrank"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboVerdeIcone.png";
//    }else if(objeto->GetNome() == "OptimusPrime"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboPretoIcone.png";
//    }else if(objeto->GetNome() == "Bamboubi"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboAmareloIcone.png";
//    }else if(objeto->GetNome() == "Walle"){
//        caminho = "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboAzulIcone.png";
//    }else if(objeto->GetNome() == "Joao"){
//        caminho = "images/img/penguinfaceIcone.png";
//    }else if(objeto->GetNome() == "Joana"){
//        caminho = "images/img/penguinface2Icone.png";
//    }else if(objeto->GetNome() == "Jose"){
//        caminho = "images/img/penguinface5Icone.png";
//    }else if(objeto->GetNome() == "Josea"){
//        caminho = "images/img/penguinface6Icone.png";
//    }else if(objeto->GetNome() == "Mario"){
//        caminho = "images/img/penguinface4Icone.png";
//    }else if(objeto->GetNome() == "Maria"){
//        caminho = "images/img/penguinface3Icone.png";
//    }
//}

//    Sprite botao(caminho);
//    StillAnimation* botaoAnim = new StillAnimation(box.x + 30, box.y + 30 + 50*buttonArray.size(), rotation, botao, 50, false);

}
