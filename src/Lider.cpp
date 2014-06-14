//#include "Lider.h"

//Lider* Lider::lider;

//Lider::Lider(float x, float y, float defesa, float ataque, int speed, int distance, float vidaMaxima,
//             int coolDown, TileMap* mapRef, int range)
//{
//    //ver a proporção do personagem em relaçao ao tile do mundopara aplicar na posicao certa
////    sp.SetScaleX((float) 2);
////    sp.SetScaleY((float) 2);

//    //SetFrameCount
//    //SetFrameTime

//    vida.Open(this);
//    sp.SetSpriteSheet(4, 4);
//    sp.SetAnimation(0, 4);
//    sp.SetFrameTime(4.0 * 1.0/24.0);
//#ifdef ANDRE
//    sp.Open("C:/Users/Andre/Desktop/DefesaMitica-2entrega/DefessaMitica2/images/img/robot2iceaxe.png");
//#endif
//#ifdef MASHIRO
//    sp.Open("images/img/robot2iceaxe.png");
//#endif

//    mapReference = mapRef;
//    box.h = sp.GetHeight();
//    box.w = sp.GetWidth();
//    box.SetRectCenterX( MapPositionToPixelPosition(x) );
//    box.SetRectCenterY( MapPositionToPixelPosition(y) );

//    this->defesa = defesa;
//    this->ataque = ataque;
//    this->vidaMaxima = vidaMaxima;
//    this->vidaAtual = vidaMaxima;
//    this->range = range;
//    this->distance = distance;
//    this->speed = speed;
//    this->rotation = 0;
//    this->coolDown = coolDown;
//    this->rotation = 0;

//    allyPosition = FRONT;
//    allyState = REPOUSO;
//    menuAberto = false;

//}

//Lider::~Lider(){
//    lider = NULL;
//}

//void Lider::Update(float dt)
//{

//    UpdateAlly(dt);
//    vida.Update();
//    vida.SetX(box.RectCenterX());
//    vida.SetY(box.RectCenterY());

//}

//void Lider::Render(int cameraX, int cameraY){
//    sp.Render(box.x - cameraX, box.y - cameraY);
//    if(menuAberto){
//        int offSet = 100;
//        int angulo = 90;
//        for(int i = 0; i < buttonArray.size(); i++){
//            buttonArray[i].SetX(box.RectCenterX() + cos(angulo*M_PI/180)*offSet);
//            buttonArray[i].SetY(box.RectCenterY() - 20 + sin(angulo*M_PI/180)*offSet);
//            buttonArray[i].Render(cameraX,cameraY);
//            angulo += 90;
//        }
//    }else{
//        vida.Render(cameraX, cameraY);
//    }
//}

//bool Lider::Is(string type){
//    if(type == "Lider"){
//        return true;
//    }
//    return false;
//}

//void Lider::Ejetar()
//{
//    /*
//    cout << "AQUI" << endl;
//    cout << "AQUI" << endl;
//    cout << "AQUI" << endl;
//    cout << "AQUI" << endl;
//    cout << "AQUI" << endl;
//    cout << "AQUI" << endl;
//    cout << "AQUI" << endl;
//    pilotoArray.pop_back();
//    if(pilotoArray.size() == 0){
//        allyState = INATIVO;
//    }*/
//}

