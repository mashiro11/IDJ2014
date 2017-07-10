#include "../include/StageState.h"

StageState::StageState(CharacterData characters):
bg(STAGE_BACKGROUND_FILE),
tileSet(STAGE_TILE_W_H,STAGE_TILE_W_H, STAGE_TILESET_FILE),
backGroundMusic(STAGE_BACKGROUND_MUSIC_FILE),
tileMap(STAGE_TILEMAP_FILE, &tileSet)
{
    backGroundMusic.Play(-1);
    stringstream aux;
    Point position = tileMap.PixelToChessPosition(InputManager::GetInstance().GetMouseX(),
                                                  InputManager::GetInstance().GetMouseY());
    aux << position.x << " x " << position.y;

    InfoMenu *menuLateral = new InfoMenu(770,0);//(GAME_WIDTH, 0);
    this->infoMenu = menuLateral;

    Camera::pos.x = 300;
    Camera::pos.y = 750;

    InicializaPersonagens(characters, infoMenu);
    Enemy *enemy = new Enemy(1, 1, &tileMap, "UNICORN");
    enemy->SetStatus(10, 5, 2, 1, 7, 5);
    enemy->MakeRangeArea();
    objectArray.emplace_back(enemy);

    Enemy *enemy2 = new Enemy(18, 1, &tileMap, "HAHA");
    enemy2->SetStatus(10, 5, 2, 1, 7, 5);
    enemy2->MakeRangeArea();
    objectArray.emplace_back(enemy2);

    Chefe *chefe = new Chefe(9, 2, &tileMap, "Bozao");
    chefe->SetStatus(150, 10, 2, 1, 7, 5);
    chefe->MakeRangeArea();
    objectArray.emplace_back(chefe);

    chessPosition.Initialize(FONT1, 60, Text::TEXT_BLENDED, aux.str());
    chessPosition.SetColor(255, 0, 0);

    chessPosition.SetPos( 0, 0);
    chessPosition.SetText(aux.str());
    tileNumber = 1;
    showDebug = false;
}

StageState::~StageState()
{
    backGroundMusic.Stop();
    objectArray.clear();
    Sprite::Clear();
}

void StageState::Update(float dt)
{
    //cout << "update do stageState iniciado" << endl;
    Input(dt);
    stringstream aux;

    if(InputManager::GetInstance().KeyPress(SDLK_0) == true){
        if(showDebug == false) showDebug = true;
        else showDebug = false;
    }
    if(showDebug){
        Point mousePosition;
        if(tileNumber == 0){
                mousePosition.x = InputManager::GetInstance().GetMouseX();
                mousePosition.y = InputManager::GetInstance().GetMouseY();
        }else{
                mousePosition = tileMap.PixelToChessPosition(InputManager::GetInstance().GetMouseX(),
                                                             InputManager::GetInstance().GetMouseY(), tileNumber);
        }
        aux << mousePosition.x << " x " << mousePosition.y;
        chessPosition.SetText(aux.str());
    }


    Camera::Update(Game::GetInstance().GetDeltaTime());
    infoMenu->Update(dt);
    //cout << "   verificando quem morreu" << endl;
    for(int i = 0; i < objectArray.size(); i++){
        //cout << "   ->>inicio do loop" << endl;
        objectArray[ i ]->Update(Game::GetInstance().GetDeltaTime());
        //cout << "   ->>verifica if" << endl;
        if(objectArray[ i ]->IsDead() == true){
                //cout << "   ->>inicio do if" << endl;
                if(objectArray[i]->Is("Ally")){
                    infoMenu->NotificarMorte(objectArray[i]->GetNome());
                    if(objectArray[i]->IsLeader() == true){
                        requestDelete = true;
                        backGroundMusic.Stop();
                        StateData fimDeJogo;
                        fimDeJogo.playerVictory = false;
                        EndState* endGame = new EndState(fimDeJogo);
                        Game::GetInstance().Push(endGame);
                    }
                    /*if(object que morreu for um lider){endstate}*/
                }

                if(objectArray[i]->Is("Robo")){
                    /*gambiarra*/
                    objectArray[i]->Morrer();
                }
                objectArray.erase( objectArray.begin() + i );
                //cout << "   ->>fim do if" << endl;
        }
        //cout << "   ->>fim do loop" << endl;
    }
    //cout << "   excluidos itens mortos" << endl;

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

    if(Chefe::chefeMorto == 1){
        vitoriaTime.Update(dt);
        if(vitoriaTime.Get() > 2.5){
            requestDelete = true;
            backGroundMusic.Stop();
            StateData fimDeJogo;
            vitoriaTime.Restart();
            fimDeJogo.playerVictory = true;
            EndState* endGame = new EndState(fimDeJogo);
            Game::GetInstance().Push(endGame);
        }
    }

    if(/* condicao de derrota */0){
        requestDelete = true;
        backGroundMusic.Stop();
        StateData fimDeJogo;
        fimDeJogo.playerVictory = false;
        EndState* endGame = new EndState(fimDeJogo);
        Game::GetInstance().Push(endGame);
    }
    //cout << "update do stageState terminado" << endl;
}

void StageState::Render()
{
    bg.Render(0,0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	//personagem.Render(Camera::pos.x, Camera::pos.y);
	if(showDebug) chessPosition.Render();
    for(unsigned int i = 0; i < objectArray.size(); i++){
          if( objectArray[i]->IsDead() == true){
                continue;
          }
          objectArray[i]->Render(Camera::pos.x, Camera::pos.y);//linha alterada
    }
    infoMenu->Render(Camera::pos.x, Camera::pos.y);
    //tileMap.RenderLayer(1, Camera::pos.x*2, Camera::pos.y*2);
}


void StageState::AddObject(int mouseX, int mouseY)
{
}

void StageState::Input(float dt) {
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
    if(InputManager::GetInstance().KeyPress(SDLK_1) == true ){
        tileNumber = 1;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_2) == true ){
        tileNumber = 2;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_3) == true ){
        tileNumber = 3;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_0) == true ){
        tileNumber = 0;
    }
}

void StageState::InicializaPersonagens(CharacterData characters, InfoMenu *infoMenu)
{
    if(find(characters.robo.begin(), characters.robo.end(), "Joao") != characters.robo.end()){
    //Joao
        Sprite sp(ROBO_SP1);
        Sprite pilotoSp1(PILOTO_SP1);
        Robo *robo = new Robo(7, 18, &tileMap, false, sp, "Robotinic");
        cout << "robo construido" << endl;
        robo->SetStatus(10, 10, 2, 5, 7, 5, 10);
        robo->MakeRangeArea();
        objectArray.emplace_back(robo);
        infoMenu->InsereBotao(robo);

        Piloto *piloto = new Piloto(robo, "Joao", pilotoSp1, true, &tileMap);
        piloto->SetStatus(70, 5, 1, 3, 5, 4, 10);
        objectArray.emplace_back(piloto);
        infoMenu->InsereBotao(piloto);
        robo->InserePiloto(piloto);
    }
}
