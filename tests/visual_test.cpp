#include <raylib.h>
#include "../include/core/Tabuleiro.hpp"
#include "../include/UI/Interface.hpp"

int main() {

    const int larguraTela = 1200; 
    const int alturaTela = 800;
    

    InitWindow(larguraTela, alturaTela, "Teste Visual - Xadrez");
    SetTargetFPS(60);


    Tab* tabuleiro = new Tab();
    Interface minhaInterface(100, 800); 

    while (!WindowShouldClose()) {
        
        BeginDrawing();
            ClearBackground(BROWN); 


            minhaInterface.DrawTab(tabuleiro);

        EndDrawing();
    }


    CloseWindow();

    return 0;
}