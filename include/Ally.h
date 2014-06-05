#ifndef ALLY_H
#define ALLY_H

#include <queue>
#include <vector>
#include <list>

#include "GameObject.h"
#include "Sprite.h"
#include "StillAnimation.h"
#include "TileMap.h"
#include "Timer.h"

enum AllyState{ATACANDO, DEFENDENDO, INATIVO, MOVENDO, AGUARDANDO, REPOUSO};
enum AllyPosition{FRONT, BACK, LEFT, RIGHT};

using std::vector;
using std::list;
using std::queue;

class Ally : public GameObject{
public:
    //Ally(float x, float y, float defense, float attack, int speed, int distance, float hp, int coolDown, TileMap* mapRef);
    Ally(){};
    ~Ally(){};
    void Update(float dt);
    virtual void Render(int cameraX, int cameraY) = 0;
    Point MapPosition();
    float TileCenter(int coord);
    void MapPositionToPixelPosition(int line, int row);
    int PixelPositionToMapPosition(int pixels);
    bool IsDead();
    void NotifyCollision(GameObject& other);
    bool Is(string type);
    Sprite* VerificaVida();

    int GetHitPoint();
    void Danificar(float dano);
    void Defender();
    void Andar();
    void OrientarSprite();
    void MakePath(int line, int row);
    void Parar();
    void Abrir_Menu();
    void Fechar_Menu();
    void Embarcar();
    void Usar_Item();
    void Alocar_Item();
    void Especial();
    void Atacar();
    void Ejetar();

protected:
    AllyState allyState;
    AllyPosition allyPosition;
    Sprite sp;
    queue<Point> path;
    vector<StillAnimation> buttonArray;
    list<int> closeEnemies;
    int coolDown;
    int distance;
    int speed;
    float hp;
    float ataque;
    float defesa;
    bool menuAberto;
    TileMap *mapReference;
    Timer timer;
private:
};

#endif // ALLY_H
