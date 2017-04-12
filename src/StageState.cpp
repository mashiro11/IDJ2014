#include "../include/StageState.h"

StageState::StageState(CharacterData characters):
bg("img/ocean.jpg"),
tileSet(64,64, "img/tileSet.jpg"),
tileMap("images/map/tileMap20x20.txt", &tileSet),
backGroundMusic("images/audio/Tema_Boss_01.wav")
{
    backGroundMusic.Play(-1);
    stringstream aux;
    Point position = tileMap.PixelToChessPosition(InputManager::GetInstance().GetMouseX(),
                                                  InputManager::GetInstance().GetMouseY());
    aux << position.x << " x " << position.y;

    InfoMenu *menuLateral = new InfoMenu(GAME_WIDTH, 0);
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

    chessPosition.Initialize("images/font/Call me maybe.ttf", 60, Text::TEXT_BLENDED, aux.str());
    chessPosition.SetColor(255, 0, 0);

    chessPosition.SetPos( 0, 0);
    chessPosition.SetText(aux.str());
    tileNumber = 1;
    cout << "construtor do stageState: fim" << endl;
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
        Sprite sp("img/robot2iceaxe.png");
        Sprite pilotoSp1("img/pilotoPrata.png");
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

    if(find(characters.robo.begin(), characters.robo.end(), "Joana") != characters.robo.end()){
    //Joana
        Sprite sp2("img/roboRosa.png");
        Sprite pilotoSp2("img/pilotoRosa.png");
        Robo *robo2 = new Robo(8, 18, &tileMap, false, sp2, "Roboboy");
        robo2->SetStatus(60, 5, 2, 5, 7, 5, 10);
        robo2->MakeRangeArea();
        objectArray.emplace_back(robo2);
        infoMenu->InsereBotao(robo2);

        Piloto *piloto2 = new Piloto(robo2, "Joana", pilotoSp2, false, &tileMap);
        piloto2->SetStatus(10, 5, 1, 3, 4, 4, 10);
        objectArray.emplace_back(piloto2);
        infoMenu->InsereBotao(piloto2);
        robo2->InserePiloto(piloto2);

    }

    if(find(characters.robo.begin(), characters.robo.end(), "Maria") != characters.robo.end()){
    //Maria
        Sprite sp3("img/roboVerde.png");
        Sprite pilotoSp3("img/pilotoVerde.png");
        Robo *robo3 = new Robo(9, 18, &tileMap, false, sp3, "Blitzcrank");
        robo3->SetStatus(80, 10, 2, 5, 3, 5, 10);
        robo3->MakeRangeArea();
        objectArray.emplace_back(robo3);
        infoMenu->InsereBotao(robo3);

        Piloto *piloto3 = new Piloto(robo3, "Maria", pilotoSp3, false, &tileMap);
        piloto3->SetStatus(10, 5, 1, 3, 9, 4, 10);
        objectArray.emplace_back(piloto3);
        infoMenu->InsereBotao(piloto3);
        robo3->InserePiloto(piloto3);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Mario") != characters.robo.end()){
    //Mario
        Sprite sp4("img/roboPreto.png");
        Sprite pilotoSp4("img/pilotoPreto.png");
        Robo *robo4 = new Robo(10, 18, &tileMap, false, sp4, "OptimusPrime");
        robo4->SetStatus(100, 10, 2, 5, 2, 5, 10);
        robo4->MakeRangeArea();
        objectArray.emplace_back(robo4);
        infoMenu->InsereBotao(robo4);

        Piloto *piloto4 = new Piloto(robo4, "Mario", pilotoSp4, false, &tileMap);
        piloto4->SetStatus(10, 5, 1, 3, 4, 4, 10);
        objectArray.emplace_back(piloto4);
        infoMenu->InsereBotao(piloto4);
        robo4->InserePiloto(piloto4);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Jose") != characters.robo.end()){
    //Jose
        Sprite sp5("img/roboAmarelo.png");
        Sprite pilotoSp5("img/pilotoAmarelo.png");
        Robo *robo5 = new Robo(11, 18, &tileMap, false, sp5, "Bamboubi");
        robo5->SetStatus(120, 10, 2, 5, 6, 5, 10);
        robo5->MakeRangeArea();
        objectArray.emplace_back(robo5);
        infoMenu->InsereBotao(robo5);

        Piloto *piloto5 = new Piloto(robo5, "Jose", pilotoSp5, false, &tileMap);
        piloto5->SetStatus(10, 5, 1, 3, 4, 4, 10);
        objectArray.emplace_back(piloto5);
        infoMenu->InsereBotao(piloto5);
        robo5->InserePiloto(piloto5);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Josea") != characters.robo.end()){
    //Josea
        Sprite sp6("img/roboAzul.png");
        Sprite pilotoSp6("img/pilotoAzul.png");
        Robo *robo6 = new Robo(12, 18, &tileMap, false, sp6, "Walle");
        robo6->SetStatus(100, 10, 2, 5, 7, 5, 10);
        robo6->MakeRangeArea();
        objectArray.emplace_back(robo6);
        infoMenu->InsereBotao(robo6);

        Piloto *piloto6 = new Piloto(robo6, "Josea", pilotoSp6, false, &tileMap);
        piloto6->SetStatus(10, 5, 1, 3, 4, 4, 10);
        objectArray.emplace_back(piloto6);
        infoMenu->InsereBotao(piloto6);
        robo6->InserePiloto(piloto6);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Batata") != characters.robo.end()){
    //Batata
        Sprite sp7("img/roboVermelho.png");
        Sprite pilotoSp7("img/pilotoVermelho.png");
        Robo *robo7 = new Robo(13, 18, &tileMap, false, sp7, "Gurren");
        robo7->SetStatus(30, 10, 2, 5, 7, 5, 10);
        robo7->MakeRangeArea();
        objectArray.emplace_back(robo7);
        infoMenu->InsereBotao(robo7);

        Piloto *piloto7 = new Piloto(robo7, "Batata", pilotoSp7, false, &tileMap);
        piloto7->SetStatus(10, 5, 1, 3, 4, 4, 10);
        objectArray.emplace_back(piloto7);
        infoMenu->InsereBotao(piloto7);
        robo7->InserePiloto(piloto7);
    }

    if(find(characters.robo.begin(), characters.robo.end(), "Digglet") != characters.robo.end()){
    //Josea
        Sprite sp8("img/roboMarrom.png");
        Sprite pilotoSp8("img/pilotoMarrom.png");
        Robo *robo8 = new Robo(6, 18, &tileMap, false, sp8, "ApoloBR");
        robo8->SetStatus(150, 2, 2, 5, 7, 5, 10);
        robo8->MakeRangeArea();
        objectArray.emplace_back(robo8);
        infoMenu->InsereBotao(robo8);

        Piloto *piloto8 = new Piloto(robo8, "Digglet", pilotoSp8, false, &tileMap);
        piloto8->SetStatus(10, 5, 1, 3, 4, 4, 10);
        objectArray.emplace_back(piloto8);
        infoMenu->InsereBotao(piloto8);
        robo8->InserePiloto(piloto8);
    }
}
