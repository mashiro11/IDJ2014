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
        ~Walkable();
        void Update(float dt);
		bool Is(ComponentType type) const;
		void Render(){};
		void EarlyUpdate(float dt);
		void LateUpdate(float dt);
		void SetControlable(bool control);

		int PixelToGrid(int x, int tileW);
        void AddPath(int x, int y);

    protected:

    private:
        GameObject& associated;
        bool controlable;
        bool selected;
        Point destination;
        vector<Point*> pathPoints;
};

#endif // WALKABLE_H
