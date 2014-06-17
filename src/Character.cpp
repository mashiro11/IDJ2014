#include "Character.h"

//Character::Character()
//{
//
//}

Character::~Character()
{
    //dtor
}

void Character::Render(int cameraX, int cameraY)
{
    sp.Render(box.x - cameraX, box.y - cameraY);
}

void Character::MakeRangeArea()
{
    Point currentPosition( mapReference->PixelPositionToMapPosition( this->box.RectCenterX() ),
                           mapReference->PixelPositionToMapPosition( this->box.RectCenterY() ) );
    for(int i = 0; i < range; i++){
        int contX = 0;
        int contY = i - range;
        int incrementX = 1;
        int incrementY = 1;

        for(int j = 0; j < (range - i)*4; j++){
                if( contX == range - i && contY == 0 ){
                    incrementX = -1;
                    incrementY =  1;
                }
                if( contX == 0 && contY == range - i ){
                    incrementX = -1;
                    incrementY = -1;
                }
                if( contX == i - range && contY == 0 ){
                    incrementX =  1;
                    incrementY = -1;
                }
                rangeMap.emplace_back( Point(currentPosition.x + contX, currentPosition.y + contY) );
                contX += incrementX;
                contY += incrementY;
        }
    }
}

void Character::RangeAreaUpdate(int x, int y)
{
    if(x != 0){
        for(int i = 0; i < rangeMap.size(); i++){
            rangeMap[i].x += x;
        }
    }else if(y != 0){
        for(int i = 0; i < rangeMap.size(); i++){
            rangeMap[i].y += y;
        }
    }
    for(unordered_map<GameObject*, Point>::iterator aux = closeEnemies.begin(); aux != closeEnemies.end(); aux++){
        if(mapReference->At(aux->second.x, aux->second.y).state == FREE){
                closeEnemies.erase( aux );
        }
    }
}

void Character::IdentifyOpponent()
{
    //cout << this->nome << " entrou no Identify" << endl;
    if(Is("Ally") == true){
        for(int i = 0; i < rangeMap.size(); i++){
            if(mapReference->At( rangeMap[i].x, rangeMap[i].y ).state ==  ENEMY){

                Point enemyPosition(rangeMap[i].x, rangeMap[i].y);
                closeEnemies[ mapReference->At( rangeMap[i].x, rangeMap[i].y ).occuper ] = enemyPosition;
                cout << "Inimigos proximos de " << this->nome << ": " << closeEnemies.size() << " -#" << endl;
            }
        }
    }else if(Is("Enemy") == true){
        for(int i = 0; i < rangeMap.size(); i++){
            if(mapReference->At( rangeMap[i].x, rangeMap[i].y ).state ==  ALLY ){

                Point enemyPosition(rangeMap[i].x, rangeMap[i].y);
                closeEnemies[ mapReference->At( rangeMap[i].x, rangeMap[i].y ).occuper ] = enemyPosition;
                cout << "Aliados proximos de " << this->nome << ": " << closeEnemies.size() << " -#" << endl;
            }
        }
    }
}
