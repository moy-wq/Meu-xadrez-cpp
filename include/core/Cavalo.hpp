#pragma once
#include <iostream>
#include "Piece.hpp"

class Cavalo: public Piece {
    public:
        Cavalo(bool status, int startx, int starty, Color color);

        bool IsValidMove(int targetx, int targety, bool IsCapture) override;

};