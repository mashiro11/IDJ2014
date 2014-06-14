#ifndef TILEINFO_H
#define TILEINFO_H

#include "GameObject.h"

enum TileState{
            BLOCKED = 0,
            FREE,
            ALLY,
            ENEMY
};

class TileInfo
{
    public:
        TileInfo(int tileType = -1, TileState state = FREE, GameObject* occuper = NULL);
        TileInfo(){tileType = -1; state = FREE; occuper = NULL;}
        ~TileInfo();

        TileState state;
        int tileType;
        GameObject* occuper;
    protected:
    private:
        //Point mapAdress;
        //vector<Point> neighbors[4];
};

#endif // TILEINFO_H
