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
        virtual int GetHitPoint() = 0;
        virtual void NotifyCollision(GameObject& other) = 0;
        virtual bool Is(string type) = 0;
        Rect box;
        float rotation;
    protected:
        /* vazio */
    private:
        /* vazio */
};

#endif // GAMEOBJECT_H
