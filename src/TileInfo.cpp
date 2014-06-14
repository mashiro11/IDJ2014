#include "TileInfo.h"

TileInfo::TileInfo(int tileType, TileState state, GameObject* occuper)
{
    this->tileType = tileType;
    this->state = state;
    this->occuper = occuper;
}

TileInfo::~TileInfo()
{
    //dtor
}
