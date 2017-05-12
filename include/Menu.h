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

#include "resources_path.h"
#define MENU_MIN_t 0
#define MENU_TYPE   "Menu"
#define MENU_TEXT_FONT_SIZE     50

#define BUTTON_OFFSET_Y         5

enum MenuType{
    HORIZONTAL = 0,
    VERTICAL
};

enum PositionAlign{
    LEFT_ALIGN = 0,
    CENTERED,
    RIGHT_ALIGN
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
    void SetDirection(MenuType mt, float esp = 0);
    void SetPosition(float x, float y, bool centered = false);


protected:

private:
    void _organizeOptions();
//    Text start;
//    Text options;
//    Text quit;
    int selectedOption;
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
    bool centered;
};

#endif // MENU_H
