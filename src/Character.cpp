#include "../include/Character.h"

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

void Character::MakeRangeArea(int tileNumber)
{
    if(tileNumber == 1){
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
    }else if(tileNumber == 2){

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
    CloseEnemiesUpdate();
}

void Character::CloseEnemiesUpdate()
{
    //cout << this->nome << ": inicio do loop. closeEnemies.size(): " << closeEnemies.size() << endl;
    bool itemRemovido = false;
    int i = 0;
    for(unordered_map<GameObject*, Point>::iterator aux = closeEnemies.begin(); aux != closeEnemies.end(); i++){
        //cout << "testando: (" << aux->second.x << ", " << aux->second.y << ")" << endl;
        if(aux->second.x < mapReference->GetWidth() &&
           aux->second.y < mapReference->GetHeight()){
                if(mapReference->At(aux->second.x, aux->second.y).occuper == NULL ||
                   (abs(aux->second.x - currentPosition.x) + abs(aux->second.y - currentPosition.y) ) > range){
                        closeEnemies.erase( aux );
                        itemRemovido = true;

                }
        }
        if(closeEnemies.empty() == true){
                aux = closeEnemies.end();
        }else{
                aux++;
                if(itemRemovido == true ){
                    if(i < closeEnemies.size()){
                        aux++;
                        itemRemovido = false;
                    }else{
                        aux = closeEnemies.end();
                    }
                }
        }
    }
    //cout << "fim do loop" << endl;
}
void Character::IdentifyOpponent()
{
    //cout << this->nome << " entrou no Identify" << endl;
    if(Is("Ally") == true){
        //cout << "inicio do loop" << endl;
        for(int i = 0; i < rangeMap.size(); i++){
            //cout << "(" <<  rangeMap[i].x << "," << rangeMap[i].y << ")" << endl;
            if(rangeMap[i].x < mapReference->GetWidth() &&
               rangeMap[i].y < mapReference->GetHeight()){
                        if(mapReference->At( rangeMap[i].x, rangeMap[i].y ).state ==  ENEMY){

                            Point enemyPosition(rangeMap[i].x, rangeMap[i].y);
                            closeEnemies[ mapReference->At( rangeMap[i].x, rangeMap[i].y ).occuper ] = enemyPosition;
                            //cout << "Inimigos proximos de " << this->nome << ": " << closeEnemies.size() << " -#" << endl;
                        }
            }
        }
        //cout << "fim do loop" << endl;
    }else if(Is("Enemy") == true){
        //cout << "inicio do loop" << endl;
        for(int i = 0; i < rangeMap.size(); i++){
            //cout << "(" <<  rangeMap[i].x << "," << rangeMap[i].y << ")" << endl;
            if(rangeMap[i].x < mapReference->GetWidth() &&
               rangeMap[i].y < mapReference->GetHeight()){
                   //cout << "estou olhando apenas nos limites do mapa" << endl;
                    if(mapReference->At( rangeMap[i].x, rangeMap[i].y ).state ==  ALLY ){
                        //cout << "Sei que tem um ally perto >=)" << endl;
                        Point enemyPosition(rangeMap[i].x, rangeMap[i].y);
                        closeEnemies[ mapReference->At( rangeMap[i].x, rangeMap[i].y ).occuper ] = enemyPosition;
                        //cout << "Aliados proximos de " << this->nome << ": " << closeEnemies.size() << " -#" << endl;
                    }
            }
        }
    }
}

string Character::GetNome()
{
    return this->nome;
}

void Character::Pathfinder(int goalX, int goalY)
{
    cout << "inicio pathfinder" << endl;
    cout << "goal: " << goalX << ", " << goalY << endl;
    cout << "currentP: " << currentPosition.x << ", " << currentPosition.y << endl;
    if(currentPosition.x != goalX || currentPosition.y != goalY){
            vector<NODO> processed;
            queue<NODO> toProcess;
            NODO novo;

            novo.indice = -1;
            novo.point.x = currentPosition.x;
            novo.point.y = currentPosition.y;
            processed.emplace_back(novo);

            int indicePai = 0;
            novo.indice = indicePai;

            if(currentPosition.y - 1 >= 0 &&
               (mapReference->At(currentPosition.x, currentPosition.y - 1).state == FREE ||
                mapReference->At(currentPosition.x, currentPosition.y - 1).state == ENEMY) ){
                    novo.point.x = currentPosition.x;
                    novo.point.y = currentPosition.y - 1;
                    toProcess.push(novo);
                    cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
                         << " - pai: " << toProcess.back().indice << endl;
            }

            if(currentPosition.y + 1 < mapReference->GetHeight() &&
               (mapReference->At(currentPosition.x, currentPosition.y + 1).state == FREE ||
                mapReference->At(currentPosition.x, currentPosition.y + 1).state == ENEMY) ){
                    novo.point.x = currentPosition.x;
                    novo.point.y = currentPosition.y + 1;
                    toProcess.push(novo);
                    cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
                         << " - pai: " << toProcess.back().indice << endl;
            }

            if(currentPosition.x + 1 < mapReference->GetWidth() &&
               (mapReference->At(currentPosition.x + 1, currentPosition.y).state == FREE ||
                mapReference->At(currentPosition.x + 1, currentPosition.y).state == ENEMY) ){
                    novo.point.x = currentPosition.x + 1;
                    novo.point.y = currentPosition.y;
                    toProcess.push(novo);
                    cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
                         << " - pai: " << toProcess.back().indice << endl;
            }

            if(currentPosition.x - 1 >= 0 &&
               (mapReference->At(currentPosition.x - 1, currentPosition.y).state == FREE ||
                mapReference->At(currentPosition.x - 1, currentPosition.y).state == ENEMY) ){
                    novo.point.x = currentPosition.x - 1;
                    novo.point.y = currentPosition.y;
                    toProcess.push(novo);
                    cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
                         << " - pai: " << toProcess.back().indice << endl;
            }
            ++indicePai;
            do{
                    if(toProcess.front().point.x == goalX && toProcess.front().point.y == goalY){
                        int anterior = toProcess.front().indice;

                        novo.indice = indicePai;
                        novo.point.x = toProcess.front().point.x;
                        novo.point.y = toProcess.front().point.y;

                        stack<Point> temp;
                        temp.push( Point( toProcess.front().point.x, toProcess.front().point.y ) );
//                        cout << "processed.size: " << processed.size() << endl;
//                        cout << "novo: " << novo.point.x << ", " <<  novo.point.y << endl;
//                        cout << "novo.indice: " << novo.indice << endl;
//                        for(int j = 0; j < processed.size(); j++){
//                            cout << "processed[" << j << "]: " << processed[j].point.x << ", " << processed[j].point.y << endl;
//                        }
//                        cout << "- - - -" << endl;
//                        cout << "toProcess.front(): " << toProcess.front().point.x << ", " << toProcess.front().point.y
//                             << " - pai: " << toProcess.front().indice << endl;
                        while(anterior != -1){
                        //    cout << "processed[anterior]: " << processed[anterior].point.x << ", " << processed[anterior].point.y << endl;
                            temp.push( Point( processed[anterior].point.x, processed[anterior].point.y ) );
//                            cout << "path: " << temp.top().x << ", " << temp.top().y
//                                 << " - pai:" << processed[anterior].indice << endl;
                            anterior = processed[anterior].indice;
                        }
                        while(temp.empty() == false){
                            path.push( Point(temp.top().x, temp.top().y) );
                            temp.pop();
                        }
                        break;
                    }else{
                        if(toProcess.empty() == false){
                                //insere apenas se ele nao foi processado
                                int i = 0;
                                for( i = 0; i < processed.size(); i++ ){
                                    if(processed[i].point.x == toProcess.front().point.x &&
                                       processed[i].point.y == toProcess.front().point.y){
                                           i = -1;
                                           break;
                                       }
                                }
                                if(i == processed.size()){
                                    processed.emplace_back( toProcess.front() );
                                }else{
                                    toProcess.pop();
                                    //cout << "ja foi processado" << endl;
                                    //cout << "fim do false" << endl;
                                    continue;
                                }

                                novo.indice = indicePai;
                                novo.point.x = toProcess.front().point.x;
                                novo.point.y = toProcess.front().point.y;
                                toProcess.pop();

                                //cout << "processed.back: " << processed.back().point.x << ", " << processed.back().point.y << endl;
                                if(processed.back().point.y - 1 >= 0 &&
                                   (mapReference->At(processed.back().point.x, processed.back().point.y - 1).state == FREE ||
                                    mapReference->At(processed.back().point.x, processed.back().point.y - 1).state == ENEMY) ){
                                        novo.point.y -= 1;
                                        toProcess.push(novo);
                                        novo.point.y += 1 ;
//                                        cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
//                                             << " - pai: " << toProcess.back().indice << endl;
                                }

                                if(processed.back().point.y + 1 < mapReference->GetHeight() &&
                                   (mapReference->At(processed.back().point.x, processed.back().point.y + 1).state == FREE ||
                                    mapReference->At(processed.back().point.x, processed.back().point.y + 1).state == ENEMY) ){
                                        novo.point.y += 1;
                                        toProcess.push(novo);
                                        novo.point.y -= 1 ;
//                                        cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
//                                             << " - pai: " << toProcess.back().indice << endl;
                                }

                                if(processed.back().point.x + 1 < mapReference->GetWidth() &&
                                   (mapReference->At(processed.back().point.x + 1, processed.back().point.y).state == FREE ||
                                    mapReference->At(processed.back().point.x + 1, processed.back().point.y).state == ENEMY) ){
                                        novo.point.x += 1;
                                        toProcess.push(novo);
                                        novo.point.x -= 1 ;
//                                        cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
//                                             << " - pai: " << toProcess.back().indice << endl;
                                }

                                if(processed.back().point.x - 1 >= 0 &&
                                   (mapReference->At(processed.back().point.x - 1, processed.back().point.y).state == FREE ||
                                    mapReference->At(processed.back().point.x - 1, processed.back().point.y).state == ENEMY) ){
                                        novo.point.x -= 1;
                                        toProcess.push(novo);
                                        novo.point.y += 1 ;
//                                        cout << "toProcess.back(): " << toProcess.back().point.x << ", " << toProcess.back().point.y
//                                             << " - pai: " << toProcess.back().indice << endl;
                                }

                                //cout << "fim do false" << endl;
                        }else{//de if(toProcess.empty() == false)
                                //cout << "impossivel de chegar" << endl;
                                break;
                        }
                    ++indicePai;
                    }
            }while(1);
    }
    //cout << "fim pathfinder" << endl;
}

bool Character::Centered()
{
    if(box.RectCenterX() == mapReference->TileCenter( currentPosition.x ) &&
       box.RectCenterY() == mapReference->TileCenter( currentPosition.y )){
            return true;
    }
    return false;
}

int Character::GetCurrentX()
{
    return currentPosition.x;
}

int Character::GetCurrentY()
{
    return currentPosition.y;
}

