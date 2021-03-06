#ifndef BARRAVIDA_H
#define BARRAVIDA_H
#include "StillAnimation.h"
#include "resources_path.h"

class BarraVida
{
public:
    BarraVida(GameObject* objeto, int vidaMaxima);
    BarraVida(){
        this->objeto = NULL;
    };
    ~BarraVida(){};
    void Update();
    void Render(int cameraX, int cameraY);
    void SetX(float x);
    void SetY(float y);
    void Open(GameObject* alvo, int vidaMaxima);
    bool IsDead();
    void SetVida(int vidaNova);
    int GetVida();
    float GetPorcentagemVida();
    bool IsFull();

protected:
    /*vazio*/
private:
    Rect box;
    Sprite vida;
    Sprite moldura;
    GameObject* objeto;
    int vidaMaxima;
    int vidaAtual;

};

#endif // BARRAVIDA_H
