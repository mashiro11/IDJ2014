#ifndef BARRAVIDAMENU_H
#define BARRAVIDAMENU_H

#include "StillAnimation.h"

class BarraVidaMenu
{
public:
    BarraVidaMenu(float x, float y);
    BarraVidaMenu(){};
    ~BarraVidaMenu(){};
    void Update(float dt);
    void Render(int cameraX, int cameraY);
    void SetX(float x);
    void SetY(float y);
    void Open(float x, float y);
    bool IsDead();
    void SetVida(float vidaNova);
protected:
    /*vazio*/
private:
    Rect box;
    Sprite vida;
    Sprite moldura;
};

#endif // BARRAVIDAMENU_H
