#include "../include/Bar.h"

#define DEBUG
#ifdef DEBUG
    #define DEBUG_PRINT(x) do{ cout << x <<  endl; }while(0)
#else
    #define DEBUG_PRINT(x)
#endif // DEBUG

Bar::Bar(int points, GameObject &associated):
    currPoints(points),
    maxPoints(points),
    fluid(BARRA_VIDA),
    frame(BARRA_VIDA_MOLDURA),
    associated(associated)
{
    DEBUG_PRINT("Bar::Bar()-inicio");
    box.x = this->associated.box.x;
    box.y = this->associated.box.y;
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
    if(refilAuto){
       timer.Update(dt);
       if(timer.TimeUp() && currPoints < maxPoints){
            timer.Restart();
            currPoints += refilPace;
            if(currPoints > maxPoints) currPoints = maxPoints;
            fluid.SetClip(0, 0, box.w * ((float)currPoints/maxPoints), box.h);
       }
    }
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
}

void Bar::SetY(float y){
    box.y = y + associated.box.y;
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
    if(currPoints/maxPoints == 1){
        return true;
    }
    return false;
}

void Bar::SetRefilAuto(int refilPace, int time){
    this->refilAuto = true;
    this->refilPace = refilPace;
    this->timer.Set(time);
}

void Bar::SetPosition(float x, float y){
    if((int)x)this->box.x = this->associated.box.x + x;
    if((int)y)this->box.y = this->associated.box.y + y;
}

#ifdef DEBUG
    #undef DEBUG
#endif

