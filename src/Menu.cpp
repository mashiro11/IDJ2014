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
    menuType = VERTICAL;
    absoluteX = box.x = 0;
    absoluteY = box.y = 0;
    espacamento = 0;
    centered = false;
    box.w = 0;
    box.h = 0;
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
}

void Menu::HandleInputs(){
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)){
        for(int i = 0; i<options.size(); i++){
            if(options[i]->IsInside(InputManager::GetInstance().GetMouseX() + Camera::pos.x,
                                    InputManager::GetInstance().GetMouseY() + Camera::pos.y)){
                gotInput = true;
                selectedOption = i;
            }
        }
    }
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
    _organizeOptions();
//    Sprite selectedButton;
//    selectedButton.SetFile(BUTTON_NOT_SELECTED);// = Sprite(BUTTON_NOT_SELECTED);
//    buttons.push_back(selectedButton);
}

void Menu::RemoveMenuOption(int option){
    options.erase(options.begin() + option);
    _organizeOptions();
//    buttons.erase(buttons.begin() + option);
//    options[currentOption]->SetColor(TEXT_BLACK);
}

void Menu::SetPosition(float x, float y, bool centered){
    absoluteX = x;
    absoluteY = y;
    this->centered = centered;
    _organizeOptions();
}

void Menu::SetDirection(MenuType mt, float esp){
    menuType = mt;
    espacamento = esp;
    box.w = 0;
    box.h = 0;
    _organizeOptions();
}
/**
 *  A função _organizeOptions é responsável por rearranjar as opções dentro do menu
 *  de acordo com a orientação, VERTICAL ou HORIZONTAL, escolhida para o Menu.
*/
void Menu::_organizeOptions(){
    DEBUG_PRINT("Posicao antes: " << box.x << "x" << box.y)
    box.x = absoluteX;
    box.y = absoluteY;
    DEBUG_PRINT("Posicao depois: " << box.x << "x" << box.y)
    switch(menuType){
        case VERTICAL:
            box.h = (options.size()*(options[0]->GetHeigth() + espacamento) - espacamento);
            for(unsigned int i = 0; i < options.size(); i++){
                if(options[i]->GetWidth() > box.w)
                    box.w = options[i]->GetWidth();
            }
            if(centered){
                box.x -= box.w/2;
                box.y -= box.h/2;
            }
            for(unsigned int i = 0; i < options.size(); i++){
                this->options[i]->SetPos(box.x, box.y + (options[0]->GetHeigth()+espacamento)*i );
            }
            break;
        case HORIZONTAL:
            box.h = options[0]->GetHeigth();
            box.w = (options.size()-1)*espacamento;
            for(unsigned int i = 0; i < options.size(); i++){
                box.w += options[i]->GetWidth();
            }
            if(centered){
                box.x -= box.w/2;
                box.y -= box.h/2;
            }
            int sum = 0;
            for(unsigned int i = 0; i < options.size(); i++){
                this->options[i]->SetPos(box.x + sum, box.y);
                sum += options[i]->GetWidth() + espacamento;
            }
            break;
    }
    DEBUG_PRINT("Menu::_organizeOptions()");
    DEBUG_PRINT(" Menu: posicao(" << box.x << "x" << box.y << ")")
    DEBUG_PRINT(" Menu: dimens.(" << box.w << "x" << box.h << ")")
    DEBUG_PRINT(" Primeira Opcao: posicao box(" << options[0]->GetPosX() << "," << options[0]->GetPosY() << ")")
    DEBUG_PRINT(" Primeira Opcao: dimens. box(" << options[0]->GetWidth() << "x" << options[0]->GetHeigth() << ")")
}
#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
