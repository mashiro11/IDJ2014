#include "Camera.h"

const int MinX = -100;
const int MaxX = 524;

const int MinY = -100;
const int MaxY = 900;
const int cameraSpeed = 100; //adicionado



Point Camera::pos;
float Camera::speed;
Point Camera::speedP;
GameObject* Camera::focus;

void Camera::Follow (GameObject* newFocus)
{
    //Seta um novo ‘foco’ para a câmera, que é um GameObject a ser seguido por ela.
    focus = newFocus;
}

void Camera::Unfollow ()
{
    //Atribui NULL ao foco.
    focus = NULL;
}

void Camera::Update (float dt)
{
    speed = 1000*dt/4;
    if((InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))  ||
       (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) ||
       (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))    ||
       (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))){
                    focus = NULL;
    }
    if(focus != NULL){
           //centraliza o foco na tela, movimento independe de dt, depende apenas do tamanho da tela
           // float angulo = atan2(focus->box.y - pos.y,focus->box.x - pos.x);
            float angulo = M_PI*45/180;

            if(pos.x > focus->box.RectCenterX() - Game::GetInstance().GetWindowWidth()/2 + 5){
                pos.x -= cos(angulo)*speed/1.2;
            }else if(pos.x < focus->box.RectCenterX() - Game::GetInstance().GetWindowWidth()/2 - 5){
                pos.x += cos(angulo)*speed/1.2;
            }
            if(pos.y > focus->box.RectCenterY() - Game::GetInstance().GetWindowHeight()/2 + 5){
                pos.y -= sin(angulo)*speed/1.2;
            }else if(pos.y < focus->box.RectCenterY() - Game::GetInstance().GetWindowHeight()/2 - 5){
                pos.y += sin(angulo)*speed/1.2;
            }
            if((pos.x < focus->box.RectCenterX() - Game::GetInstance().GetWindowWidth()/2 + 5)&&
               (pos.x > focus->box.RectCenterX() - Game::GetInstance().GetWindowWidth()/2 - 5)&&
               (pos.y < focus->box.RectCenterY() - Game::GetInstance().GetWindowHeight()/2 + 5)&&
               (pos.y > focus->box.RectCenterY() - Game::GetInstance().GetWindowHeight()/2 - 5)){
                focus = NULL;
            }
    }else{
        speed = 1/(dt*10);//arbitrário
        if( InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) == true ){
                pos.y -= speed;
        }
        if( InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) == true ){
                pos.y += speed;
        }
        if( InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY) == true ){
                pos.x -= speed;
        }
        if( InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) == true ){
                pos.x += speed;
        }
    }
//    if(pos.x > MaxX) pos.x = MaxX;
//    if(pos.x < MinX) pos.x = MinX;
//    if(pos.y > MaxY) pos.y = MaxY;
//    if(pos.y < MinY) pos.y = MinY;
}

GameObject* Camera::GetFocus()
{
    return focus;
}

float Camera::CameraCenterX()
{
    return Game::GetInstance().GetWindowWidth()/2;
}

float Camera::CameraCenterY()
{
    return Game::GetInstance().GetWindowHeight()/2;
}

Point Camera::CameraCenter()
{
    return Point(CameraCenterX(), CameraCenterY());
}
