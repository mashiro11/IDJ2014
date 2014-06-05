#ifndef RECT_H
#define RECT_H

#include "Point.h"
/*
    Classe representando um Retângulo,
    com vértice superior esquerdo em x,y,
    largura w (width) e altura h (height)
*/
class Rect
{
    public:
        Rect();
        Rect(float coordX, float coordY){x = coordX; y = coordY;};
        float x, y, w, h; //posição x, y cartesiana na tela, w e h representam width e height, respectivamente
        ~Rect();
        void mover(Point p){x = p.x; y = p.y;};
        bool IsInside(float coordX, float coordY);

        float RectCenterX();
        float RectCenterY();
        Point GetCenter() const;
        void SetRectCenterX(float centerX);
        void SetRectCenterY(float centerY);
        float distancia(Point ponto);
    protected:
        /* vazio */
    private:
        /* vazio */
};

#endif // RECT_H
