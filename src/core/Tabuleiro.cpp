#include "../../include/core/Tabuleiro.hpp"
#include <iostream>
#include <cmath>



Piece* Tab::getPiece(int x, int y){
    if (y > 0 && y < 8 && x > 0 && y < 8){
        return matriz[x][y];
    }
} 
bool Tab::MovePiece(int startx, int starty, int targetx, int targety){
    Piece* peca_movida = matriz[startx][starty];

    if (peca_movida == nullptr){
        return false;
    }

    Piece* peca_destino = matriz[targetx][targety];

    if (peca_destino != nullptr){
        
        if (peca_movida->getColor() == peca_destino->getColor()){
            return false;
        }
    } 
    
    bool IsCapture = (peca_destino != nullptr);

    if (peca_movida->IsValidMove(targetx, targety, IsCapture)){

        if (peca_destino != nullptr){
            delete peca_destino;
        }

        matriz[targetx][targety] = peca_movida;
        matriz[startx][starty] = nullptr;

        peca_movida->SetPos(targetx, targety);

        return true;

    }

    return false;
} 

Piece* Tab::PromotePeao(int x, int y, char opt){
    Piece* peao = matriz[x][y];

    Color c = peao->getColor();

    delete peao;
    switch (opt){
        case 'R':
            return new Rainha(true, x, y, c);
                break;
        case 'C':
            return new Cavalo(true, x, y, c);
                break;
        case 'T':
            return new Torre(true, x, y, c);
            break;            
        case 'B':
            return new Bispo(true, x, y, c);
            break;

        default: 
            return new Rainha(true, x, y, c);
    }



}

bool Tab::IsPathClear(int startx, int starty, int targetx, int targety){
    int stepx = (targetx > startx) ? 1: (targetx < startx ? -1: 0);
    int stepy = (targety > starty) ? 1: (targety < starty ? -1: 0);

    int currentx = startx + stepx;
    int currenty = starty + stepy;

    while (currentx != targetx || currenty != targety){
        if (matriz[currentx][currenty] != nullptr){
            return false;
        }
        currentx++;
        currenty++;
    }

    return true;
}



/*percorre o tabuleiro em possíveis direções buscando peças que podem atacar o rei (condição de check)*/
bool Tab::CheckRaio(int kingx, int kingy, int stepx, int stepy, Tipo p1, Tipo p2){ 
    Piece* king = matriz[kingx][kingy];
    int possible_x = kingx + stepx;
    int possible_y = kingy + stepy;

    while ( possible_x >= 0 && possible_x < 8 && possible_y >= 0 && possible_y < 8 ){
        Piece* possible_piece = matriz[possible_x][possible_y];

        if (possible_piece != nullptr){
            if (possible_piece->getColor() != king->getColor() && possible_piece->getType() == p1 || possible_piece->getType() == p2){
                return true;        
            }
            break;
        }

    possible_x += stepx;
    possible_y += stepy; // modificam exatamente a direção percorrida no tabuleiro
        
    }
    return false;
}


bool Tab::CheckCavalo(int kingx, int kingy, int stepx, int stepy){
    Piece* king = matriz[kingx][kingy];
    int possible_x = kingx + stepx;
    int poissible_y = kingy + stepy;




}




bool Tab::IsCheck(int kingx, int kingy){
    Piece* king_piece = matriz[kingx][kingy];
    Color color_king = king_piece->getColor();  









}