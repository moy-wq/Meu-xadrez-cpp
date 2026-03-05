#include "../../include/core/Tabuleiro.hpp"
#include <iostream>



Piece* Tab::getPiece(int x, int y){
    if (y > 0 && y < 8 && x > 0 && y < 8){
        return matriz[x][y];
    }
} //Localização da peça
bool Tab::MovePiece(int startx, int starty, int targetx, int targety){
    Piece* peca_movida = matriz[startx][starty];

    if (peca_movida == nullptr){
        return false;
    }

    Piece* peca_destino = matriz[targetx][targety];

    if (peca_destino != nullptr){
        
        if (peca_movida->getColor() == peca_destino->getColor()){
            return false;
        }
    }
    
    bool IsCapture = (peca_destino != nullptr);

    if (peca_movida->IsValidMove(targetx, targety, IsCapture)){

        if (peca_destino != nullptr){
            delete peca_destino;
        }

        matriz[targetx][targety] = peca_movida;
        matriz[startx][starty] = nullptr;

        peca_movida->SetPos(targetx, targety);

        return true;

    }

    return false;
}

Piece* Tab::PromotePeao(int x, int y, char opt){
    Piece* peao = matriz[x][y];

    Color c = peao->getColor();

    delete peao;
    switch (opt){
        case 'R':
            return new Rainha(true, x, y, c);
                break;
        case 'C':
            return new Cavalo(true, x, y, c);
                break;
        case 'T':
            return new Torre(true, x, y, c);
            break;            
        case 'B':
            return new Bispo(true, x, y, c);
            break;

        default: 
            return new Rainha(true, x, y, c);
    }



}


void Tab::Drawboard(){

}
