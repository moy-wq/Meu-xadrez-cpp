#pragma once

#include <raylib.h>
#include "../core/Tabuleiro.hpp"
#include "../core/Piece.hpp"

class Interface{
    private:
        int tamanhoCasa;
        int offsethorizontal;

        int fix_x, fix_y;

        Texture2D PeaoBranco;
        Texture2D PeaoPreto;
        Texture2D BispoBranco;
        Texture2D BispoPreto;
        Texture2D TorreBranca;
        Texture2D TorrePreta;
        Texture2D CavaloBranco;
        Texture2D CavaloPreto;
        Texture2D ReiBranco;
        Texture2D ReiPreto;
        Texture2D RainhaBranca;
        Texture2D RainhaPreta;


    public:
        Interface(int tamCasa, int offset);
        void DrawTab(Tab* tabuleiroLogico);
        void PlaceTexture(Piece* peca_atual, int i, int j);
        void ShowPossibleMoves(Piece* currentPiece, Tab* tabuleiro_logico);

        ~Interface();
        void DrawGameOverScreen(Cor corVencedora);
        void DrawCurrentTurn(Cor turnoAtual);

        void DrawBeginWindow();

        int getX();
        int getY();

};

