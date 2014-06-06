#ifndef LIDER_H
#define LIDER_H
#include "Ally.h"

class Lider:public Ally{
public:
    Lider(float x, float y, float defesa, float ataque, int speed, int distance, float hp,
          int coolDown, TileMap* mapRef, int range);
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
