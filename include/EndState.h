#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "StateData.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"

class EndState : public State
{
    public:
        EndState(StateData stateData);
        void Update(float dt);
        void Render();
        void StateMachine();

    protected:
    private:
        void Input();
        Sprite bg;
        Music music;
        Text instruction;
        Timer cronometro;
};

#endif // ENDSTATE_H
