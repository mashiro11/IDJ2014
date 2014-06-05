#ifndef POINT_H
#define POINT_H

#include <math.h>


class Point
{
    public:
        Point(){x = 0; y = 0;};
        Point(float coordX, float coordY){ x = coordX; y = coordY;};
        ~Point();
        float distancia(Point outro_P);
        float coefAng(Point outro_p);
        float coefLin(Point outro_P);
        void SetPoint(float coordX, float coordY){ x = coordX; y = coordY;};

        // Aqui est�o tr�s operadores que sua classe Point deve precisar, se j� n�o tiver.
        // Se sua classe tiver m�todos para Mag, Norm, Dot e/ou Rotate, voc� pode substituir
        // os usos desses m�todos por usos dos seus, mas garanta que deem resultados corretos.

         Point operator+(const Point& rhs) const {
            return Point(x + rhs.x, y + rhs.y);
         }

         Point operator-(const Point& rhs) const {
            return Point(x - rhs.x, y - rhs.y);
         }

         Point operator*(const float rhs) const {
            return Point(x * rhs, y * rhs);
         }

        float x, y;
    protected:
        /* vazio */
    private:
        /* vazio */
};

#endif // POINT_H
