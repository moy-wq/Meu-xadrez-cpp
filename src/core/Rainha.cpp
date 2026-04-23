#include "../../include/core/Rainha.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"
#include <cmath>



Rainha::Rainha(int startx, int starty, Cor color): Piece(startx, starty, color, Tipo::RAINHA){} // Construtor de Piece


bool Rainha::IsValidMove(int targetx, int targety, bool IsCapture){
    int Deltax = std::abs(targetx - this->x);
    int Deltay = std::abs(targety - this->y);

    if (targetx >= 0 && targetx < 8 && targety >= 0 && targety < 8){
        if (Deltax == Deltay || (Deltax == 0 && Deltay != 0 || Deltay == 0 && Deltax != 0)){
            return true;
        }
    }
    return false;


}