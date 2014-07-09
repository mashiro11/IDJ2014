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
    bool Ejetar();
    void Update(float dt);
    bool Embarcar(Ally* alvo);
    void InserePiloto(Piloto* piloto);
    void Morrer();
    void Danificar(float dano);


protected:
    /*vazio*/
private:
    std::vector<Piloto*> pilotoArray;

};

#endif // ROBO_H
