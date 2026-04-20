#include "../../include/core/Tabuleiro.hpp"
#include "../../include/core/Bispo.hpp"
#include "../../include/core/Cavalo.hpp"
#include "../../include/core/Peao.hpp"
#include "../../include/core/Piece.hpp"
#include "../../include/core/Rainha.hpp"
#include "../../include/core/Rei.hpp"
#include "../../include/core/Torre.hpp"
#include <iostream>
#include <cmath>





Tab::Tab(){
    for (int x=0; x <8; x++){
        for (int y=0; y < 8; y++){
            matriz[x][y] = nullptr;
        }
    }


    for (int y=0; y < 8; y++){
        matriz[1][y] = new Peao(1, y, Cor::White);
        matriz[6][y] = new Peao(6, y, Cor::Black);
    }

    ReiBranco = new Rei(0,4,Cor::White);
    matriz[0][4] = ReiBranco;

    ReiPreto = new Rei(7,4,Cor::Black);
    matriz[7][4] = ReiPreto;

    matriz[0][0] = new Torre(0,0, Cor::White);
    matriz[0][7] = new Torre(0,7, Cor::White);
    matriz[7][0] = new Torre(7,0,Cor::Black);
    matriz[7][7] = new Torre(7,7,Cor::Black);

    matriz[0][3] = new Rainha(0, 3, Cor::White);
    matriz[7][3] = new Rainha(7, 3, Cor::Black);

    matriz[0][1] = new Cavalo(0,1, Cor::White);
    matriz[0][6] = new Cavalo(0,6, Cor::White);
    matriz[7][1] = new Cavalo(7,1, Cor::Black);
    matriz[7][6] = new Cavalo(7,6, Cor::Black);

    matriz[0][2] = new Bispo(0,2,Cor::White);
    matriz[0][5] = new Bispo(0,5,Cor::White);
    matriz[7][2] = new Bispo(7,2,Cor::Black);
    matriz[7][5] = new Bispo(7,5,Cor::Black);

    TurnoAtual = Cor::White;
}

Tab::~Tab() {
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (matriz[x][y] != nullptr) {
                delete matriz[x][y];
                matriz[x][y] = nullptr;
            }
        }
    }
}


Piece* Tab::getPiece(int x, int y){
    if (y >= 0 && y < 8 && x >= 0 && x < 8){
        return matriz[x][y];
    } else return nullptr;
} 


bool Tab::MovePiece(int startx, int starty, int targetx, int targety){
    Piece* peca_movida = matriz[startx][starty];

    Cor Color_player = peca_movida->getColor();
    
    int kx, ky;
    
    if (Color_player == Cor::White) {
        kx = ReiBranco->GetX(); 
        ky = ReiBranco->GetY();
    } else {
        kx = ReiPreto->GetX();
        ky = ReiPreto->GetY();
    }
    
    
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
  
        matriz[targetx][targety] = peca_movida;
        matriz[startx][starty] = nullptr;
        peca_movida->SetPos(targetx, targety); // simula o movimento para avaliar a condição de check

        bool SafeMove = !IsCheck(kx,ky); 
        if (SafeMove){
            if (peca_destino != nullptr){
                delete peca_destino;
            }

            if (TurnoAtual == Cor::White){ // Troca o turno
                TurnoAtual = Cor::Black;
            } else {
            }

            return true;

        } else {
            matriz[startx][starty] = peca_movida;
            matriz[targetx][targety] = peca_destino;
            peca_movida->SetPos(startx, starty);
            
            return false;
        }

    }

    return false;
} 

/* Promove o peão para a peça desejada pelo usuário*/
Piece* Tab::PromotePeao(int x, int y, char opt){
    Piece* peao = matriz[x][y];

    Cor c = peao->getColor();

    delete peao;
    switch (opt){
        case 'R':
            return new Rainha( x, y, c);
                break;
        case 'C':
            return new Cavalo( x, y, c);
                break;
        case 'T':
            return new Torre( x, y, c);
            break;            
        case 'B':
            return new Bispo( x, y, c);
            break;

        default: 
            return new Rainha( x, y, c);
    }



}

/* checa se o caminho está livre para a posição desejada*/
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
bool Tab::CheckRaio(int kingx, int kingy, int stepx, int stepy, Tipo p1, Tipo p2) const{ 
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


/* checa as possíveis posições do cavalo*/
bool Tab::CheckCavalo(int kingx, int kingy) const{
    Piece* king = matriz[kingx][kingy];

    int dx[] = {1,-1,1,-1, 2,2,-2,-2};
    int dy[] = {2,-2,2,-2, 1,-1,1,-1};

    for (int i = 0; i < 8;i++){
        int targetX = dx[i];
        int targetY = dy[i];
        if (targetX >= 0 && targetX < 8 && targetY >= 0 && targetY < 8){
            Piece* possible_piece = matriz[targetX][targetY];

            if (possible_piece != nullptr && possible_piece->getColor() != king->getColor()){
                return true;
            }
        }
    }
    return false;
}




bool Tab::IsCheck(int kingx, int kingy) const{
    Piece* king_piece = matriz[kingx][kingy];
    Cor color_king = king_piece->getColor();  
    
    if (CheckRaio(kingx, kingy,  1,  0, Tipo::TORRE, Tipo::RAINHA)) return true; 
    if (CheckRaio(kingx, kingy, -1,  0, Tipo::TORRE, Tipo::RAINHA)) return true; 
    if (CheckRaio(kingx, kingy,  0,  1, Tipo::TORRE, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy,  0, -1, Tipo::TORRE, Tipo::RAINHA)) return true; 

    if (CheckRaio(kingx, kingy,  1,  1, Tipo::BISPO, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy, -1,  1, Tipo::BISPO, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy,  1, -1, Tipo::BISPO, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy, -1, -1, Tipo::BISPO, Tipo::RAINHA)) return true;

    if (CheckCavalo(kingx, kingy)) return true;

    return false;
}









