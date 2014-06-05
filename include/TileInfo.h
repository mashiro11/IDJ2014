#ifndef TILEINFO_H
#define TILEINFO_H

enum TileState{
            FREE = 0,
            BLOCKED,
            ALLY,
            ENEMY
};

class TileInfo
{
    public:
        TileInfo(int tileType = -1, TileState state = FREE);
        ~TileInfo();

        TileState state;
        int tileType;
    protected:
    private:
        //Point mapAdress;
        //vector<Point> neighbors[4];
};

#endif // TILEINFO_H
