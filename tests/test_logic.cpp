#include <raylib.h>
#include "../include/core/Tabuleiro.hpp"
#include "../include/UI/Interface.hpp"

int main() {

    const int larguraTela = 1200; 
    const int alturaTela = 800;
    

    InitWindow(larguraTela, alturaTela, "Teste Visual - Xadrez");
    SetTargetFPS(60);

    
    Tab* meuTabuleiroLogico;
    
    Interface minhaInterface(100, 800); 

    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(DARKGRAY); 


        minhaInterface.DrawTab(meuTabuleiroLogico);

        EndDrawing();
    }


    CloseWindow();

    return 0;
}