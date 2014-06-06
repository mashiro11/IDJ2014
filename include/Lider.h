#ifndef LIDER_H
#define LIDER_H
#include "Ally.h"

class Lider:public Ally{
public:
    Lider(float tileSize, float x, float y, float defesa, float ataque, float hp, int coolDown,
          int range, int distance, int speed);
    ~Lider();
    static Lider* lider;
    void Ejetar();
    void Render(int cameraX, int cameraY);
    bool Is(string type);
    void Update(float dt);
    void Abrir_Menu();

private:
    BarraVida vida;
};


#endif // LIDER_H
