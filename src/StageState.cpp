#include "StageState.h"

StageState::StageState():
bg("images/ocean.jpg"),
tileSet(64,64, "images/img/tileSet.jpg"),
tileMap("images/map/tileMap.txt", &tileSet),
backGroundMusic("images/audio/stageState.ogg")
{
    backGroundMusic.Play(-1);
    stringstream aux;
    Point position = tileMap.PixelToChessPosition(InputManager::GetInstance().GetMouseX(),
                                                  InputManager::GetInstance().GetMouseY());
    aux << position.x << " x " << position.y;

    Lider *lider = new Lider(64, 4, 1, 10, 10, 10, 10, 5, 5, 3);
    Lider::lider = lider;
    objectArray.emplace_back(lider);

    Robo *robo = new Robo(64, 6, 3, 10, 10, 10, 10, 5, 5, 3);
    objectArray.emplace_back(robo);

    Piloto *piloto = new Piloto(64, 10, 10, 10, 10, 10, robo, 3);
    objectArray.emplace_back(piloto);
    robo->InserePiloto(piloto);

    InfoMenu *infoMenu = new InfoMenu(770, 0);
    objectArray.emplace_back(infoMenu);

    infoMenu->InsereBotao(lider);
    infoMenu->InsereBotao(robo);
    infoMenu->InsereBotao(piloto);

    SDL_Color color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;
    chessPosition.Initialize("images/font/Call me maybe.ttf", 60, Text::TEXT_BLENDED, aux.str() , color);
    chessPosition.SetPos( 0, 0);
    chessPosition.SetText(aux.str());
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
    Sprite::Clear();
}

void StageState::Update(float dt)
{
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
    if(/* condicao de vitória*/0){
        requestDelete = true;
        backGroundMusic.Stop();
        StateData fimDeJogo;
        fimDeJogo.playerVictory = true;
        EndState* endGame = new EndState(fimDeJogo);
        Game::GetInstance().Push(endGame);
    }
    if(/* condicao de derrota */0){
        requestDelete = true;
        backGroundMusic.Stop();
        StateData fimDeJogo;
        fimDeJogo.playerVictory = false;
        EndState* endGame = new EndState(fimDeJogo);
        Game::GetInstance().Push(endGame);
    }
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
