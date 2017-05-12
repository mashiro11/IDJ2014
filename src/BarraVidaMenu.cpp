#include "../include/BarraVidaMenu.h"

BarraVidaMenu::BarraVidaMenu(float x, float y)
{
    vida.Open(BARRA_VIDA_MENU);
    moldura.Open(BARRA_VIDA_MENU_MOLDURA);

    box.w = vida.GetWidth();
    box.h = vida.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
}

void BarraVidaMenu::Open(float x, float y)
{
    vida.Open(BARRA_VIDA_MENU);
    moldura.Open(BARRA_VIDA_MENU_MOLDURA);

    box.w = vida.GetWidth();
    box.h = vida.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
    }

void BarraVidaMenu::Update(float dt)
{


}

void BarraVidaMenu::SetVida(float vidaNova)
{
    if (vidaNova < 0){
        vidaNova = 0;
    }
    vida.SetClip(0, 0, box.w*vidaNova/100, box.h);
}

void BarraVidaMenu::Render(int cameraX, int cameraY)
{
    vida.Render(box.x - cameraX, box.y - cameraY);
    moldura.Render(box.x - cameraX, box.y - cameraY);
}

void BarraVidaMenu::SetX(float x)
{
    box.SetRectCenterX(x);
}

void BarraVidaMenu::SetY(float y)
{
    box.SetRectCenterY(y);
}
