#include "../include/GameObject.h"

//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

GameObject::GameObject()
{
    //ctor
}

GameObject::~GameObject()
{
    //dtor
}

void GameObject::Update(float dt){
    DEBUG_PRINT("GameObject::Update()-inicio");
    for(auto it = components.begin(); it != components.end(); it++){
        (*it)->Update(dt);
    }
    DEBUG_PRINT("GameObject::Update()-fim");
}

void GameObject::Render(){
    DEBUG_PRINT("GameObject::Render()-inicio");
    for(auto it = components.begin(); it != components.end(); it++){
        (*it)->Render();
    }
    DEBUG_PRINT("GameObject::Render()-fim");
}

void GameObject::AddComponent(Component& comp){
    components.push_back(&comp);
}

bool GameObject::IsDead(){
    return false;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
