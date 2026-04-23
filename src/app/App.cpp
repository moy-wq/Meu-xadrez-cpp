#include <iostream>
#include <raylib.h>
#include "../../include/app/App.hpp"


App::App(){
    this->tabuleiro = new Tab();
    this->interface = new Interface(100,800);

}

/*Loop do jogo*/
void App::app_loop(){ // incompleto
    Tab* tabuleiro_logico = this->tabuleiro;
    while(!WindowShouldClose()){
        
        Vector2 Mouse_Pos = App::processing_mouse_click();




        BeginDrawing();
            interface->DrawTab(tabuleiro_logico);
        EndDrawing();

        
    }
}

/*mostra os movimentos no terminal*/
void App::print_move(Tipo tipoPeca, Cor corPeca, int linhaOrigem, int colOrigem, int linhaDestino, int colDestino){
    char Letra_origin = 'A' + colOrigem;
    char Letra_Destino = 'A' + colDestino;

    linhaOrigem++;
    linhaDestino++;

    std::string cor_peca;
    if (corPeca == Cor::Black) cor_peca = "preto";
    else cor_peca = "branco";
    
    std::string nomePeca;
    switch (tipoPeca) {
        case Tipo::PEAO:   nomePeca = "Peao"; break;
        case Tipo::TORRE:  nomePeca = "Torre"; break;
        case Tipo::CAVALO: nomePeca = "Cavalo"; break;
        case Tipo::BISPO:  nomePeca = "Bispo"; break;
        case Tipo::RAINHA: nomePeca = "Rainha"; break;
        case Tipo::REI:    nomePeca = "Rei"; break;
        default:           nomePeca = "Peca Desconhecida"; break;
    }

    std::cout << "[LOG] " << nomePeca << " " << cor_peca
              << " moveu de " << Letra_origin << linhaOrigem 
              << " para " << Letra_Destino << linhaDestino << std::endl;


}


/*conversão para o formato da matriz (tabuleiro)*/
Vector2 App::processing_mouse_click(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        int x = GetMouseX();
        int y = GetMouseY();           
                
            x /=100;
            y = 7 - (y / 100); 

        if (x > 8 || x < 0 || y > 8 || y < 0) return Vector2{-1.0f, -1.0f};
        return Vector2{(float) x, (float) y};
    }



    

}
