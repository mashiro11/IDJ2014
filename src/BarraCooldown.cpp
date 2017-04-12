#include "../include/BarraCooldown.h"

BarraCooldown::BarraCooldown()
{
    tamanho = 0;
}

BarraCooldown::BarraCooldown(int cooldown, float x, float y)
{
    barra.Open("img/barraCooldown.png");
    moldura.Open("img/barraCooldownMoldura.png");
    tamanho = 0;
    this->cooldown = cooldown;
    box.w = barra.GetWidth();
    box.h = barra.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
}

void BarraCooldown::Open(int cooldown, float x, float y)
{
    barra.Open("img/barraCooldown.png");
    moldura.Open("img/barraCooldownMoldura.png");

    tamanho = 0;
    this->cooldown = cooldown;
    box.w = barra.GetWidth();
    box.h = barra.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
}

void BarraCooldown::Update(float dt)
{
    if(timer.Get() < cooldown){
        timer.Update(dt);
    }
    if(timer.Get() >= cooldown){
        timer.Set(cooldown);
    }

    barra.SetClip(0, 0, box.w*timer.Get()/cooldown, box.h);
}

void BarraCooldown::Render(int cameraX, int cameraY)
{
    barra.Render(box.x - cameraX, box.y - cameraY + 70);
    moldura.Render(box.x - cameraX, box.y - cameraY + 70);
}

bool BarraCooldown::IsDead()
{
    return false;
}

void BarraCooldown::SetX(float x)
{
    box.SetRectCenterX(x);
}

void BarraCooldown::SetY(float y)
{
    box.SetRectCenterY(y);
}

bool BarraCooldown::IsFull()
{
    if(timer.Get()/cooldown == 1){
        return true;
    }
    return false;
}

void BarraCooldown::Esvazia()
{
    timer.Restart();
}

void BarraCooldown::SetTimer(float time)
{
    timer.Set(time);
}

