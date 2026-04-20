#include "../../include/core/Piece.hpp"
#include <iostream>

enum class Color {White, Black};


Piece::Piece(int startx, int starty, Cor color, Tipo type){ // construtor
    this->x = startx;
    this->y = starty;
    this->c = color;
    this->tipo = type;
}

Cor Piece::getColor() const{
    return this->c;
}

Tipo Piece::getType() const{
    return this->tipo;
}

int Piece::GetX() const{
    return this->x;
}

int Piece::GetY() const{
    return this->y;
}

void Piece::SetPos(int newx, int newy){
    this->x = newx;
    this->y = newy;

}



Piece::~Piece(){};

