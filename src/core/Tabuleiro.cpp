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


    for (int x=0; x < 8; x++){
        matriz[x][1] = new Peao(x, 1, Color::White);
        matriz[x][6] = new Peao(x, 6, Color::Black);
    }

    ReiBranco = new Rei(4,0,Color::White);
    matriz[4][0] = ReiBranco;

    ReiPreto = new Rei(4,7,Color::Black);
    matriz[4][7] = ReiPreto;

    matriz[0][0] = new Torre(0,0, Color::White);
    matriz[7][0] = new Torre(7,0, Color::White);
    matriz[0][7] = new Torre(0,7,Color::Black);
    matriz[7][7] = new Torre(7,7,Color::Black);

    matriz[3][0] = new Rainha(3, 0, Color::White);
    matriz[3][7] = new Rainha(3, 7, Color::Black);

    matriz[1][0] = new Cavalo(1,0, Color::White);
    matriz[6][0] = new Cavalo(6,0, Color::White);
    matriz[1][7] = new Cavalo(1,7, Color::Black);
    matriz[6][7] = new Cavalo(6,7, Color::Black);

    matriz[2][0] = new Bispo(2,0,Color::White);
    matriz[5][0] = new Bispo(5,0,Color::White);
    matriz[2][7] = new Bispo(2,7,Color::Black);
    matriz[5][7] = new Bispo(5,7,Color::Black);

    TurnoAtual = Color::White;
}




Piece* Tab::getPiece(int x, int y){
    if (y > 0 && y < 8 && x > 0 && y < 8){
        return matriz[x][y];
    }
} 


bool Tab::MovePiece(int startx, int starty, int targetx, int targety){
    Piece* peca_movida = matriz[startx][starty];

    Color Color_player = peca_movida->getColor();
    
    int kx, ky;
    
    if (Color_player == Color::White) {
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

            if (TurnoAtual == Color::White){ // Troca o turno
                TurnoAtual = Color::Black;
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

    Color c = peao->getColor();

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


/* checa as possíveis posições do cavalo*/
bool Tab::CheckCavalo(int kingx, int kingy){
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




bool Tab::IsCheck(int kingx, int kingy){
    Piece* king_piece = matriz[kingx][kingy];
    Color color_king = king_piece->getColor();  
    
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









