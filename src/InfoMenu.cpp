#include "../include/InfoMenu.h"
#include <sstream>

InfoMenu::InfoMenu(float x, float y):
    cronometro()
{
    sp.Open(INFO_MENU_FILE);

    box.x = x;// - sp.GetWidth();
    box.y = y;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    minutos = 0;

    texto.Initialize(FONT1, 60,Text::TEXT_SOLID, "Inicio");
    texto.SetColor(255, 0, 0);
    texto.SetPos(x + 75, y + 550, true, true);
    showDebug = false;
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
    if(InputManager::GetInstance().KeyPress(SDLK_0)){
        if(showDebug) showDebug = false;
        else showDebug = true;
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
    ss << floorf((tempo) * 100) / 100;
    texto.SetText(ss.str());
}

void InfoMenu::Render(int cameraX, int cameraY){
    sp.Render(box.x, box.y);
    for(int i = 0; i < buttonArray.size(); i++){
        buttonArray[i].Render(0,0);
    }
    for(int j = 0; j < vidaArray.size(); j++){
        vidaArray[j].Render(0,0);
    }
    if(showDebug)texto.Render(0,0);
}

void InfoMenu::InsereBotao(Ally* objeto){
    string caminho;
    if(objeto->Is("Robo")){
        if(objeto->GetNome() == "Robotinic"){
            caminho = MENU_ROBO_ICON1;
        }else if(objeto->GetNome() == "Roboboy"){
            caminho = MENU_ROBO_ICON2;
        }else if(objeto->GetNome() == "Blitzcrank"){
            caminho = MENU_ROBO_ICON3;
        }else if(objeto->GetNome() == "OptimusPrime"){
            caminho = MENU_ROBO_ICON4;
        }else if(objeto->GetNome() == "Bamboubi"){
            caminho = MENU_ROBO_ICON5;
        }else if(objeto->GetNome() == "Walle"){
            caminho = MENU_ROBO_ICON6;
        }else if(objeto->GetNome() == "Gurren"){
            caminho = MENU_ROBO_ICON7;
        }else if(objeto->GetNome() == "ApoloBR"){
            caminho = MENU_ROBO_ICON8;
        }
    }else if(objeto->Is("Piloto")){
        if(objeto->GetNome() == "Joao"){
            caminho = MENU_PEN_ICON1;
        }else if(objeto->GetNome() == "Joana"){
            caminho = MENU_PEN_ICON2;
        }else if(objeto->GetNome() == "Jose"){
            caminho = MENU_PEN_ICON3;
        }else if(objeto->GetNome() == "Josea"){
            caminho = MENU_PEN_ICON4;
        }else if(objeto->GetNome() == "Mario"){
            caminho = MENU_PEN_ICON5;
        }else if(objeto->GetNome() == "Maria"){
            caminho = MENU_PEN_ICON6;
        }else if(objeto->GetNome() == "Batata"){
            caminho = MENU_PEN_ICON7;
        }else if(objeto->GetNome() == "Digglet"){
            caminho = MENU_PEN_ICON8;
   }
    }

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
}
