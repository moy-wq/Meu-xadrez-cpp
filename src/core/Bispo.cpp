#include "../../include/core/Bispo.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"

#include <cmath>
#include <iostream>

Bispo::Bispo(int startx, int starty, Color color): Piece(startx, starty, color, Tipo::BISPO){} // Construtor de Piece

bool Bispo::IsValidMove(int targetx,int targety, bool IsCapture){
    
    int Deltax = std::abs(targetx - this->x);
    int Deltay = std::abs(targety - this->y);

    if (targetx >= 0 && targetx < 8 && targety >= 0 && targety < 8){
        if (Deltax == Deltay && Deltax > 0){
            return true;
        }
    }
    return false;
}

