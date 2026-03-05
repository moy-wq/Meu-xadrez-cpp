#include "../../include/core/Piece.hpp"
#include <iostream>

enum class Color {White, Black};


Piece::Piece(bool status ,int startx, int starty, Color color, Tipo type){ // construtor
    this->x = startx;
    this->y = starty;
    this->active = status;
    this->c = color;
    this->tipo = type;
}

Color Piece::getColor() const{
    return this->c;
}

Tipo Piece::getType() const{
    return this->tipo;
}

void Piece::SetPos(int newx, int newy){
    this->x = newx;
    this->y = newy;

}



Piece::~Piece(){}

