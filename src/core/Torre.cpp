#include "../../include/core/Torre.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"
#include <cmath>

Torre::Torre(bool status, int startx, int starty, Color color): Piece(status, startx, starty, color, Tipo::TORRE){} // Construtor de Piece

bool Torre::IsValidMove(int targetx, int targety, bool IsCapture){
    int Deltax = std::abs(targetx - this->x);
    int Deltay = std::abs(targety - this->y);

    if (targetx >= 0 && targetx < 8 && targety >= 0 && targety < 8) {
        if (Deltax == 0 && Deltay != 0 || Deltay == 0 && Deltax != 0){
            return true;
        }
    }
    return false;


}
