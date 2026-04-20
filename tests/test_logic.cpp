#include <raylib.h>
#include "../include/core/Tabuleiro.hpp" // Ajuste o nome do arquivo .hpp se for diferente
#include "../include/UI/Interface.hpp"

int main() {
    // 1. Inicialização da Janela da Raylib
    const int larguraTela = 1200; // Espaço extra para menus, se quiser
    const int alturaTela = 800;
    

    InitWindow(larguraTela, alturaTela, "Teste Visual - Xadrez");
    SetTargetFPS(60);

    
    Tab meuTabuleiroLogico;
    
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