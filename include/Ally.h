#ifndef ALLY_H
#define ALLY_H

#include <queue>
#include <vector>
#include <list>

#include "GameObject.h"
#include "Sprite.h"
#include "StillAnimation.h"
#include "BarraVida.h"
#include "TileMap.h"
#include "Timer.h"


enum AllyState{ATACANDO, DEFENDENDO, INATIVO, MOVENDO, AGUARDANDO_ANDAR, AGUARDANDO_EMBARCAR, AGUARDANDO_ITEM, REPOUSO};
enum AllyPosition{FRONT, BACK, LEFT, RIGHT};

using std::vector;
using std::list;
using std::queue;

class Ally:public GameObject{
public:
    Ally();
    ~Ally(){};
    void Update(float dt) = 0;
    virtual void Render(int cameraX, int cameraY) = 0;
    Point MapPosition();
    float TileCenter(int coord);
    float MapPositionToPixelPosition(int coord);
    int PixelPositionToMapPosition(int pixels);
    bool IsDead();
    void NotifyCollision(GameObject& other);

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
    void MakePath(int line, int row);
    bool ValidPath();
    void OrientarSprite();

protected:
    void UpdateAlly(float dt);
    AllyState allyState;
    AllyPosition allyPosition;
    int tileSize;
    Sprite sp;
    //velocidade de movimentacao (ataque, andar, etc)
    int speed;
    Point destiny;
    vector<StillAnimation> buttonArray;
    list<int> closeEnemies;
    //velocidade que carrega a barra
    int coolDown;
    //distancia ate onde pode andar
    int distance;
    float ataque;
    float defesa;
    //alcance de ataque
    int range;
    bool menuAberto;
    BarraVida vida;
    queue<Point> path;
    TileMap *mapReference;
    Timer timer;


private:
};

#endif // ALLY_H
