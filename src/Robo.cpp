#include "../include/Robo.h"

Robo::Robo(float x, float y, TileMap* mapRef, bool lider, string spritePath, string nome)
{

    tileNumber = 1;
    //sp.SetScaleX((float) tileNumber);
    //sp.SetScaleY((float) tileNumber);
    sp.Open(spritePath);
    sp.SetSpriteSheet(4, 4);
    sp.SetAnimation(0, 4);
    sp.SetFrameTime(4.0 * 1.0/24.0);


    this->lider = lider;
    this->nome = nome;

    mapReference = mapRef;
    box.h = sp.GetHeight();
    box.w = sp.GetWidth();
    box.SetRectCenterX( mapReference->MapPositionToPixelPosition(x,tileNumber) );
    box.SetRectCenterY( mapReference->MapPositionToPixelPosition(y,tileNumber) );
    currentPosition.SetPoint( x, y );

    this->rotation = 0;

    allyPosition = FRONT;
    charState = REPOUSO;
    menuAberto = false;
    //cout << "(" << x << ", " << y << ")" << endl;
    //mapReference->At(x, y).state = ALLY;
    //mapReference->At(x, y).occuper = this;

    mapReference->SetTileState(currentPosition, ALLY, tileNumber);
    mapReference->SetTileOccuper(currentPosition, this, tileNumber);
}

Robo::~Robo()
{
     mapReference->At( mapReference->PixelPositionToMapPosition( box.RectCenterX() ),
                       mapReference->PixelPositionToMapPosition( box.RectCenterY() ) ).state = FREE;
}

void Robo::Update(float dt)
{

    if(charState != INATIVO){
        Ally::Update(dt);
        //barraCooldown.Update(dt);
        //barraCooldown.SetX(box.RectCenterX());
        //barraCooldown.SetY(box.RectCenterY());
    }
    /*if(IsDead() == true){
        cout << this->nome <<": Fui destruido!! Noooooooo.... D: " << endl;
        mapReference->At( currentPosition.x, currentPosition.y ).state = FREE;
        mapReference->At( currentPosition.x , currentPosition.y ).occuper = NULL;

    }

    vida.Update();
    vida.SetX(box.RectCenterX());
    vida.SetY(box.RectCenterY());
    */
}

void Robo::Render(){
    sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y);
    /*
    if(menuAberto){
        int offSet = 100;
        int angulo = 90;
        for(int i = 0; i < buttonArray.size(); i++){
            buttonArray[i].SetX(box.RectCenterX() + cos(angulo*M_PI/180)*offSet);
            buttonArray[i].SetY(box.RectCenterY() - 20 + sin(angulo*M_PI/180)*offSet);
            buttonArray[i].Render(cameraX,cameraY);
            angulo += 90;
        }
    }else{
        barraCooldown.Render(cameraX, cameraY);
        vida.Render(cameraX, cameraY);
    }
    */
}

bool Robo::Is(string type){
    if(type == "Robo" || type == "Ally"){
        return true;
    }
    return false;
}

bool Robo::Ejetar()
{
    /*
    Piloto* piloto = pilotoArray.back();
    if(piloto->Ejetar() == true){
        pilotoArray.pop_back();
        if(pilotoArray.size() == 0){
            this->charState = INATIVO;
        }else{
            this->charState = REPOUSO;
        }
        return true;
    }
    */
    return false;
}

void Robo::InserePiloto(Piloto *piloto)
{
    //pilotoArray.push_back(piloto);
}


void Robo::Morrer()
{
    /*
    for(int i = 0; i < pilotoArray.size(); i++){
        pilotoArray[i]->Morrer();
    }*/
}

bool Robo::Embarcar(Ally *alvo)
{
    /*
    if(pilotoArray.size() < 2){
        if(charState == INATIVO){
            charState = REPOUSO;
        }
        Piloto* piloto = (Piloto*) alvo;
        pilotoArray.push_back(piloto);
        return true;
    }else{
        return false;
    }*/
}

void Robo::Danificar(float dano)
{
    /*
    Sprite hit(HIT);
    Game::GetInstance().GetCurrentState().AddObject(new StillAnimation(box.RectCenterX() + 10,
                                                                       box.RectCenterY() - 25, rotation, hit, 0.5, true));
    int vidaNova = vida.GetVida();
    vidaNova -= dano - defesa/10;
    vida.SetVida(vidaNova);
    */
}
