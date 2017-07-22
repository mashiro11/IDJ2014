#include "../include/State.h"

State::State()
{
    requestDelete = false;
    requestQuit = false;
}

State::~State()
{
    //dtor
}

void State::AddObject(GameObject* ptr)
{
    objectArray.emplace_back(ptr);
}

bool State::RequestedDelete()
{
    return requestDelete;
}

bool State::RequestedQuit()
{
    return requestQuit;
}

void State::UpdateArray(float dt)
{
    Camera::Update(Game::GetInstance().GetDeltaTime());//pode ser aqui ou lá fora, após chamada do input
    //Camera::Unfollow();//provisório//pode ser aqui ou lá fora, após chamada do input
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[ i ]->Update( Game::GetInstance().GetDeltaTime() );
        if(objectArray[ i ]->IsDead() == true){
                objectArray.erase( objectArray.begin() + i );
        }
    }
    for(int i = 0; i < objectArray.size(); i++){
        for(int j = i + 1; j < objectArray.size(); j++ ){
                if(objectArray[i]->Is("StillAnimation") == false && objectArray[j]->Is("StillAnimation") == false)
                if(Collision::IsColliding(objectArray[i]->box,
                                          objectArray[j]->box,
                                          objectArray[i]->rotation,
                                          objectArray[j]->rotation
                                          ) == true
                                                    ){
                                                       objectArray[i]->NotifyCollision(*objectArray[j]);
                                                       objectArray[j]->NotifyCollision(*objectArray[i]);
                                                    }
        }
    }
    if(SDL_QuitRequested() == true){
        requestQuit = true;
    }
}
