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
        virtual ~GameObject();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool IsDead() = 0;
        virtual void NotifyCollision(GameObject& other) = 0;
        virtual bool Is(string type) = 0;
        Rect box;
        float rotation;

    protected:
        vector<Component*> components;
    private:

};

#endif // GAMEOBJECT_H
