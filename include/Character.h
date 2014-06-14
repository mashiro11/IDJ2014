#ifndef CHARACTER_H
#define CHARACTER_H


#include <queue>
#include <vector>
#include <list>
#include <unordered_map>

#include "GameObject.h"
#include "Sprite.h"
#include "StillAnimation.h"
#include "BarraVida.h"
#include "TileMap.h"
#include "Timer.h"

using std::vector;
using std::list;
using std::queue;
using std::string;
using std::unordered_map;

enum CharacterPosition{FRONT, BACK, LEFT, RIGHT};

class Character: public GameObject{

        public:
            Character();
            ~Character();
            virtual void Update(float dt) = 0;
            virtual void Render(int cameraX, int cameraY);

            virtual bool IsDead() = 0;
            virtual void NotifyCollision(GameObject& other) = 0;

            void Danificar(float dano);
            void Defender();
            void Andar();
            void Parar();
            virtual void Especial() = 0;
            void Atacar();
            void OrientarSprite();

        protected:
            Sprite sp;
            CharacterPosition charPosition;
            //Point currentPosition;

            unordered_map<string, GameObject*> closeEnemies;
            TileMap *mapReference;
            Timer timer;

            /**
                STATUS
            **/
            //velocidade de movimentacao (ataque, andar, etc)
            int speed;//velocidade de movimentação no mapa
            float ataque;//poder de ataque
            float defesa;//poder de defesa
            int range;//alcance de ataque

        private:
};
#endif // CHARACTER_H
