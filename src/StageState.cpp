#include "../include/StageState.h"

//#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

StageState::StageState():
    bg(STAGE_BACKGROUND_FILE),
    tilemap(STAGE_TILEMAP_FILE, STAGE_TILESET_FILE, STAGE_TILE_WIDTH, STAGE_TILE_WIDTH),
    backGroundMusic(STAGE_BACKGROUND_MUSIC_FILE)
{
    DEBUG_PRINT("StageState::StageState()-inicio");
    bg.SetCameraRelative(false);
    backGroundMusic.Play(-1);

    AddObject(new Robo(10, 10, ROBO_SP1));//64 é o tamanho do tile
    DEBUG_PRINT("StageState::StageState()-fim");
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
    Sprite::Clear();
}

void StageState::Update(float dt)
{
    DEBUG_PRINT("StageState::Update()- inicio");
    //Tranqueira-----
    Input(dt);
    stringstream aux;
    //---------------


    for(auto it = objectArray.begin(); it != objectArray.end(); it++){
        (*it)->Update(dt);
    }
    Camera::Update(Game::GetInstance().GetDeltaTime());
    DEBUG_PRINT("StageState::Update()- fim");
}

void StageState::Render()
{
    DEBUG_PRINT("StageState::Render()- inicio");
    bg.Render();
    tilemap.Render();
	for(unsigned int i = 0; i < objectArray.size(); i++){
	    if( objectArray[i]->IsDead() == true) continue;
	    objectArray[i]->Render();
    }
	DEBUG_PRINT("StageState::Render()- fim");
}

void StageState::Input(float dt) {
    if( InputManager::GetInstance().ShouldQuit() == true ){
            requestQuit = true;
    }
    if( InputManager::GetInstance().KeyPress(SDLK_ESCAPE) == true ){
            backGroundMusic.Stop();
            requestDelete = true;
    }
    if( InputManager::GetInstance().IsKeyDown(SDLK_KP_EQUALS)){
        backGroundMusic.VolumeUpdate(-50);
    }
    if( InputManager::GetInstance().IsKeyDown(SDLK_KP_MINUS)){
        backGroundMusic.VolumeUpdate(+50);
    }
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
