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

    if (peca_movida == nullptr){
        return false;
    }

    Cor Color_player = peca_movida->getColor();
    if (Color_player != TurnoAtual) {
        return false; 
    }

    Piece* peca_destino = matriz[targetx][targety];

 
    if (peca_destino != nullptr && Color_player == peca_destino->getColor()){
        return false;
    } 
    
    bool IsCapture = (peca_destino != nullptr);

    if (peca_movida->getType() != Tipo::CAVALO && !IsPathClear(startx, starty, targetx, targety)) {
        return false;
    }


    if (peca_movida->IsValidMove(targetx, targety, IsCapture)){
  
        // Executa o movimento fantasma
        matriz[targetx][targety] = peca_movida;
        matriz[startx][starty] = nullptr;
        peca_movida->SetPos(targetx, targety); 

        // Descobre onde o Rei vai estar para checar o Xeque
        int kx, ky;
        if (Color_player == Cor::White) {
            kx = (peca_movida == ReiBranco) ? targetx : ReiBranco->GetX(); 
            ky = (peca_movida == ReiBranco) ? targety : ReiBranco->GetY();
        } else {
            kx = (peca_movida == ReiPreto) ? targetx : ReiPreto->GetX();
            ky = (peca_movida == ReiPreto) ? targety : ReiPreto->GetY();
        }

        bool SafeMove = !IsCheck(kx, ky); 

        if (SafeMove){
 
            if (peca_destino != nullptr){
                delete peca_destino; 
            }


            if (TurnoAtual == Cor::White){ 
                TurnoAtual = Cor::Black;
            } else {
                TurnoAtual = Cor::White;
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
    Piece* current_piece = matriz[startx][starty];
    if (current_piece == nullptr) return true;
    if (current_piece->getType() == Tipo::CAVALO) return true;

    while (currentx != targetx || currenty != targety){
        if (matriz[currentx][currenty] != nullptr){
            return false;
        }
        currentx += stepx;
        currenty += stepy;
    }

    return true;
}



/*percorre o tabuleiro em possíveis direções buscando peças que podem atacar o rei (condição de check)*/
bool Tab::CheckRaio(int kingx, int kingy, int stepx, int stepy, Tipo p1, Tipo p2) const { 
    Piece* king = matriz[kingx][kingy];

    if (king == nullptr) return false;

    int possible_x = kingx + stepx;
    int possible_y = kingy + stepy;

    while ( possible_x >= 0 && possible_x < 8 && possible_y >= 0 && possible_y < 8 ){
        Piece* possible_piece = matriz[possible_x][possible_y];

        if (possible_piece != nullptr){
            if (possible_piece->getColor() != king->getColor() && 
               (possible_piece->getType() == p1 || possible_piece->getType() == p2)) {
                return true;        
            }
            break;
        }

        possible_x += stepx;
        possible_y += stepy; 
    }
    return false;
}

/* checa as possíveis posições do cavalo*/
bool Tab::CheckCavalo(int kingx, int kingy) const {
    Piece* king = matriz[kingx][kingy];
    if (king == nullptr) return false;

    // Os 8 movimentos em "L" relativos à posição do Rei
    int dx[] = { 1,  1, -1, -1,  2,  2, -2, -2};
    int dy[] = { 2, -2,  2, -2,  1, -1,  1, -1};

    for (int i = 0; i < 8; i++) {
        // CORREÇÃO 1: Você precisa somar a posição do Rei!
        int targetX = kingx + dx[i];
        int targetY = kingy + dy[i];

        // Verifica se a casa está dentro do tabuleiro
        if (targetX >= 0 && targetX < 8 && targetY >= 0 && targetY < 8) {
            Piece* possible_piece = matriz[targetX][targetY];

            // CORREÇÃO 2: Tem que ser COR DIFERENTE e TIPO CAVALO
            if (possible_piece != nullptr && 
                possible_piece->getColor() != king->getColor() && 
                possible_piece->getType() == Tipo::CAVALO) {
                return true;
            }
        }
    }
    return false;
}


bool Tab::IsCheck(int kingx, int kingy) const {
    Piece* king_piece = matriz[kingx][kingy];
    if (king_piece == nullptr) return false; 
    
    Cor color_king = king_piece->getColor();  

    // 1. Raios e Cavalo (Assumindo que CheckRaio e CheckCavalo já filtram cor corretamente)
    if (CheckRaio(kingx, kingy,  1,  0, Tipo::TORRE, Tipo::RAINHA)) return true; 
    if (CheckRaio(kingx, kingy, -1,  0, Tipo::TORRE, Tipo::RAINHA)) return true; 
    if (CheckRaio(kingx, kingy,  0,  1, Tipo::TORRE, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy,  0, -1, Tipo::TORRE, Tipo::RAINHA)) return true; 

    if (CheckRaio(kingx, kingy,  1,  1, Tipo::BISPO, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy, -1,  1, Tipo::BISPO, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy,  1, -1, Tipo::BISPO, Tipo::RAINHA)) return true;
    if (CheckRaio(kingx, kingy, -1, -1, Tipo::BISPO, Tipo::RAINHA)) return true;

    if (CheckCavalo(kingx, kingy)) return true;

    // 2. Xeque de Peão (Inimigos vêm da direção oposta ao movimento do Rei)
    // Se Rei Branco (sobe o mapa +1), os peões pretos vêm de cima (+1)
    // Se Rei Preto (desce o mapa -1), os peões brancos vêm de baixo (-1)
    int dir = (color_king == Cor::White) ? 1 : -1; 
    int pawnX = kingx + dir;

    if (pawnX >= 0 && pawnX < 8) {
        for (int dy : {-1, 1}) {
            int pawnY = kingy + dy;
            if (pawnY >= 0 && pawnY < 8) {
                Piece* p = matriz[pawnX][pawnY];
                if (p != nullptr && p->getColor() != color_king && p->getType() == Tipo::PEAO) {
                    return true;
                }
            }
        }
    }

    // 3. Xeque de Rei (Um rei não pode encostar no outro)
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = kingx + dx, ny = kingy + dy;
            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
                Piece* p = matriz[nx][ny];
                if (p != nullptr && p->getColor() != color_king && p->getType() == Tipo::REI) {
                    return true;
                }
            }
        }
    }

    return false; 
}


