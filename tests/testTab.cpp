#include <iostream>
#include "../include/UI/Interface.hpp"

int main() {
    Tab* tabuleiro_logico = new Tab();
    InitWindow(1200, 800, "Xadrez Teste");
    
    Interface teste = Interface(100,200);

    while(!WindowShouldClose()){
        BeginDrawing();
            teste.DrawTab(tabuleiro_logico);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;



}