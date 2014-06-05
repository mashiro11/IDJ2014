#ifndef PENGUINS_H
#define PENGUINS_H

#include "GameObject.h"
#include "Sprite.h"
#include "Bullet.h"
#include "StillAnimation.h"
#include "Sound.h"


class Penguins : public GameObject
{
    public:
        Penguins(float x, float y);
        ~Penguins();
        void Update (float dt);
        void Render (int cameraX, int cameraY);
        bool IsDead ();
        void NotifyCollision(GameObject& other);
        bool Is(string type);
        void Shoot ();
        static Penguins* player;

        int GetHitPoint();

    protected:
        /* vazio */
    private:
        Sprite bodySp;
        Sprite cannonSp;
        Point speed;
        float linearSpeed;
        float cannonAngle;
        int hp;
};

#endif // PENGUINS_H