bool Tab::IsCheckmate(Cor playerColor) {
    int currentKx = (playerColor == Cor::White) ? this->ReiBranco->GetX() : ReiPreto->GetX();
    int currentKy = (playerColor == Cor::White) ? this->ReiBranco->GetY() : ReiPreto->GetY();

    if (!IsCheck(currentKx, currentKy)) {
        return false; 
    }


    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            Piece* p = matriz[x][y];

            if (p != nullptr && p->getColor() == playerColor) {
                
                for (int targetX = 0; targetX < 8; targetX++) {
                    for (int targetY = 0; targetY < 8; targetY++) {
                        Piece* targetPiece = matriz[targetX][targetY];
                        

                        if (targetPiece != nullptr && targetPiece->getType() == Tipo::REI) {
                            continue; 
                        }
                        if (targetPiece != nullptr && targetPiece->getColor() == playerColor) {
                            continue; 
                        }
                        
                        bool isCapture = (targetPiece != nullptr);

                        bool caminhoLivre = (p->getType() == Tipo::CAVALO) ? true : IsPathClear(x, y, targetX, targetY);
   
                        if (caminhoLivre && p->IsValidMove(targetX, targetY, isCapture)) {

                            matriz[targetX][targetY] = p;
                            matriz[x][y] = nullptr;

                            int antigaPecaX = x; 
                            int antigaPecaY = y;
                            
                            p->SetPos(targetX, targetY);

                            int simKx = (p->getType() == Tipo::REI) ? targetX : currentKx;
                            int simKy = (p->getType() == Tipo::REI) ? targetY : currentKy;

                            bool stillInCheck = IsCheck(simKx, simKy);
                            
                            matriz[antigaPecaX][antigaPecaY] = p;   
                            matriz[targetX][targetY] = targetPiece;
                            p->SetPos(antigaPecaX, antigaPecaY);

                            if (!stillInCheck) {
                                return false; 
                            }
                        }
                    }
                }
            }
        }
    }


    return true;
}

Cor Tab::GetTurnoAtual() const {
    return this->TurnoAtual;
}