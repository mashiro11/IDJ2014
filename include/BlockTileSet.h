#ifndef BLOCKTILESET_H
#define BLOCKTILESET_H

#include "Sprite.h"
#include "TileSet.h"

#include <iostream>
#include <string>

class BlockTileSet : public TileSet
{
    public:
        BlockTileSet(int tileWidth, int tileHeight, string file);
        //~BlockTileSet();
        void Open (string file);
        void Render(unsigned index, int x, int y);
    protected:
        /* vazio */
    private:
        Sprite tileSet;
        int rows;
        int columns;
};
#endif // BLOCKTILESET_H
