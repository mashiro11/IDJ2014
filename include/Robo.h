#ifndef ROBO_H
#define ROBO_H
#include "Ally.h"
#include "Piloto.h"
#include <iostream>

class Robo: public Ally{
public:
    Robo(float x, float y, TileMap* mapRef, bool lider, Sprite sprite, string nome);
    ~Robo();
    void Render(int cameraX, int cameraY);
    bool Is(string type);
    void Ejetar();
    void Update(float dt);
    void InserePiloto(Piloto* piloto);

protected:
    /*vazio*/
private:
    std::vector<Piloto*> pilotoArray;
    BarraVida vida;

};

#endif // ROBO_H
