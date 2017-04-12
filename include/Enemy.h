#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.h"
#include "Sprite.h"
#include "Character.h"
#include "Ally.h"
#include "StillAnimation.h"

//enum EnemyState{MOVENDO, ATACANDO, AGUARDANDO};
class Enemy: public Character
{
        public:
            Enemy(float x, float y, TileMap* mapRef, string nome = "");
            ~Enemy();
            void SetStatus(int vidaMaxima, float ataque, int range, float defesa, int speed, int coolDown);
            void NotifyCollision(GameObject &other);
            bool Is(string type);
            bool IsDead();
            //void Render(int cameraX, int cameraY);
            void Update(float dt);
            void Input();
            void Especial(){};
            void StateMachine(float dt);

            void Andar();
            void MakePath();
            bool ValidPath();
            void Atacar();
            void Danificar(float dano);
            void OrientarSprite();
        private:
            int vida;
            int coolDown;

            //essa linha sera apagada
            bool inputTest;
};

#endif // ENEMY_H
