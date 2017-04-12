#include "../include/Menu.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG

Menu::Menu(){
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
    AddMenuOption("JOGAR");
    AddMenuOption("Opcoes");
    AddMenuOption("Sair");
    DEBUG_PRINT("Posicao box(" << options[0]->GetPosX() << "," << options[0]->GetPosY() << ")")
    DEBUG_PRINT("Size box(" << options[0]->GetWidth() << "," << options[0]->GetHeigth() << ")")

    newLineSpace = options[0]->GetWidth();//no minimo
    selectedOption = -1;
}
Menu::~Menu()
{
    //dtor
}

//
//Menu::Menu(float posX, float posY, int newLineSpace){
//    //ctor
////    this->sp.SetFile(BG_MENU);// = Sprite(BG_MENU);
//    this->box.x = posX;
//    this->box.y = posY;
////    this->buttonSelected.SetFile(BUTTON_SELECTED);// = Sprite(BUTTON_SELECTED);
//    this->newLineSpace = newLineSpace;
//    this->currentOption = 0;
//    this->lastOption = -1;
//    this->gotInput = false;
//}
//
//
//void Menu::Load(){
////    this->sp.Load();
////    this->buttonSelected.Load();
////    for(unsigned int i = 0; i < buttons.size(); i++){
////        this->buttons[i].Load();
////    }
//}
//
void Menu::Update(float dt){
    HandleInputs();
    cronometro.Update(dt);
    if( cronometro.Get() > 2 ) cronometro.Restart();
////    this->buttonSelected.Update(dt);
////	// Menu Select
////    if(gotInput){
////        gotInput = false;
//////        options[currentOption]->SetColor(TEXT_BLACK);
////        if(lastOption != -1){
////            options[lastOption]->SetColor(TEXT_WHITE);
////        }
////    }
}
//
void Menu::HandleInputs(){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        for(int i = 0; i<options.size(); i++){
            if(options[i]->IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                    InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                cout << "IsInside:" << options[i]->GetText() << endl;
                gotInput = true;
                selectedOption = i;
            }
        }
    }
//    if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
//        selectedOption = currentOption;
//	}
//	// Menu Input
//	if(InputManager::GetInstance().KeyPress(UP_ARROW_KEY)){
//		gotInput = true;
//		lastOption = currentOption;
//		this->currentOption--;
//		if(this->currentOption < MENU_MIN_t)
//			this->currentOption = options.size() - 1;
//	}
//
//	if(InputManager::GetInstance().KeyPress(DOWN_ARROW_KEY)){
//		gotInput = true;
//		lastOption = currentOption;
//		this->currentOption++;
//		if(this->currentOption > options.size()-1)
//			this->currentOption = MENU_MIN_t;
//	}
}

void Menu::Render(int x, int y){
    if(cronometro.Get() < 2 && cronometro.Get() > 0.5){
        //this->sp.Render(box.x - (this->sp.GetWidth()/2), this->box.y - (this->sp.GetHeight()/(buttons.size() + 1)));
//        for(unsigned int i = 0; i < buttons.size(); i++){
//            this->buttons[i].Render(box.x - (buttons[i].GetWidth()/2), box.y - BUTTON_OFFSET_Y +(newLineSpace*i));
//        }
        //this->buttonSelected.Render(box.x - (buttonSelected.GetWidth()/2), box.y - BUTTON_OFFSET_Y +(newLineSpace*currentOption));
        //this->buttonSelected.FadeToggle(true);
        //DEBUG_PRINT("alpha: " << this->buttonSelected.GetAlpha())

        for(unsigned int i = 0; i < options.size(); i++){
            this->options[i]->Render(0, 0);
        }
    }
}
//
//bool Menu::IsDead(){
//    return false;
//}
//
//void Menu::NotifyCollision(GameObject* other){
//}
//
//bool Menu::Is(std::string type){
//    return MENU_TYPE;
//}
//
//int Menu::GetLayer(){
//    return 0;
//}
//
//int Menu::GetSublayer(){
//    return 0;
//}
//bool Menu::GetSelection(){
//    if(selectedOption != -1) return true;
//    else return false;
//}
//
int Menu::GetSelectedOption(){
    int selected = selectedOption;
    selectedOption = -1;
    return selected;
}

void Menu::AddMenuOption(string newOpt){

    options.push_back(new Text(MENU_TEXT_FONT, MENU_TEXT_FONT_SIZE, Text::TEXT_BLENDED, newOpt) );
    options.back()->SetPos(box.x, box.y + newLineSpace*(options.size()-1));

//    Sprite selectedButton;
//    selectedButton.SetFile(BUTTON_NOT_SELECTED);// = Sprite(BUTTON_NOT_SELECTED);
//    buttons.push_back(selectedButton);
}

//void Menu::RemoveMenuOption(int option){
//    options.erase(options.begin() + option);
//    buttons.erase(buttons.begin() + option);
//
//    for(int i = 0; i < options.size(); i++){
//        this->options[i]->SetPos(this->box.x,this->box.y + newLineSpace*i,true,false);
//    }
//    options[currentOption]->SetColor(TEXT_BLACK);
//}
//
void Menu::SetPosition(float x, float y){
    box.x = x;
    box.y = y;
    OrganizeOptions();
}

void Menu::OrganizeOptions(){
    for(unsigned int i = 0; i < options.size(); i++){
        this->options[i]->SetPos(box.x, box.y + newLineSpace*i);
    }
}
#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
