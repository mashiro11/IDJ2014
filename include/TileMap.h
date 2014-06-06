#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


#include "MultiTileSet.h"
#include "Point.h"


using std::vector;
using std::ifstream;
using std::stringstream;
using std::getline;
using std::cout;
using std::endl;
using std::streambuf;

class TileMap
{
    public:
        TileMap(int mWidth, int mHeight, int layers, TileSet* tileSet = NULL);
        TileMap(string file, TileSet* tileSet = NULL);
        void Load(string file);
        void SetTileSet(TileSet* tileSet);
        TileInfo& At(int x, int y, int z = 0);
        void Render (int cameraX = 0, int cameraY = 0);
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

        int GetWidth(){return mapWidth;};
        int GetHeight(){return mapHeight;};
        int GetDepth(){return mapDepth;};
        //~TileMap();
        Point PixelToChessPosition(int x, int y);
        int GetTileSize();
        int GetSize();
    protected:
        /* vazio */
    private:
        vector<int> tileMatrix;
        //O mapa nao pode conter só ints, deverá conter informação de estar ou nao ocupado, além de quais
        //tiles são seus vizinhos
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};

#endif // TILEMAP_H
