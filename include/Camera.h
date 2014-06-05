#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "GameObject.h"
#include "Game.h"//antiga GameBase -> Game (T4)
#include "Point.h"
#include "InputManager.h"

class Camera
{
    public:
        //CAMERA();
        //~CAMERA();
        static Point pos;
        static float speed;
        static Point speedP;
        static void Follow (GameObject* newFocus);
        static void Unfollow ();
        static void Update (float dt);
        static GameObject* GetFocus();
        static float CameraCenterX();
        static float CameraCenterY();
        static Point CameraCenter();

    protected:
        /* vazio */
    private:
        static GameObject* focus;
};

#endif // CAMERA_H
