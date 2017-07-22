#include "../include/Robo.h"

#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Robo::Robo(float x, float y, string nome):
    sp(ROBO_SP1, x, y, ROBO_SHEET_FRAMES, ROBO_SHEET_LINES, ROBO_SHEET_FRAME_TIME)
{
    DEBUG_PRINT("Robo::Robo()-inicio");

    this->nome = nome;

    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.x = x;
    box.y = y;


    //Barra de vida
    Bar* barraVida = new Bar(200, BARRA_VIDA_MOLDURA, BARRA_VIDA, *this);
    barraVida->SetPosition(0,0);
    components.push_back(barraVida);

    //barra de cooldown
    Bar *coolDownBar = new Bar(10, BARRA_COOLDDOWN_MOLDURA, BARRA_COOLDOWN, *this);
    coolDownBar->SetY(10);
    coolDownBar->SetRefilAuto(10);
    coolDownBar->SetPoints(0);
    coolDownBar->SetPosition(0,10);
    DEBUG_PRINT(coolDownBar->GetY() << "x" << coolDownBar->GetY());
    components.push_back(coolDownBar);

    DEBUG_PRINT("Robo::Robo()-fim");
}

Robo::~Robo(){
}

void Robo::Update(float dt){
    //DEBUG_PRINT("Robo::Update()-inicio");
    sp.Update(dt);
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Update(dt);
    }
    //DEBUG_PRINT("Robo::Update()-fim");
}

void Robo::Render(){
    //DEBUG_PRINT("Robo::Render()-inicio");
    sp.Render();
    for(unsigned int i = 0; i < components.size(); i++){
        components[i]->Render();
    }
    //DEBUG_PRINT("Robo::Render()-fim");
}

bool Robo::Is(string type){
    if(type == "Robo"){
        return true;
    }
    return false;
}

bool Robo::IsDead(){
    return false;
}

void Robo::NotifyCollision(GameObject& other){
}

#ifdef DEBUG
    #undef DEBUG
#endif
