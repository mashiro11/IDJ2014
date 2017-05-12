#ifndef BARRACOOLDOWN_H
#define BARRACOOLDOWN_H
#include "StillAnimation.h"
#include "Timer.h"
#include "resources_path.h"

class BarraCooldown
{
public:
    BarraCooldown(int cooldown, float x, float y);
    BarraCooldown();
    ~BarraCooldown(){};
    void Update(float dt);
    void Render(int cameraX, int cameraY);
    void SetX(float x);
    void SetY(float y);
    bool IsDead();
    void Open(int cooldown, float x, float y);
    bool IsFull();
    void Esvazia();
    void SetTimer(float time);
protected:

private:
    Timer timer;
    Rect box;
    float tamanho;
    int cooldown;
    Sprite moldura;
    Sprite barra;
};

#endif // BARRACOOLDOWN_H
