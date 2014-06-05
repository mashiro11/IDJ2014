#include "TileInfo.h"

TileInfo::TileInfo(int tileType, TileState state)
{
    this->tileType = tileType;
    this->state = state;
}

TileInfo::~TileInfo()
{
    //dtor
}
