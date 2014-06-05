#include "MultiTileSet.h"

MultiTileSet::MultiTileSet()
{

}

MultiTileSet::MultiTileSet(int tileWidth, int tileHeight)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
}

MultiTileSet::~MultiTileSet()
{
    tileArray.clear();
}
void MultiTileSet::Open(string file)
{
    tileArray.emplace_back(file);
}
void MultiTileSet::Render(unsigned index, int x, int y)
{
    if( index < tileArray.size() ){
        tileArray[index].Render(x,y);
    }
}
