#pragma once

#include <raylib.h>
#include "../core/Tabuleiro.hpp"
#include "../UI/Interface.hpp"

class App{

    private:
        Tab* tabuleiro;
        Interface* interface;

    public:
        App();
        ~App();

        void app_loop(); // loop com a interface principal
        void processing_mouse_click(); // pegar o click do mouse
        void print_move(); // mostrar o os movimentos console



}