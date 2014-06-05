#include "BlockTileSet.h"

BlockTileSet::BlockTileSet(int tileWidth, int tileHeight, string file)
{
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    Open(file);
}

void BlockTileSet::Open (string file)
{
    tileSet.Open(file);
    columns = tileSet.GetWidth()/tileWidth;
    rows = tileSet.GetHeight()/tileHeight;
}

void BlockTileSet::Render (unsigned index, int x, int y)
{
    if( index < columns * rows ){
        //cout << "Index: " << index << endl;
        //cout << "Columns: " << columns << endl;
        //cout << "Rows: " << rows << endl;
        //cout << "TileHeight: " <<  tileHeight << endl;
        //cout << "TileWidth: " <<  tileWidth << endl;
        int clipY;
        clipY = (index % columns);
        tileSet.SetClip( (index % columns) *  tileWidth, (index / columns ) * tileHeight, tileWidth, tileHeight);
        tileSet.Render( x , y );
    }
}
