#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H

#include <list>

#include "TileMap.h"
#include "Ally.h"

class MoveManager
{
    public:
        //MoveManager();
        //~MoveManager();
        static list<Point> MakePath(TileMap *tileMap, Point allyPosition);
    protected:
    private:
};

#endif // MOVEMANAGER_H
