#ifndef ALLY_H
#define ALLY_H

#include <queue>
#include <vector>
#include <list>
#include <sstream>

#include "GameObject.h"
#include "Sprite.h"
#include "StillAnimation.h"
#include "BarraVida.h"
#include "TileMap.h"
#include "Timer.h"
#include "Character.h"


enum AllyState{ATACANDO, DEFENDENDO, INATIVO, MOVENDO, AGUARDANDO_ANDAR, AGUARDANDO_EMBARCAR, AGUARDANDO_ITEM, REPOUSO};

using std::vector;
using std::list;
using std::queue;
using std::stringstream;

class Ally:  public Character //public GameObject
{
public:
    Ally();
    ~Ally(){};
    void Update(float dt) = 0;
    virtual void Render(int cameraX, int cameraY) = 0;

    void StateMachine();
    void Input();
    bool IsDead();
    void NotifyCollision(GameObject& other);

    void SetStatus(int vidaMaxima, float ataque, int renge, float defesa, int speed, int distance, int coolDown);
    void Danificar(float dano);
    void Defender();
    void Andar();
    void Parar();
    void Abrir_Menu();
    void Fechar_Menu();
    void Usar_Item();
    void Alocar_Item();
    void Especial();
    void Atacar();
    virtual void Ejetar() = 0;
    //void MakePath(int line, int row);
    void MakePath();
    void MakeRangeArea();
    void OrientarSprite();
    bool IsLider();
    bool ValidPath();

protected:
    void UpdateAlly(float dt);
    bool lider;
    AllyState allyState;
    CharacterPosition allyPosition;
    string nome;
    int tileSize;
    Sprite sp;
    //velocidade de movimentacao (ataque, andar, etc)
    vector<StillAnimation> buttonArray;
    //list<int> closeEnemies;
    //velocidade que carrega a barra
    int coolDown;
    //distancia ate onde pode andar
    int distance;
    //alcance de ataque
    bool menuAberto;
    BarraVida vida;
    queue<Point> path;
    //TileMap *mapReference;
    Timer timer;
private:
};

#endif // ALLY_H
