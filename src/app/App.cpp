#include <iostream>
#include <raylib.h>
#include "../../include/app/App.hpp"


App::App(){
    this->tabuleiro = nullptr;
    this->interface = nullptr;

}

/*Loop do jogo*/
void App::app_loop(){
    this->currentState = GameState::MENU;

    InitWindow(1200,800, "Xadrez");
    SetTargetFPS(60);

    if (this->tabuleiro == nullptr) {
        this->tabuleiro = new Tab();
    }
    
    if (this->interface == nullptr) {
        this->interface = new Interface(100, 200);
    }
    
    Tab* tabuleiro_logico = this->tabuleiro;
    Piece* pecaSelecionada = nullptr; 

    Cor corVencedora; 

    while(!WindowShouldClose()){       
        if (currentState == MENU){
            if (IsKeyPressed(KEY_ENTER)) {
                this->currentState = GameState::PLAYING;
            }
        }

        if (currentState == PLAYING) {
            
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 clickPos = App::processing_mouse_click(); 
                
                if (pecaSelecionada == nullptr) {
            
                    Piece* p = tabuleiro_logico->getPiece(clickPos.y, clickPos.x); 
                    
                    if (p != nullptr) {
                        pecaSelecionada = p;
                    }
                } else {
                    int startX = pecaSelecionada->GetX(); 
                    int startY = pecaSelecionada->GetY(); 

                    Cor corPeca = pecaSelecionada->getColor();
                    Tipo tipoPeca = pecaSelecionada->getType(); 

                    
                    bool moveu = tabuleiro_logico->MovePiece(startX, startY, clickPos.y, clickPos.x);

                    pecaSelecionada = nullptr;

                    if (moveu) {
                        print_move(tipoPeca, corPeca, startY, startX, clickPos.y, clickPos.x);

                        if (tabuleiro_logico->IsCheckmate(tabuleiro_logico->GetTurnoAtual())) {
                            currentState = GAME_OVER;
                            corVencedora = (tabuleiro_logico->GetTurnoAtual() == Cor::Black) ? Cor::White : Cor::Black;
                        }
                    }
                }
            }
            
        } else if (this->currentState == GameState::GAME_OVER) {
            
            if (IsKeyPressed(KEY_ENTER)) {
                delete this->tabuleiro;          
                this->tabuleiro = new Tab();     
                tabuleiro_logico = this->tabuleiro; 
                currentState = PLAYING;
            }
        }


        BeginDrawing();
            ClearBackground(BROWN);
            if (this->currentState == MENU){
                this->interface->DrawBeginWindow();
            }

            if (currentState == PLAYING) {
                interface->DrawTab(tabuleiro_logico);
                if (pecaSelecionada != nullptr){ interface->ShowPossibleMoves(pecaSelecionada,tabuleiro_logico); }
            } else if (currentState == GAME_OVER) {
                interface->DrawGameOverScreen(corVencedora);
            }
            
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

    int rawX = GetMouseX() - 200; 
    int rawY = GetMouseY();

    if (rawX < 0) return Vector2{-1.0f, -1.0f};

    int x = rawX / 100;
    int y = rawY / 100;

    if (x > 7 || x < 0 || y > 7 || y < 0) return Vector2{-1.0f, -1.0f};
    return Vector2{(float) x, (float) y};
}

App::~App() {
    if (this->tabuleiro != nullptr) {
        delete this->tabuleiro;
    }
    if (this->interface != nullptr) {
        delete this->interface;
    }
}