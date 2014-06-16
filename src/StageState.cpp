#include "StageState.h"

StageState::StageState(CharacterData characters):
    #ifdef ANDRE
bg("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/ocean.jpg"),
tileSet(64,64, "C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/tileSet.jpg"),
tileMap("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/map/tileMap.txt", &tileSet),
backGroundMusic("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/audio/stageState.ogg")
#endif
#ifdef MASHIRO
bg("images/ocean.jpg"),
tileSet(64,64, "images/img/tileSet.jpg"),
tileMap("images/map/tileMap.txt", &tileSet),
backGroundMusic("images/audio/stageState.ogg")
#endif
{
    backGroundMusic.Play(-1);
    stringstream aux;
    Point position = tileMap.PixelToChessPosition(InputManager::GetInstance().GetMouseX(),
                                                  InputManager::GetInstance().GetMouseY());
    aux << position.x << " x " << position.y;

    InfoMenu *infoMenu = new InfoMenu(770, 0);
    objectArray.emplace_back(infoMenu);

    InicializaPersonagens(characters, infoMenu);


    SDL_Color color;
    color.r = 0;
    color.g = 0;
    color.b = 0;
    color.a = 255;

#ifdef ANDRE
    chessPosition.Initialize("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/font/Call me maybe.ttf", 60, Text::TEXT_BLENDED, aux.str() , color);
#endif
#ifdef MASHIRO
    chessPosition.Initialize("images/font/Call me maybe.ttf", 60, Text::TEXT_BLENDED, aux.str() , color);
#endif

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

void StageState::InicializaPersonagens(CharacterData characters, InfoMenu *infoMenu)
{
    if(find(characters.robo.begin(), characters.robo.end(), "Joao") != characters.robo.end()){
    //Joao
        #ifdef ANDRE
        Sprite sp("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/robot2iceaxe.png");
        Sprite pilotoSp1("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png");
        #endif
        #ifdef MASHIRO
        #endif
        Robo *robo = new Robo(7, 7, 10, 10, 4, 7, 10, 10, &tileMap, 5, true, sp, "Robotinic");
        objectArray.emplace_back(robo);
        infoMenu->InsereBotao(robo);

        Piloto *piloto = new Piloto(10, 10, 10, 2, 3, robo, 5, "Joao", pilotoSp1, true, &tileMap);
        infoMenu->InsereBotao(piloto);
        robo->InserePiloto(piloto);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Joana") != characters.robo.end()){
    //Joana
        #ifdef ANDRE
        Sprite sp2("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboRosa.png");
        Sprite pilotoSp2("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png");
        #endif
        #ifdef MASHIRO
        Sprite sp2("/images/img/roboRosa.png");
        Sprite pilotoSp2("/images/img/alien.png");
        #endif
        Robo *robo2 = new Robo(5, 5, 10, 10, 4, 7, 10, 10, &tileMap, 5, true, sp2, "Roboboy");
        objectArray.emplace_back(robo2);
        infoMenu->InsereBotao(robo2);

        Piloto *piloto2 = new Piloto(10, 10, 10, 2, 3, robo2, 5, "Joana", pilotoSp2, true, &tileMap);
        infoMenu->InsereBotao(piloto2);
        robo2->InserePiloto(piloto2);

    }

    if(find(characters.robo.begin(), characters.robo.end(), "Maria") != characters.robo.end()){
    //Maria
        #ifdef ANDRE
        Sprite sp3("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboVerde.png");
        Sprite pilotoSp3("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png");
        #endif
        #ifdef MASHIRO
        Sprite sp3("/images/img/roboVerde.png");
        Sprite pilotoSp3("/images/img/alien.png");
        #endif
        Robo *robo3 = new Robo(6, 6, 10, 10, 4, 7, 10, 10, &tileMap, 5, true, sp3, "Blitzcrank");
        objectArray.emplace_back(robo3);
        infoMenu->InsereBotao(robo3);

        Piloto *piloto3 = new Piloto(10, 10, 10, 2, 3, robo3, 5, "Maria", pilotoSp3, true, &tileMap);
        infoMenu->InsereBotao(piloto3);
        robo3->InserePiloto(piloto3);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Mario") != characters.robo.end()){
    //Mario
        #ifdef ANDRE
        Sprite sp4("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboPreto.png");
        Sprite pilotoSp4("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png");
        #endif
        #ifdef MASHIRO
        Sprite sp4("/images/img/roboPreto.png");
        Sprite pilotoSp4("/images/img/alien.png");
        #endif
        Robo *robo4 = new Robo(3, 3, 10, 10, 4, 7, 10, 10, &tileMap, 5, true, sp4, "OptimusPrime");
        objectArray.emplace_back(robo4);
        infoMenu->InsereBotao(robo4);

        Piloto *piloto4 = new Piloto(10, 10, 10, 2, 3, robo4, 5, "Joao", pilotoSp4, true, &tileMap);
        infoMenu->InsereBotao(piloto4);
        robo4->InserePiloto(piloto4);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Jose") != characters.robo.end()){
    //Jose
        #ifdef ANDRE
        Sprite sp5("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboAmarelo.png");
        Sprite pilotoSp5("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png");
        #endif
        #ifdef MASHIRO
        Sprite sp5("/images/img/roboAmarelo.png");
        Sprite pilotoSp5("/images/img/alien.png");
        #endif
        Robo *robo5 = new Robo(8, 8, 10, 10, 4, 7, 10, 10, &tileMap, 5, true, sp5, "Bamboubi");
        objectArray.emplace_back(robo5);
        infoMenu->InsereBotao(robo5);

        Piloto *piloto5 = new Piloto(10, 10, 10, 2, 3, robo5, 5, "Joao", pilotoSp5, true, &tileMap);
        infoMenu->InsereBotao(piloto5);
        robo5->InserePiloto(piloto5);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Josea") != characters.robo.end()){
    //Josea
        #ifdef ANDRE
        Sprite sp6("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/roboAzul.png");
        Sprite pilotoSp6("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/alien.png");
        #endif
        #ifdef MASHIRO
        Sprite sp6("/images/img/roboAzul.png");
        Sprite pilotoSp6("/images/img/alien.png");
        #endif
        Robo *robo6 = new Robo(4, 4, 10, 10, 4, 7, 10, 10, &tileMap, 5, true, sp6, "Walle");
        objectArray.emplace_back(robo6);
        infoMenu->InsereBotao(robo6);

        Piloto *piloto6 = new Piloto(10, 10, 10, 2, 3, robo6, 5, "Joao", pilotoSp6, true, &tileMap);
        infoMenu->InsereBotao(piloto6);
        robo6->InserePiloto(piloto6);
    }
}
