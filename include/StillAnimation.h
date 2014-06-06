#ifndef STILLANIMATION_H
#define STILLANIMATION_H

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Sound.h"

class StillAnimation : public GameObject
{
    public:
        StillAnimation (float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends);
        //~StillAnimation();
        void Update (float dt);
        void Render (int cameraX, int cameraY);
        bool IsDead ();
        void NotifyCollision (GameObject& other){};
        bool Is (string type);
        void SetX(float x);
        void SetY(float y);
        int GetHitPoint(){ return endTimer.Get(); };

    protected:
        /* vazio */
    private:
        Timer endTimer;
        float timeLimit;
        bool oneTimeOnly;
        Sprite sp;
};

#endif // ANIMATION_H
