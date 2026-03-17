#pragma once
#include <iostream>
#include "../core/Piece.hpp"
#include "../core/Peao.hpp"
#include "../core/Bispo.hpp"
#include "../core/Cavalo.hpp"
#include "../core/Torre.hpp"
#include "../core/Rei.hpp"
#include "../core/Rainha.hpp"

class Tab{
    public:
        Tab();
        ~Tab();

        Piece* getPiece(int x, int y); //Localização da peça

        bool MovePiece(int startx, int starty, int targetx, int targety);
        bool IsPathClear(int startx, int starty, int targetx, int targety);
        bool IsCheck(int kingx, int kingy);

        Piece* PromotePeao(int x, int y, char opt); 

        void Drawboard();

        
    private:
        Piece* matriz[8][8];
        Piece* ReiBranco;
        Piece* ReiPreto;

        bool CheckRaio(int kingx, int kingy, int stepx, int stepy,Tipo p1, Tipo p2);
        bool CheckCavalo(int kingx, int kingy);
        bool CheckPeao(int kingx, int kingy, int stepx, int stepy);
};