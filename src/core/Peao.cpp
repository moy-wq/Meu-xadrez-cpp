#include "../../include/core/Peao.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"


Peao::Peao(int startx, int starty, Cor color): Piece(startx, starty, color, Tipo::PEAO){} // Construtor de Piece



bool Peao::IsValidMove(int targetx, int targety, bool IsCapture){
    int direction = (this->c == Cor::White ) ? 1 : -1; //if ternário
    
    if (this->x == targetx && targety == 1 + this->y){

        return !IsCapture;
    
    } else if (this->x + 1 == targety && this->y + 1 == targety){
    
        return IsCapture;
    }
    
    return false;

}







