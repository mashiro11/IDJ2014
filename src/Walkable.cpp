#include "Walkable.h"

Walkable::Walkable(GameObject& associated):
    associated(associated)
{
    //ctor
}

void Walkable::Update(float dt){
    if(controlable){
        if(InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT) && InputManager::GetInstance().IsMouseInside(associated.box)){
            selected = true;
        }
        if(selected && InputManager::GetInstance().MouseRelease(SDL_BUTTON_LEFT)){
           if(InputManager::GetInstance().IsMouseInside(associated.box)){
                cout << "Apenas selecionado" << endl;
                selected = false;
           }else{
                cout << "Deveria andar" << endl;
                selected = false;
           }
        }
    }
}

Walkable::~Walkable()
{
    //dtor
}

bool Walkable::Is(ComponentType type) const{
    return type == WALKABLE;
}

void Walkable::LateUpdate(float dt){}

void Walkable::EarlyUpdate(float dt){}
