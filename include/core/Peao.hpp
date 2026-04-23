#pragma once
#include <iostream>
#include "Piece.hpp"

class Peao: public Piece {
    public:
        Peao(int startx, int starty, Cor color);

        bool IsValidMove(int targetx, int targety, bool IsCapture) override;
        
        Piece* IsPromoted(int option);

        virtual bool CanJump() const override {return false;} ;

};