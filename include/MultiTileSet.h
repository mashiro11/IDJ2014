#ifndef MULTITILESET_H
#define MULTITILESET_H

#include "TileSet.h"
#include "Sprite.h"

class MultiTileSet : public TileSet
{
    public:
        MultiTileSet();
        MultiTileSet(int tileWidth, int tileHeight);
        ~MultiTileSet();
        void Open(string file);
        void Render(unsigned index, int x, int y);
    protected:
        vector<Sprite> tileArray;
    private:
};

#endif // MULTITILESET_H
