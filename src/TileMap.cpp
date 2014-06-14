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
                            tileMatrix[ l ].tileType = num - 1;

                            if(tileMatrix[ l ].tileType == 1 ||
                               tileMatrix[ l ].tileType == -1){
                                    //cout << "tile bloqueado" << endl;
                                    tileMatrix[ l ].state = BLOCKED;
                            }
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

TileInfo& TileMap::At(int x, int y, int z)
{
    int posInVector = -1;
    TileInfo *endereco = NULL;
    if(x > mapWidth || y > mapHeight || z > mapDepth) return *endereco; //fora das dimens?es da matriz
    posInVector = z*(mapWidth * mapHeight) + mapWidth * y + x;
    //endereco = &(tileMatrix[posInVector].tileType);
    endereco = &(tileMatrix[posInVector]);
    return *endereco;
}
void TileMap::Render(int cameraX, int cameraY)
{
    for (int k = 0, l = 0; k < mapDepth; k++){
        for(int i = 0; i < mapWidth; i++){
                for(int j = 0; j < mapHeight; j++, l++){
                    tileSet->Render(tileMatrix[l].tileType,
                                    j * tileSet->GetTileWidth() - cameraX,
                                    i * tileSet->GetTileHeight() - cameraY);
                }
        }
    }
}
void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
    //Faz o mesmo que Render, mas para uma layer s?.
    int k = layer * mapWidth * mapHeight;
    for(int i = 0; i < mapWidth; i++){
            for(int j = 0; j < mapHeight; j++, k++){
                tileSet->Render(tileMatrix[k].tileType,
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

float TileMap::TileCenter(int coord)
{
    return coord * GetTileSize() + GetTileSize()/2;
}

float TileMap::MapPositionToPixelPosition(int coord)
{
    return GetTileSize() * coord + GetTileSize()/2.0;
}

int TileMap::PixelPositionToMapPosition(int pixels)
{
    return pixels/GetTileSize();
}
