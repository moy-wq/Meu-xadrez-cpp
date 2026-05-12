#include "../../include/core/Peao.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"


Peao::Peao(int startx, int starty, Cor color): Piece(startx, starty, color, Tipo::PEAO){} // Construtor de Piece


bool Peao::IsValidMove(int targetx, int targety, bool IsCapture){

    int direction = (this->getColor() == Cor::White) ? 1 : -1; 


    if (targety == this->y && targetx == this->x + direction) {
        return !IsCapture; 
    }


    bool isFirstMove = (this->getColor() == Cor::White && this->x == 1) || 
                       (this->getColor() == Cor::Black && this->x == 6);
                       
    if (isFirstMove && targety == this->y && targetx == this->x + (direction * 2)) {
        return !IsCapture;
    }

    if (targetx == this->x + direction && (targety == this->y + 1 || targety == this->y - 1)) {
        return IsCapture; 
    }
    
    return false;
}