#include <stdio.h>

#include "Game.h"
#include "TitleState.h"

int main(int argc, char** argv){
    Game novoJogo("Jogo teste", 1024, 600);
    novoJogo.Push(new TitleState);
    novoJogo.Run();
    return 0;
}
