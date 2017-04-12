#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>

#include "Sprite.h"
#include "Text.h"
#include "Camera.h"
#include "InputManager.h"
#include "Timer.h"
#include "Rect.h"

#define BG_MENU "img/menuProvisorio.png"
#define MENU_MIN_t 0

#define MENU_TYPE   "Menu"

#define MENU_TEXT_FONT          "images/font/NEON____.TTF"
#define MENU_TEXT_FONT_SIZE     50
#define BUTTON_SELECTED         "img/buttonselected.png"
#define BUTTON_NOT_SELECTED     "img/buttonnotselected.png"
#define BUTTON_OFFSET_Y         5

enum MenuType{
    HORIZONTAL = 0,
    VERTICAL
};

class Menu//: public GameObject
{
public:
    Menu();
    ~Menu();

//    Menu(float posX, float posY, int newLineSpace);
//    void Load();
    void Update(float dt);
    void Render(int x = 0, int y = 0);
//    bool IsDead();
//    void NotifyCollision(GameObject* other);
//    bool Is(std::string type);
//
//    bool GetSelection();
    int GetSelectedOption();
    void AddMenuOption(string newOpt);
    void RemoveMenuOption(int option);
    void SetType(MenuType mt);
    void SetPosition(float x, float y, bool centered = false);
    void SetSpacement(float esp);


protected:

private:
    void OrganizeOptions(bool centered);
//    Text start;
//    Text options;
//    Text quit;
    int selectedOption;
    int safeSpace;
//    int currentOption;
//    int lastOption;
//    int selectedOption;
//    Sprite buttonSelected;
    std::vector<Text*> options;
//    std::vector<Sprite> buttons;
    Timer cronometro;
    bool gotInput;
    void HandleInputs();
    Rect box;
    MenuType menuType;
    float absoluteX,absoluteY, espacamento;
};

#endif // MENU_H
