#ifndef CHARACTER_H
#define CHARACTER_H

#include <queue>
#include <vector>
#include <list>
#include <stack>
#include <unordered_map>
#include <sstream>

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
using std::stringstream;
using std::stack;

enum CharacterPosition{FRONT, BACK, LEFT, RIGHT};
enum CharState{ATACANDO, DEFENDENDO, INATIVO, MOVENDO,
               AGUARDANDO_ANDAR, AGUARDANDO_EMBARCAR,
               AGUARDANDO_ITEM, REPOUSO, EMBARCAR, ESPECIAL, AGUARDANDO_ALVO};

typedef struct nodo{
    int indice;
    Point point;
}NODO;

class Character: public GameObject{

        public:
            //Character();
            ~Character();
            virtual void Update(float dt) = 0;
            virtual void Render(int cameraX, int cameraY);

            virtual bool IsDead() = 0;
            virtual bool Is(string type) = 0;
            virtual void NotifyCollision(GameObject& other) = 0;

            void MakeRangeArea(int tileNumber = 1);
            void RangeAreaUpdate(int x, int y);
            void CloseEnemiesUpdate();
            void IdentifyOpponent();
            void GraphDepht(int x, int y, int depth);
            void Danificar(float dano);
            void Defender();
            void Andar();
            void Parar();
            virtual void Especial() = 0;
            void Atacar();
            void OrientarSprite();
            string GetNome();
            void Pathfinder(int goalX, int goalY);
            bool Centered();
            int GetCurrentX();
            int GetCurrentY();


        protected:
            Sprite sp;
            CharacterPosition charPosition;
            CharState charState;
            Point currentPosition;

            unordered_map<GameObject*, Point> closeEnemies;
            TileMap *mapReference;
            vector<Point> rangeMap;//guardar a área de ataque
            queue<Point> path; //caminho que irá andar
            vector<NODO> processed;
            Timer timer;
            int tileNumber;

            /**
                STATUS
            **/
            string nome;
            //velocidade de movimentacao (ataque, andar, etc)
            int speed;//velocidade de movimentação no mapa
            float ataque;//poder de ataque
            float defesa;//poder de defesa
            int range;//alcance de ataque
            int coolDown;
            int atackCoolDown;//tempo de espera para novo movimento
            int distance;

        private:
};
#endif // CHARACTER_H
