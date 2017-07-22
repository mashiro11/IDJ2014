#include "../include/Bar.h"

#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Bar::Bar(int points, string frameFile, string fluidFile, GameObject &associated):
    currPoints(points),
    maxPoints(points),
    fluid(fluidFile),
    frame(frameFile),
    associated(associated)
{
    DEBUG_PRINT("Bar::Bar()-inicio");
    box.x = this->associated.box.x;
    box.y = this->associated.box.y;
    fluid.SetPosition(box.x, box.y);
    frame.SetPosition(box.x, box.y);

    maxPoints = currPoints = points;
    box.w = frame.GetWidth();
    box.h = frame.GetHeight();
    refilAuto = false;
    DEBUG_PRINT("Bar::Bar()-fim");
}

bool Bar::Is(ComponentType comp) const{
    return (ComponentType::BAR == comp);
}

void Bar::EarlyUpdate(float dt){
}

void Bar::Update(float dt)
{
    //DEBUG_PRINT("Bar::Update()-inicio");
    if(refilAuto){
        if(currPoints < maxPoints){
            currPoints += refilPace*dt;
            if(currPoints > maxPoints) currPoints = maxPoints;
            fluid.SetClip(0, 0, box.w * (currPoints/maxPoints), box.h);
        }
    }
    //DEBUG_PRINT("Bar::Update()-fim");
}

void Bar::LateUpdate(float dt){
}

/*
bool Bar::IsDead()
{
    if(currPoints <= 0) return true;
    return false;
}
*/

void Bar::Render()
{
    fluid.Render();
    frame.Render();
}

void Bar::SetX(float x){
    box.x = x;
    frame.SetPosition(box.x, box.y);
    fluid.SetPosition(box.x, box.y);
}

void Bar::SetY(float y){
    box.y = y + associated.box.y;
    frame.SetPosition(box.x, box.y);
    fluid.SetPosition(box.x, box.y);
}

void Bar::SetPoints(int points)
{
    if(points > maxPoints){
        currPoints = maxPoints;
    }else{
        currPoints = points;
    }
}

int Bar::GetPoints()
{
    return currPoints;
}

float Bar::GetPercentPoints()
{
    return 100*currPoints/maxPoints;
}

bool Bar::IsFull(){
    if(currPoints == maxPoints){
        return true;
    }
    return false;
}

void Bar::SetRefilAuto(float time){
    this->refilAuto = true;
    this->refilPace = maxPoints/time;
    DEBUG_PRINT("refilPace: " << refilPace);
}

void Bar::SetPosition(float x, float y){
    this->box.x = this->associated.box.x + x;
    this->box.y = this->associated.box.y + y;
    frame.SetPosition(box.x, box.y);
    fluid.SetPosition(box.x, box.y);
}

int Bar::GetX(){
    return box.x;
}

int Bar::GetY(){
    return box.y;
}

#ifdef DEBUG
    #undef DEBUG
#endif

