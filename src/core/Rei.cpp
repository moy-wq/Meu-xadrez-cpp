#include "../../include/core/Peao.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"
#include <cmath>
Rei::Rei(bool status, int startx, int starty, Color color): Piece(status, startx, starty, color, Tipo::REI){} // Construtor de Piece


bool Rei::IsValidMove(int targetx, int targety, bool IsCapture){
    int Deltax = std::abs(targetx - this->x);
    int Deltay = std::abs(targety - this->y);

    if (targetx >= 0 && targetx < 8 && targety >= 0 && targety < 8){
        if (Deltax + Deltay <= 2){
            return true;
        }
    }
    return false;
}