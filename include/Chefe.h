#ifndef CHEFE_H
#define CHEFE_H
#include "Ally.h"
#include "TileMap.h"
#include "resources_path.h"

class Chefe:public Character{
public:
    Chefe(float x, float y, TileMap* mapRef, string nome);
    ~Chefe();
    void Update(float dt);
    //void Render(int cameraX, int cameraY);
    void SetStatus(int vidaMaxima, float ataque, int range, float defesa, int speed, int coolDown);
    bool Is(string type);
    bool IsDead();
    void NotifyCollision(GameObject &other);
    void Input();
    void Especial();
    void AtaqueRanged();
    void StateMachine(float dt);
    void Atacar();
    void Danificar(float dano);
    void CalcularDistancia();
    static int chefeMorto;

protected:

private:
    int vida;
    int coolDown;
    int atacando;
    Timer ataqueTime;
    Timer especialTime;
    Timer rangedTime;
    std::vector<int> distancias;

};

#endif // CHEFE_H
