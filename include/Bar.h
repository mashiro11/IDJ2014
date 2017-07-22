#ifndef BAR_H
#define BAR_H
#include "StillAnimation.h"
#include "resources_path.h"
#include "Camera.h"
#include "Timer.h"

class Bar: public Component
{
public:
    Bar(int points, GameObject& associated);
    ~Bar(){};
    bool Is(ComponentType comp) const;
    void EarlyUpdate(float dt);
    void Update(float dt);
    void LateUpdate(float dt);
    void Render();
    void SetX(float x);
    void SetY(float y);
    void SetPoints(int points);
    int GetPoints();
    float GetPercentPoints();
    bool IsFull();
    void SetRefilAuto(int refilPace, int time = 1);
    void SetPosition(float x, float y);
    //void Open(GameObject* alvo, int vidaMaxima);
//    bool IsDead();
//    void SetVida(int vidaNova);
//    int GetVida();
//    float GetPorcentagemVida();
//    bool IsFull();

protected:

private:
    GameObject& associated;
    Rect box;
    Sprite fluid;
    Sprite frame;
    int maxPoints;
    int currPoints;
    bool refilAuto;
    int refilPace;
    Timer timer;
};

#endif // BAR_H
