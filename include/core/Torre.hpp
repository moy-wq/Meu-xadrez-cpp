#pragma once
#include <iostream>
#include "Piece.hpp"

class Torre: public Piece {
    public:
        Torre(int startx, int starty, Cor color);

        bool IsValidMove(int targetx, int targety, bool IsCapture) override;

        virtual bool CanJump() const override {return false;} ;

};