#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
/*
    STD classes
*/
#include <string>
#include <vector>
#include <memory>

/*
    Game classes
*/
#include "../include/Rect.h"
#include "Sprite.h"
#include "Component.h"

using std::string;
using std::vector;
using std::shared_ptr;

class GameObject
{
    public:
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void NotifyCollision(GameObject& other){};
        //bool Is(string type);
        Rect box;
        float rotation;
        void AddComponent(Component& comp);
        //Sprite sp;

    protected:
    private:
        vector<Component*> components;

};

#endif // GAMEOBJECT_H
