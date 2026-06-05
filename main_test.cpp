#include <iostream>
#include "../include/app/App.hpp"
using namespace std;

int main(){

    InitWindow(1200, 800, "Xadrez ");
    SetTargetFPS(60);
    App app_teste;

    app_teste.app_loop();

    CloseWindow();
    
    return 0;
}