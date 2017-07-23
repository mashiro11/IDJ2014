#include <cstdio>

#include "TileMap.h"

#define DEBUG
#ifdef DEBUG
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        #define DEBUG_PRINT(message)
#endif //DEBUG

TileMap::TileMap(string file, string tileSetFile, int tileWidth, int tileHeight):
    tileSet(tileSetFile),
    tileWidth(tileWidth),
    tileHeight(tileHeight)
{
    DEBUG_PRINT("TileMap::TileMap() - inicio");
    if(this->tileSet.IsOpen()){
		this->rows = this->tileSet.GetHeight()/this->tileHeight;
		this->columns = this->tileSet.GetWidth()/this->tileWidth;
	}
	Load(file);
	PrintMap(); //para DEBUG
	DEBUG_PRINT("TileMap::TileMap() - fim");
}

TileMap::~TileMap() {

}

void TileMap::PrintMap(){
	for(int k = 0; k < this->mapDepth; k++){
		for(int j = 0; j < this->mapHeight; j++){
			for(int i =0 ; i < this->mapWidth; i++){
				if(At(i, j, k) < 10)
					cout << "0";
				cout << At(i,j,k) << ",";
			}
			cout << endl;
		}
	}
}

void TileMap::Render(){
	//DEBUG_PRINT("TileMap::Render() - inicio");
	for(int i = 0; i < this->mapDepth; i++){
		RenderLayer(i);
	}
	//DEBUG_PRINT("TileMap::Render() - fim");
}

void TileMap::RenderLayer(int layer){
    //DEBUG_PRINT("TileMap::RenderLayer() - inicio");
    int index;
    for(int j = 0; j < this->mapHeight; j++){
		for(int i = 0; i < this->mapWidth; i++){
			index = At(i, j, layer);
            tileSet.SetClip( (index%columns) * this->tileWidth, // 1 | 2 | => 2 colunas, movimenta em x
                             (index/columns) * this->tileHeight,        // 3 | 4 | => 2a linha, movimenta em y
                             this->tileWidth,
                             this->tileHeight
                           );
            tileSet.SetPosition(tileWidth * i, tileHeight * j);
            this->tileSet.Render();
		}
    }
    //DEBUG_PRINT("TileMap::RenderLayer() - fim");
}

void TileMap::Load(string file){
	DEBUG_PRINT("TileMap::Load() - inicio");
	//FILE* arq = fopen(file.c_str(), "r");
    ifstream arquivo;
    stringstream aux;
    string line;
    arquivo.open(file.c_str(), std::ifstream::in);
    getline(arquivo, line);
    DEBUG_PRINT(line);

    aux << line;
    aux >> mapWidth;
    if(aux.peek() == ',') aux.ignore();

	aux << line;
    aux >> mapHeight;
    if(aux.peek() == ',') aux.ignore();

	aux << line;
    aux >> mapDepth;
    if(aux.peek() == ',') aux.ignore();
    if(aux.peek() == '\n') aux.ignore();
    if(aux.peek() == '\r') aux.ignore();
    //fscanf(arq, "%i, %i, %i,", &this->mapWidth, &this->mapHeight, &this->mapDepth);

	this->tileMatrix.resize(this->mapWidth * this->mapHeight * this->mapDepth);
    aux.str(string());
	for(int k = 0 ; k < this->mapDepth; k++){
        for(int j = 0 ; j < this->mapHeight; j++){
            getline(arquivo, line);
            DEBUG_PRINT(line);
            for(int i = 0; i < this->mapWidth; i++){
                DEBUG_PRINT("i-j-k: " << i << "x" << j << "x" << k);
			    aux << line;
                aux >> At(i,j,k);
                At(i,j,k) -= 1;     //com o codigo dos tiles começando em 0, apagar essa linha
                DEBUG_PRINT("valor: " << At(i,j,k));
                if(aux.peek() == ',') aux.ignore();
			}
			aux.str(string());
		}
	}
	arquivo.close();
	DEBUG_PRINT("TileMap::Load() - fim");
}
int& TileMap::At(int x, int y, int z){
	return this->tileMatrix[x + y * this->mapWidth + z * this->mapHeight * this->mapWidth];
}

int TileMap::GetWidth(){
	return this->mapWidth;
}
int TileMap::GetHeight(){
		return this->mapHeight;
}
int TileMap::GetDepth(){
		return this->mapDepth;
}

int TileMap::GetTileWidth(){
	return this->tileWidth;
}

int TileMap::GetTileHeight(){
		return this->tileHeight;
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
