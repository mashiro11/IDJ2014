#ifndef PILOTO_H
#define PILOTO_H
#include "Ally.h"

class Piloto: public Ally{
public:
    Piloto(GameObject* robo, string nome, Sprite sprite, bool lider, TileMap* mapRef);
    ~Piloto();
    void Render(int cameraX, int cameraY);
    bool Is(string type);
    void Embarcar(GameObject* alvo);
    void Update(float dt);
    void SetX(float x);
    void SetY(float y);
    void Abrir_Menu();
    void Ejetar();

protected:
    /*vazio*/

private:
    GameObject* robo;
    BarraVida vida;
};

#endif // PILOTO_H
