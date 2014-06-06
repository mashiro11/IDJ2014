#ifndef INFOMENU_H
#define INFOMENU_H
#include "Sprite.h"
#include "StillAnimation.h"
#include "Timer.h"
#include "Text.h"
#include "BarraVida.h"

class InfoMenu:public GameObject{
public:
    InfoMenu(float x, float y);
    ~InfoMenu(){};
    void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    bool Is(string type);
    void NotifyCollision(GameObject &other);
    int GetHitPoint(){};
    int GetLife(){};
    void InsereBotao(GameObject* objeto);

private:
    int minutos;
    Timer cronometro;
    Sprite sp;
    //vai virar array de barra de vida
    std::vector<StillAnimation> buttonArray;
    std::vector<BarraVida> vidaArray;
    std::vector<GameObject*> objectArray;
    Text texto;
    int offSet;
};

#endif // INFOMENU_H
