#pragma once

#include <iostream>


enum class Color {White, Black};

enum class Tipo {PEAO, TORRE, CAVALO, RAINHA, REI, BISPO};

class Piece {
    
    public:
        Piece(bool status ,int startx, int starty, Color color, Tipo type){ // construtor
            x = startx;
            y = starty;
            c = color;
            tipo = type; 
    }

    virtual bool IsValidMove(int targetx, int target_y, bool IsCapture) = 0; // Flag de possibilidade de movimento

    void SetPos(int newx, int newy);
    
    Color getColor() const;

    virtual bool CanJump() const {return false;};

    virtual bool isCheck(int targetx, int targety) const; 

    

    Tipo getType() const;
    
    virtual ~Piece(); // Destrutor
    

    protected:
        Color c;
        int x, y; 
        Tipo tipo;
    };

