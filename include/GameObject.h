#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Rect.h>
#include <string>

using std::string;

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        virtual void Update(float dt) = 0;
        virtual void Render(int cameraX, int cameraY) = 0;//linha alterada: tratando de face e alien
        virtual bool IsDead() = 0;
        virtual int GetHitPoint(){return vidaAtual;};
        virtual int GetLife(){return vidaMaxima;};
        virtual void NotifyCollision(GameObject& other) = 0;
        virtual bool Is(string type) = 0;
        Rect box;
        float rotation;

    protected:
        int vidaAtual;
        int vidaMaxima;
    private:
        /* vazio */
};

#endif // GAMEOBJECT_H
