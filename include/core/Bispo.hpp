#pragma once
#include <iostream>
#include "Piece.hpp"

class Bispo: public Piece {
    public:
        Bispo(int startx, int starty, Color color);

        bool IsValidMove(int targetx, int targety, bool IsCapture) override;

        virtual bool CanJump() const override {return false;} ;

};