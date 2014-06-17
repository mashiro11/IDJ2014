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
#include "Enemy.h"


using std::vector;
using std::list;
using std::queue;
using std::stringstream;


class Ally:public Character{
public:

    //Ally();
    ~Ally(){};
    void Update(float dt) = 0;
    virtual void Render(int cameraX, int cameraY) = 0;

    void StateMachine(float dt);
    void Input();
    bool IsDead();
    void NotifyCollision(GameObject& other);
    bool Is(string type);


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
    void MakePath();
    void OrientarSprite();
    bool IsLider();
    bool ValidPath();
    string GetNome();

protected:
    void UpdateAlly(float dt);
    bool lider;
    //CharState allyState;
    CharacterPosition allyPosition;
    vector<StillAnimation> buttonArray;


    //alcance de ataque
    bool menuAberto;

    queue<Point> path;
    Timer timer;


    /**
        STATUS
    **/
    //herança de Character
    //int speed;//velocidade de movimentação no mapa
    //float ataque;//poder de ataque
    //float defesa;//poder de defesa
    //int range;//alcance de ataque
    BarraVida vida;
    int coolDown;//tempo de espera para novo movimento
    int distance;//quantas células do grid pode andar
    //alcance de ataque
private:
};

#endif // ALLY_H
