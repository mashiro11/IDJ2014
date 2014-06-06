#ifndef ALLY_H
#define ALLY_H

#include <vector>
#include <list>

#include "GameObject.h"
#include "Sprite.h"
#include "StillAnimation.h"
#include "BarraVida.h"


enum AllyState{ATACANDO, DEFENDENDO, INATIVO, MOVENDO, AGUARDANDO_ANDAR, AGUARDANDO_EMBARCAR, REPOUSO};
enum AllyPosition{FRENTE, COSTAS, DIREITA, ESQUERDA};

using std::vector;
using std::list;

class Ally:public GameObject{
public:
    Ally();
    ~Ally(){};
    void Update(float dt) = 0;
    virtual void Render(int cameraX, int cameraY) = 0;
    Point MapPosition(int tileWidth, int tileHeight);
    void MapPositionToPixelPosition(int line, int row, int tileSize);
    int PixelPositionToMapPosition(int pixels, int tileSize);
    void SetDestiny(int line, int row);
    bool IsDead();
    void NotifyCollision(GameObject& other);

    void Danificar(float dano);
    void Defender();
    void Andar();
    void Parar();
    virtual void Abrir_Menu() = 0;
    void Fechar_Menu();
    void Usar_Item();
    void Alocar_Item();
    void Especial();
    void Atacar();
    virtual void Ejetar() = 0;

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


private:
};

#endif // ALLY_H
