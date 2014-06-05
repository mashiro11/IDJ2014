#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"
#include "Sprite.h"

#include <string>

class Bullet : public GameObject
{
    public:
        Bullet(float x, float y, float angle, float speed, float maxDistance, Sprite sprite, bool targetsPlayer);
        //~Bullet();
        void Update(float dt);
        void Render(int cameraX, int cameraY);
        bool IsDead();
        void NotifyCollision(GameObject& other);
        bool Is(string type);
        bool targetsPlayer;

        int GetHitPoint();
    protected:
        /* vazio */
    private:
        Sprite sp;
        Point speed;
        float distanceLeft;
};
#endif // BULLET_H
