#ifndef INFOMENU_H
#define INFOMENU_H
#include "Sprite.h"
#include "StillAnimation.h"
#include "Timer.h"
#include "Text.h"
#include "BarraCooldown.h"
#include "Piloto.h"
#include "BarraVidaMenu.h"

#define INFO_MENU_FILE "img/infoMenu.png"
#define INFO_MENU_FONT "images/font/Call me maybe.ttf"

class InfoMenu{
public:
    InfoMenu(float x, float y);
    ~InfoMenu(){};
    void Update(float dt);
    void Render(int cameraX, int cameraY);
    bool IsDead();
    void InsereBotao(Ally* objeto);
    void NotificarMorte(string nome);
    void Reordenar();
    void RefazBotao(Ally* objeto, int index);
    void GerenciaCronometro(float dt);

private:
    Rect box;
    Sprite sp;
    int minutos;
    Timer cronometro;

    std::vector<StillAnimation> buttonArray;
    std::vector<BarraVidaMenu> vidaArray;
    std::vector<Ally*> objectArray;
    Text texto;
    int offSet;
    bool showDebug;
};

#endif // INFOMENU_H
