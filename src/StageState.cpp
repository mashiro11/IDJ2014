#include "../include/StageState.h"

#define DEBUG
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

    GameObject* robo = new Robo(10, 10, ROBO_SP1);
    SetOnGrid(*robo, 3 , 5);
    AddObject(robo);//64 é o tamanho do tile
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
    //DEBUG_PRINT("StageState::Update()- inicio");
    //Tranqueira-----
    Input(dt);
    stringstream aux;
    //---------------


    for(auto it = objectArray.begin(); it != objectArray.end(); it++){
        (*it)->Update(dt);
    }
    Camera::Update(Game::GetInstance().GetDeltaTime());
    //DEBUG_PRINT("StageState::Update()- fim");
}

void StageState::Render()
{
    //DEBUG_PRINT("StageState::Render()- inicio");
    bg.Render();
    tilemap.Render();
	for(unsigned int i = 0; i < objectArray.size(); i++){
	    if( objectArray[i]->IsDead() == true) continue;
	    objectArray[i]->Render();
    }
	//DEBUG_PRINT("StageState::Render()- fim");
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
    if( InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) == true ){
            //arbitrario por enquanto
            if(Camera::pos.y > -tilemap.GetTileHeight()*2)
                Camera::pos.y -= CAMERA_SPEED;
    }
    if( InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) == true ){
            //arbitrario por enquanto
            if(Camera::pos.y + Game::GetInstance().GetWindowHeight() < tilemap.GetMapHeight() + tilemap.GetTileHeight()*2)
                Camera::pos.y += CAMERA_SPEED;
    }
    if( InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) == true ){
            //arbitrario por enquanto
            if(Camera::pos.x > -tilemap.GetTileWidth()*2)
                Camera::pos.x -= CAMERA_SPEED;
    }
    if( InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) == true ){
            //arbitrario por enquanto
            if(Camera::pos.x + Game::GetInstance().GetWindowWidth() < tilemap.GetMapWidth() + tilemap.GetTileWidth()*2)
                Camera::pos.x += CAMERA_SPEED;
    }
}

void StageState::SetOnGrid(GameObject& gameObject, int x, int y){
    gameObject.box.x = x * tilemap.GetTileWidth();
    gameObject.box.y = y * tilemap.GetTileHeight();
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
