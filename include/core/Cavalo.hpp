#pragma once
#include <iostream>
#include "Piece.hpp"

class Cavalo: public Piece {
    public:
        Cavalo(int startx, int starty, Cor color);

        bool IsValidMove(int targetx, int targety, bool IsCapture) override;
        
        virtual bool CanJump() const override {return true;} ;

};