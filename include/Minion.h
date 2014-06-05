#ifndef MINION_H
#define MINION_H

#include "GameObject.h"
#include "StageState.h"
#include "Sprite.h"
#include "Bullet.h"

class Minion : public GameObject
{
    public:
        Minion (GameObject* minionCenter, float angleOffset = 0);
        //~Minion();
        void Update(float dt);
        void Render(int cameraX, int cameraY);
        bool IsDead();
        void NotifyCollision(GameObject& other);
        bool Is(string type);
        void Shoot(float x, float y);


        /*
        Funções e atributos adicionados
        */
        int GetHitPoint();
        void Inflate(float minInflate, float maxInflate);
        float scale;
        int scaleSign;

    protected:
        /* vazio */
    private:
        GameObject* center;
        Sprite sp;
        float angle;
};
#endif // MINION_H
