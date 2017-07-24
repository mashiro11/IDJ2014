#ifndef ROBO_H
#define ROBO_H

#include <iostream>
#include <string>

#include "Camera.h"
#include "resources_path.h"
#include "Bar.h"
#include "Walkable.h"

using std::string;

#define ROBO_SHEET_LINES        4
#define ROBO_SHEET_FRAMES       4
#define ROBO_SHEET_FRAME_TIME   4.0*1.0/24.0

class Robo: public GameObject{
public:
    Robo(float x, float y, string file);
    ~Robo();
    void Update(float dt);
    void Render();
    bool Is(string type);
    bool IsDead();
    void NotifyCollision(GameObject& other);


    bool selected;
protected:
private:
    Sprite sp;
};

#endif // ROBO_H
