#include "Character.h"

Character::Character()
{

}

Character::~Character()
{
    //dtor
}

void Character::Render(int cameraX, int cameraY)
{
    sp.Render(box.x - cameraX, box.y - cameraY);
}


