#include "../include/Rect.h"

Rect::Rect()
{
    //ctor
}

Rect::~Rect()
{
    //dtor
}

bool Rect::IsInside(float coordX, float coordY)
{
    if((coordX > x) && (coordX < x + w) &&
       (coordY > y) && (coordY < y + h) ) return true;
    return false;
}

float Rect::RectCenterX()
{
    return x+w/2;
}

float Rect::RectCenterY()
{
    return y+h/2;
}

void Rect::SetRectCenterX(float centerX)
{
    x = centerX - w/2;
}

void Rect::SetRectCenterY(float centerY)
{
    y = centerY - h/2;
}

float Rect::distancia(Point ponto)//colocar assinatura no .h
{
    Point esseCentro(RectCenterX(), RectCenterY());
    return esseCentro.distancia(ponto);
}

Point Rect::GetCenter() const
{
    return Point( x + w/2, y + h/2);
}
