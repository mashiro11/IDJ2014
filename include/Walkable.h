#ifndef WALKABLE_H
#define WALKABLE_H

#include <iostream>

#include "GameObject.h"
#include "InputManager.h"

using std::cout;
using std::endl;

class Walkable: public Component
{
    public:
        Walkable(GameObject& associated);
        void Update(float dt);
		bool Is(ComponentType type) const;
		void Render(void){};
		void EarlyUpdate(float dt);
		void LateUpdate(float dt);
        ~Walkable();

    protected:

    private:
        GameObject& associated;
        bool controlable;
        bool selected;
};

#endif // WALKABLE_H
