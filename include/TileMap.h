#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Sprite.h"
#include "Camera.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;
using std::getline;

class TileMap {
public:
	TileMap(std::string file, string tilesetFile, int tileWidth, int tileHeight);
	~TileMap();

	void PrintMap();

    void Render();
	void RenderLayer(int layer);

	void Load(std::string file);
	int& At(int x, int y, int z = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();

	int GetTileWidth();
	int GetTileHeight();

private:
	vector<int> tileMatrix;
	int mapWidth;
	int mapHeight;
	int mapDepth;


	Sprite tileSet;
	int rows, columns;
	int tileWidth, tileHeight;

};

#endif
