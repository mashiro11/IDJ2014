#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
#include "Sprite.h"
#include "Character.h"

//enum EnemyState{MOVENDO, ATACANDO, AGUARDANDO};

class Enemy: public Character
{
        public:
            Enemy(float x, float y, TileMap* mapRef);
            ~Enemy();
            void NotifyCollision(GameObject &other);
            bool Is(string type);
            bool IsDead();
            //void Render(int cameraX, int cameraY);
            void Update(float dt);
            void Especial(){};

        private:
            //EnemyState enemyState;
            Point speed;
            Point destiny;
            float vida;
            int tileSize;
            float ataque;
            float defesa;
};

#endif // ENEMY_H
