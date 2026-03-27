#include "../../include/core/Cavalo.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Tabuleiro.hpp"

Cavalo::Cavalo(int startx, int starty, Color color): Piece(startx, starty, color, Tipo::CAVALO){} // Construtor de Piece

bool Cavalo::IsValidMove(int targetx,int targety, bool IsCapture){
    if (targetx == this->x + 2 && targety == this->x + 1){
        return true;
    }
    return false;
}
