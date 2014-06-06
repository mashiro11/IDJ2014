#ifndef BARRAVIDA_H
#define BARRAVIDA_H
#include "StillAnimation.h"

class BarraVida
{
public:
    BarraVida(GameObject* objeto);
    BarraVida(){
        this->objeto = NULL;
    };
    ~BarraVida(){};
    void Update();
    void Render(int cameraX, int cameraY);
    void SetX(float x);
    void SetY(float y);
    void Open(GameObject* alvo);
protected:
    /*vazio*/
private:
    Rect box;
    Sprite vida;
    Sprite moldura;
    GameObject* objeto;

};

#endif // BARRAVIDA_H
