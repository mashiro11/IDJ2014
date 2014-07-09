#ifndef PILOTO_H
#define PILOTO_H
#include "Ally.h"

class Piloto: public Ally{
public:
    Piloto(Character* robo, string nome, Sprite sprite, bool lider, TileMap* mapRef);
    ~Piloto();
    void Render(int cameraX, int cameraY);
    bool Is(string type);
    void Update(float dt);
    void SetX(float x);
    void SetY(float y);
    void Abrir_Menu_Piloto();
    bool Ejetar();
    bool Embarcar(Ally* alvo);
    void StateMachine(float dt);
    void Input();
    Ally* EncontrarRobo();
    void Danificar(float dano);
    void Morrer();

protected:
    /*vazio*/

private:
    Character* robo;
};

#endif // PILOTO_H
