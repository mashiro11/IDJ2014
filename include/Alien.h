#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <vector>
#include <limits>

#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Minion.h"
#include "Timer.h"
#include "Penguins.h"


using std::queue;
using std::vector;

class Minion;
class Alien : public GameObject
{
    public:
        Alien(float x, float y, int nMinions);
        ~Alien();
        void Update(float dt);
        void Render(int cameraX, int cameraY);
        bool IsDead();
        void NotifyCollision(GameObject& other);
        bool Is(string type);

        /*
        Funções e atributos adicionados
        */
        int GetHitPoint();
        void Inflate(float minInflate, float maxInflate);
        float scale;
        int scaleSign;
        static int alienCount;
        Timer shootTimer;

    protected:
        /* vazio */
    private:
        Sprite sp;
        Point speed;
        int hp;
        int shootCounter; //inserido
        queue<Point> taskQueue;
        vector<Minion> minionArray;
        enum AlienState { MOVING, RESTING };
        AlienState alienState;
        Timer shootCooldown;
};

#endif // ALIEN_H
