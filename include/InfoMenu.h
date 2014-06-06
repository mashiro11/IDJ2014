#ifndef INFOMENU_H
#define INFOMENU_H
#include "Sprite.h"
#include "StillAnimation.h"
#include "Timer.h"
#include "Text.h"

class InfoMenu:public GameObject{
public:
    InfoMenu(float x, float y, GameObject* objeto);
    ~InfoMenu(){};
    void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    bool Is(string type);
    void NotifyCollision(GameObject &other);
    int GetHitPoint();

    void InsereBotao(GameObject* objeto);

private:
    Timer cronometro;
    Sprite sp;
    std::vector<StillAnimation> buttonArray;
    std::vector<GameObject*> objectArray;
    Text texto;
};

#endif // INFOMENU_H
