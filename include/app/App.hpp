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
    Vector2 processing_mouse_click(); // pegar o click do mouse
    void print_move(Tipo tipoPeca, Cor corPeca, int linhaOrigem, int colOrigem, int linhaDestino, int colDestino); // mostrar o os movimentos console



};