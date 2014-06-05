#ifndef TILESET_H
#define TILESET_H

#include<string>
using std::string;
class TileSet
{
    public:
        //TileSet();
        ~TileSet();
        virtual void Open(string file) = 0;
        virtual void Render(unsigned index, int x, int y) = 0;
        int GetTileWidth(){return tileWidth;};
        int GetTileHeight(){return tileHeight;};

    protected:
        int tileWidth;
        int tileHeight;
    private:
};

#endif // TILESET_H
