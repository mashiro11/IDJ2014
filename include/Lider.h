#ifndef LIDER_H
#define LIDER_H
#include "Ally.h"

class Lider : public Ally {
public:
    Lider(float x, float y, float defesa, float ataque, int speed, int distance, float hp, int coolDown, TileMap* mapRef);
    ~Lider();
    static Lider* lider;
    void Render(int cameraX, int cameraY);

private:
    //Sprite sp;
};

#endif // LIDER_H
