#include "TileMap.h"

TileMap::TileMap(int mapWidth, int mapHeight, int layers, TileSet* tileSet)
{
    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;
    this->mapDepth = layers;
    tileMatrix.resize(mapWidth * mapHeight * mapDepth, -1);
    this->tileSet = tileSet;
}

TileMap::TileMap(string file, TileSet* tileSet)
{
    Load(file);
    this->tileSet = tileSet;
}

//TileMap::~TileMap()
//{
//    //dtor
//}

void TileMap::Load(string file)
{
    //uso de stdlib.h temporario
    FILE *arquivo = fopen(file.c_str(), "r");
    fscanf(arquivo, "%d", &mapWidth);
    fscanf(arquivo, "%*c");
    fscanf(arquivo, "%d", &mapHeight);
    fscanf(arquivo, "%*c");
    fscanf(arquivo, "%d", &mapDepth);
    fscanf(arquivo, "%*c");
    tileMatrix.resize( mapDepth * mapHeight * mapWidth , -1);

    int num;
    for(int k = 0, l = 0; k < mapDepth; k++){
        for(int i = 0; i < mapWidth; i++){
            for(int j = 0; j < mapHeight; j++, l++){
                            fscanf(arquivo, "%d", &num);
                            fscanf(arquivo, "%*c");
                            tileMatrix[ l ] = num - 1;
                            //cout << tileMatrix[ l ] << ",";
            }
                    //cout << endl;
        }
        //cout << endl;
    }
    //cout << endl;
    fclose(arquivo);
}

void TileMap::SetTileSet(TileSet* tileSet)
{
    this->tileSet = tileSet;
}
int& TileMap::At(int x, int y, int z)
{
    int posInVector = -1;
    int *endereco = NULL;
    if(x > mapWidth || y > mapHeight || z > mapDepth) return *endereco; //fora das dimensões da matriz
    posInVector = z*(mapWidth * mapHeight) + mapWidth * y + x;
    endereco = &(tileMatrix[posInVector]);
    return *endereco;
}
void TileMap::Render(int cameraX, int cameraY)
{
    for (int k = 0, l = 0; k < mapDepth; k++){
        for(int i = 0; i < mapWidth; i++){
                for(int j = 0; j < mapHeight; j++, l++){
                    //cout << "[" << l << "]: " << tileMatrix[l];
                    tileSet->Render(tileMatrix[l],
                                    j * tileSet->GetTileWidth() - cameraX,
                                    i * tileSet->GetTileHeight() - cameraY);
                }
        }
    }
}
void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    //Faz o mesmo que Render, mas para uma layer só.
    int k = layer * mapWidth * mapHeight;
    for(int i = 0; i < mapWidth; i++){
            for(int j = 0; j < mapHeight; j++, k++){
                tileSet->Render(tileMatrix[k],
                                j * tileSet->GetTileWidth() - cameraX,
                                i * tileSet->GetTileHeight() - cameraY);
            }
    }
}

int TileMap::GetSize()
{
    return tileMatrix.size();
}

int TileMap::GetTileSize()
{
    return tileSet->GetTileWidth();
}

Point TileMap::PixelToChessPosition(int x, int y)
{
    if(x < 0 && y < 0) return Point( -1, -1);
    else               return Point( (int)(x + Camera::pos.x)/tileSet->GetTileWidth(),
                                     (int)(y + Camera::pos.y)/tileSet->GetTileHeight() );
}
