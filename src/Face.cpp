#include "Face.h"

const int BONUS_FACTOR = 10;
const int DAMAGE = 10;

Face::Face(float mouseX, float mouseY) : sp("images/penguinface.png")
{
    //aqui coloca a funcao random!!
    float angle = rand()%360 * M_PI/180;
    float circX = cos(angle)*200;
    float circY = sin(angle)*200;

    circX += mouseX;
    circY += mouseY;

    box.w = sp.GetWidth();
    box.h = sp.GetHeight();

    box.SetRectCenterX(circX);
    box.SetRectCenterY(circY);
    rotation = 0;
}

Face::~Face()
{
    //dtor
}

void Face::Render(int cameraX, int cameraY)//linha alaterada
{
    sp.Render(box.x - cameraX, box.y - cameraY);//linha alterada
}

void Face::Update(float dt)
{
        if( InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT) == true ){
                if(InputManager::GetInstance().IsMouseInside( box ) ) {
                    // Aplica dano
                    #ifdef DEBUG
                    cout << "HP antes: " << GetHitPoint() << endl;
                    #endif

                    int hit = rand() % BONUS_FACTOR + DAMAGE;
                    Damage(hit);

                    #ifdef DEBUG
                    cout << "Dano: " << hit << endl;
                    cout << "HP depois: " << GetHitPoint() << endl;
                    #endif // DEBUG

                    // Sai do loop (só queremos acertar um)
                }
            }
            if( InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT) == true ){
                if(InputManager::GetInstance().IsMouseInside( box ) ) {
                    Camera::Follow(this);
                }
            }
}

void Face::Damage(int damage)
{
    hitpoints -= damage;
}

bool Face::IsDead()
{
    if(hitpoints <= 0) return true;
    return false;
}

void Face::NotifyCollision(GameObject& other)
{

}

bool Face::Is(string type)
{
    if(type == "Face") return true;
    return false;
}

int Face::GetHitPoint()
{
    return hitpoints;
}
