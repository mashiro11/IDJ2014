#ifndef PILOTO_H
#define PILOTO_H
#include "Ally.h"

class Piloto: public Ally{
public:
    Piloto(Character* robo, string nome, Sprite sprite, bool lider, TileMap* mapRef);
    ~Piloto();
    void Render(int cameraX, int cameraY);
    bool Is(string type);
    void Embarcar(Character* alvo);
    void Update(float dt);
    void SetX(float x);
    void SetY(float y);
    void Abrir_Menu_Piloto();
    void Ejetar();
    void StateMachine(float dt);
    void Input();
    void Encontrar_Robo(Character* alvo);

protected:
    /*vazio*/

private:
    Character* robo;
};

#endif // PILOTO_H
