#include "../../include/core/Cavalo.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"
#include <cmath>
Cavalo::Cavalo(int startx, int starty, Cor color): Piece(startx, starty, color, Tipo::CAVALO){} // Construtor de Piece


bool Cavalo::IsValidMove(int targetx, int targety, bool IsCapture) {
    int diffX = std::abs(targetx - this->x);
    int diffY = std::abs(targety - this->y);

    if ((diffX == 2 && diffY == 1) || (diffX == 1 && diffY == 2)) {
        return true; 
    }

    return false;
}