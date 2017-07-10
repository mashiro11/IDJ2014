#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
/*
    STD classes
*/
#include <string>

/*
    Game classes
*/
#include "../include/Rect.h"
#include "Sprite.h"

using std::string;

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool IsDead() = 0;
        virtual int GetHitPoint(){return vidaAtual;};
        virtual int GetLife(){return vidaMaxima;};
        virtual void NotifyCollision(GameObject& other) = 0;
        virtual bool Is(string type) = 0;
        virtual string GetNome(){};
        virtual void Morrer(){};
        virtual bool IsLeader(){};

        Rect box;
        float rotation;

    protected:
        int vidaAtual;
        int vidaMaxima;
    private:
        Sprite sp;
        /* vazio */
};

#endif // GAMEOBJECT_H
