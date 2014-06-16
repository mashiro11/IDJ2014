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
#include "Character.h"

enum AllyState{ATACANDO, DEFENDENDO, INATIVO, MOVENDO, AGUARDANDO_ANDAR, AGUARDANDO_EMBARCAR, AGUARDANDO_ITEM, REPOUSO};

using std::vector;
using std::list;
using std::queue;
using std::stringstream;

class Ally:public Character{
public:
    Ally();
    ~Ally(){};
    void Update(float dt) = 0;
    virtual void Render(int cameraX, int cameraY) = 0;

    void StateMachine();
    void Input();
    bool IsDead();
    void NotifyCollision(GameObject& other);

    Point MapPosition();
    float TileCenter(int coord);
    float MapPositionToPixelPosition(int coord);
    int PixelPositionToMapPosition(int pixels);

    bool AreaRespiro();
    bool AreaMapa();

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
    string GetNome();

protected:
    void UpdateAlly(float dt);

    AllyState allyState;
    CharacterPosition allyPosition;

    Sprite sp;
    BarraVida vida;
    Timer timer;
    //TileMap *mapReference;

    //velocidade que carrega a barra
    int coolDown;
    //distancia ate onde pode andar
    int distance;
    bool lider;
    bool menuAberto;
    string nome;
    int tileSize;

    //list<int> closeEnemies;
    queue<Point> path;
    vector<StillAnimation> buttonArray;


private:
};

#endif // ALLY_H
