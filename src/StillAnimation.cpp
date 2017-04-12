#include "../include/StillAnimation.h"

StillAnimation::StillAnimation (float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends):
    sp(sprite)
{
    this->timeLimit = timeLimit;
    oneTimeOnly = ends;
    box.w = sp.GetWidth()/sp.GetFrameCount();
    box.h = sp.GetHeight();
    box.SetRectCenterX(x);
    box.SetRectCenterY(y);
}

void StillAnimation::Update (float dt)
{
    endTimer.Update(dt);
    sp.Update(dt);
}

void StillAnimation::Render (int cameraX, int cameraY)
{
    //cout << "Estou sendo renderizado e camera:" << cameraX << "-" << cameraY << endl;
    sp.Render(box.x - cameraX, box.y - cameraY);
}

bool StillAnimation::IsDead ()
{
    //cout << "cheguei aqui" << endl;
    if( oneTimeOnly == true && endTimer.Get() >= timeLimit) return true;
    return false;

}

bool StillAnimation::Is(string type)
{
    if(type == "StillAnimation") return true;
    return false;
}

void StillAnimation::SetX(float x)
{
    box.SetRectCenterX(x);
}

void  StillAnimation::SetY(float y)
{
    box.SetRectCenterY(y);
}
