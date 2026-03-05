#pragma once
#include <iostream>
#include "Piece.hpp"

class Peao: public Piece {
    public:
        Peao(bool status, int startx, int starty, Color color);

        bool IsValidMove(int targetx, int targety, bool IsCapture) override;
        
        Piece* IsPromoted(int option);

};