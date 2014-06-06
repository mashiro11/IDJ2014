#ifndef ENEMY_H
#define ENEMY_H
#include "GameObject.h"
#include "Sprite.h"

enum EnemyState{MOVENDO, ATACANDO, AGUARDANDO};
enum EnemyPosition{FRENTE, COSTAS, DIREITA, ESQUERDA};
class Enemy:public GameObject{
public:
    Enemy(float tileSize, float x, float y, float defesa, float ataque, float vida);
    ~Enemy();
    void NotifyCollision(GameObject &other);
    bool Is(string type);
    bool IsDead();
    void Render(int cameraX, int cameraY);
    void Update(float dt);

private:
    EnemyState enemyState;
    EnemyPosition enemyPosition;
    Sprite sp;
    Point speed;
    Point destiny;
    float vida;
    int tileSize;
    float ataque;
    float defesa;
};

#endif // ENEMY_H
