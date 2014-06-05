#include "Point.h"

//Simplificado no header
//Point::Point()
//{
//    //ctor
//}

Point::~Point()
{
    //dtor
}

float Point::distancia(Point outro_P)
{
     return sqrtf( (outro_P.x - this->x)*(outro_P.x - this->x)
                 + (outro_P.y - this->y)*(outro_P.y - this->y) );
}

float Point::coefAng(Point outro_P)
{
    if( (outro_P.x - this->x) != 0 ){
        return (outro_P.y - this->y)/(outro_P.x - this->x);
    }
    return nan("");
}

float Point::coefLin(Point outro_P)
{
    return (this->y) - coefAng(outro_P)* (this->x);
}
