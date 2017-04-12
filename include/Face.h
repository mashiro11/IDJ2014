#ifndef FACE_H
#define FACE_H

#include "../include/GameObject.h"
#include "../include/Sprite.h"
#include <math.h>

//#include "Game.h"//StageState
#include "Camera.h"


const int FACE_HP = 40;

class Face : public GameObject
{
    public:
        Face(float mouseX, float mouseY);
        ~Face();
        void Damage(int damage);
        void Update(float dt);
        void Render(int cameraX, int cameraY);//linha alterada
        bool IsDead();
        void NotifyCollision(GameObject& other);
        bool Is(string type);


        /*
        Funções e atributos adicionados
        */
        int GetHitPoint();
    protected:
        /* vazio */
    private:
        int hitpoints = FACE_HP;
        Sprite sp;
};

#endif // FACE_H
