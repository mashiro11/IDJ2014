#include "StageState.h"

StageState::StageState():
bg("images/ocean.jpg"),
tileSet(64,64, "images/img/tileSet.jpg"),
tileMap("images/map/tileMap.txt", &tileSet),
backGroundMusic("images/audio/stageState.ogg")
{
    cout << "construi o estagio" << endl;
    backGroundMusic.Play(-1);
    stringstream aux;
    Point position = tileMap.PixelToChessPosition(InputManager::GetInstance().GetMouseX(),
                                                  InputManager::GetInstance().GetMouseY());
    aux << position.x << " x " << position.y;
    Lider *lider = new Lider(6, 3, 10, 10, 4, 7, 10, 10, &tileMap);
    Lider::lider = lider;
    objectArray.emplace_back(lider);

    //cout << "inicia construcao do infoMenu" << endl;
    InfoMenu *infoMenu = new InfoMenu(770, 0, lider);
    objectArray.emplace_back(infoMenu);
    //cout << "finaliza construcao do infoMenu" << endl;

    SDL_Color color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    chessPosition.Initialize("images/font/Call me maybe.ttf", 60, Text::TEXT_BLENDED, aux.str() , color);
    chessPosition.SetPos( 0, 0);
    chessPosition.SetText(aux.str());
    cout << "terminei o estagio" << endl;
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
    Sprite::Clear();
}

void StageState::Update(float dt)
{
//    cout << "inicia um loop do estagio" << endl;
    Input();
    stringstream aux;
    Point position = tileMap.PixelToChessPosition(InputManager::GetInstance().GetMouseX(),
                                                  InputManager::GetInstance().GetMouseY());
    aux << position.x << " x " << position.y;
    chessPosition.SetText(aux.str());

    Camera::Update(Game::GetInstance().GetDeltaTime());
    for(int i = 0; i < objectArray.size(); i++){
        objectArray[ i ]->Update(Game::GetInstance().GetDeltaTime());
        if(objectArray[ i ]->IsDead() == true){
                objectArray.erase( objectArray.begin() + i );
        }
    }
    for(int i = 0; i < objectArray.size(); i++){
        for(int j = i + 1; j < objectArray.size(); j++ ){
                if(objectArray[i]->Is("StillAnimation") == false && objectArray[j]->Is("StillAnimation") == false){
                        if(Collision::IsColliding(objectArray[i]->box,
                                                  objectArray[j]->box,
                                                  objectArray[i]->rotation,
                                                  objectArray[j]->rotation) == true){
                                                        objectArray[i]->NotifyCollision(*objectArray[j]);
                                                        objectArray[j]->NotifyCollision(*objectArray[i]);
                        }
                }
        }
    }
    if(/* condicao de vitória*/ false){
        requestDelete = true;
        backGroundMusic.Stop();
        StateData fimDeJogo;
        fimDeJogo.playerVictory = true;
        EndState* endGame = new EndState(fimDeJogo);
        Game::GetInstance().Push(endGame);
    }
    if(/* condicao de derrota */ false){
        requestDelete = true;
        backGroundMusic.Stop();
        StateData fimDeJogo;
        fimDeJogo.playerVictory = false;
        EndState* endGame = new EndState(fimDeJogo);
        Game::GetInstance().Push(endGame);
    }
//    cout << "finaliza um loop do estagio" << endl;
}

void StageState::Render()
{
    bg.Render(0,0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	//personagem.Render(Camera::pos.x, Camera::pos.y);
	chessPosition.Render();
    for(unsigned int i = 0; i < objectArray.size(); i++){
              if( objectArray[i]->IsDead() == true){
                    continue;
              }
              objectArray[i]->Render(Camera::pos.x, Camera::pos.y);//linha alterada
    }
    //tileMap.RenderLayer(1, Camera::pos.x*2, Camera::pos.y*2);
}


void StageState::AddObject(int mouseX, int mouseY)
{
}

void StageState::Input() {
    if( InputManager::GetInstance().ShouldQuit() == true ){
            requestQuit = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true ){
            backGroundMusic.Stop();
            requestDelete = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_SPACE) == true ){
            AddObject(InputManager::GetInstance().GetMouseX(),
                      InputManager::GetInstance().GetMouseY());
    }
    if( InputManager::GetInstance().IsKeyDown(SDLK_KP_EQUALS)){
        backGroundMusic.VolumeUpdate(-50);
    }
    if( InputManager::GetInstance().IsKeyDown(SDLK_KP_MINUS)){
        backGroundMusic.VolumeUpdate(+50);
    }
}
