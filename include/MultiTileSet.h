#ifndef MULTITILESET_H
#define MULTITILESET_H
//  STD classes
#include <vector>

//  Game Classes
#include "TileSet.h"
#include "Sprite.h"

using std::vector;

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
