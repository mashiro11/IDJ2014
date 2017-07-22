#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>

#include "GameObject.h"
#include "Camera.h"
#include "Collision.h"

using std::vector;
using std::shared_ptr;
//using std::unique_ptr;

class State
{
    public:
        State();
        virtual ~State();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual void AddObject(GameObject* object);
        bool RequestedDelete();
        bool RequestedQuit();

    protected:
        bool requestDelete;
        bool requestQuit;
        virtual void UpdateArray(float dt);
        vector<shared_ptr<GameObject>> objectArray;
        bool wait;
    private:
};

#endif // STATE_H
