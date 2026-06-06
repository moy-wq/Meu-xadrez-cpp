
#include <iostream>
#include "raylib.h"

#include "../../include/UI/Interface.hpp"
#include "../../include/core/Tabuleiro.hpp"

Interface::Interface(int tam_casa, int offset)
{
    tamanhoCasa = tam_casa;
    offsethorizontal = offset;

    Image imgPeaoBranco = LoadImage("assets/PeaoBranco.png");
    Image imgPeaoPreto = LoadImage("assets/PeaoPreto.png");
    Image imgBispoBranco = LoadImage("assets/BispoBranco.png");
    Image imgBispoPreto = LoadImage("assets/BispoPreto.png");
    Image imgTorreBranca = LoadImage("assets/TorreBranca.png");
    Image imgTorrePreta = LoadImage("assets/TorrePreta.png");
    Image imgCavaloBranco = LoadImage("assets/CavaloBranco.png");
    Image imgCavaloPreto = LoadImage("assets/CavaloPreto.png");
    Image imgReiBranco = LoadImage("assets/ReiBranco.png");
    Image imgReiPreto = LoadImage("assets/ReiPreto.png");
    Image imgRainhaBranca = LoadImage("assets/RainhaBranca.png");
    Image imgRainhaPreta = LoadImage("assets/RainhaPreta.png");

    ImageResize(&imgPeaoBranco, 80, 80);
    ImageResize(&imgPeaoPreto, 80, 80);
    ImageResize(&imgBispoBranco, 80, 80);
    ImageResize(&imgBispoPreto, 80, 80);
    ImageResize(&imgTorreBranca, 80, 80);
    ImageResize(&imgTorrePreta, 80, 80);
    ImageResize(&imgCavaloBranco, 80, 80);
    ImageResize(&imgCavaloPreto, 80, 80);
    ImageResize(&imgReiBranco, 80, 80);
    ImageResize(&imgReiPreto, 80, 80);
    ImageResize(&imgRainhaBranca, 80, 80);
    ImageResize(&imgRainhaPreta, 80, 80);

    this->PeaoBranco = LoadTextureFromImage(imgPeaoBranco);
    this->PeaoPreto = LoadTextureFromImage(imgPeaoPreto);
    this->BispoBranco = LoadTextureFromImage(imgBispoBranco);
    this->BispoPreto = LoadTextureFromImage(imgBispoPreto);
    this->TorreBranca = LoadTextureFromImage(imgTorreBranca);
    this->TorrePreta = LoadTextureFromImage(imgTorrePreta);
    this->CavaloBranco = LoadTextureFromImage(imgCavaloBranco);
    this->CavaloPreto = LoadTextureFromImage(imgCavaloPreto);
    this->ReiBranco = LoadTextureFromImage(imgReiBranco);
    this->ReiPreto = LoadTextureFromImage(imgReiPreto);
    this->RainhaBranca = LoadTextureFromImage(imgRainhaBranca);
    this->RainhaPreta = LoadTextureFromImage(imgRainhaPreta);

    UnloadImage(imgPeaoBranco);
    UnloadImage(imgPeaoPreto);
    UnloadImage(imgBispoBranco);
    UnloadImage(imgBispoPreto);
    UnloadImage(imgTorreBranca);
    UnloadImage(imgTorrePreta);
    UnloadImage(imgCavaloBranco);
    UnloadImage(imgCavaloPreto);
    UnloadImage(imgReiBranco);
    UnloadImage(imgReiPreto);
    UnloadImage(imgRainhaBranca);
    UnloadImage(imgRainhaPreta);
}

Interface::~Interface() {};

void Interface::DrawTab(Tab *tabuleiroLogico)
{
    Vector2 pos_mouse = GetMousePosition();
    Color color_quadrado = RAYWHITE;

    Interface::DrawCurrentTurn(tabuleiroLogico->GetTurnoAtual());

    for (int i = 200; i < (200 + 8 * this->tamanhoCasa); i += this->tamanhoCasa)
    {
        for (int j = 0; j < 800; j += this->tamanhoCasa)
        {

            int colunaMatriz = (i - 200) / this->tamanhoCasa;
            int linhaMatriz  = j / this->tamanhoCasa;

            Piece *peca_atual = tabuleiroLogico->getPiece(linhaMatriz, colunaMatriz);

            if (colunaMatriz % 2 == 0)
            {
                color_quadrado = (linhaMatriz % 2 == 0) ? DARKGRAY : RAYWHITE;
            }
            else
            {
                color_quadrado = (linhaMatriz % 2 != 0) ? DARKGRAY : RAYWHITE;
            }

            DrawRectangle(i, j, this->tamanhoCasa, this->tamanhoCasa, color_quadrado);


            if (pos_mouse.x >= i && pos_mouse.x < (i + this->tamanhoCasa) &&
                pos_mouse.y >= j && pos_mouse.y < (j + this->tamanhoCasa))
            {
                DrawRectangle(
                    i + 10,
                    j + 10,
                    this->tamanhoCasa - 20,
                    this->tamanhoCasa - 20,
                    SKYBLUE
                );
            }

            if (peca_atual != nullptr)
                PlaceTexture(peca_atual, i, j);
        }
    }
}

void Interface::PlaceTexture(Piece *peca_atual, int i, int j) 
{
    Vector2 posDesenho = {(float)i + 10, (float)j + 10};
    if (peca_atual->getType() == Tipo::PEAO && peca_atual->getColor() == Cor::Black)
        DrawTextureV(this->PeaoPreto, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::PEAO && peca_atual->getColor() == Cor::White)
        DrawTextureV(this->PeaoBranco, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::BISPO && peca_atual->getColor() == Cor::Black)
        DrawTextureV(this->BispoPreto, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::BISPO && peca_atual->getColor() == Cor::White)
        DrawTextureV(this->BispoBranco, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::TORRE && peca_atual->getColor() == Cor::Black)
        DrawTextureV(this->TorrePreta, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::TORRE && peca_atual->getColor() == Cor::White)
        DrawTextureV(this->TorreBranca, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::CAVALO && peca_atual->getColor() == Cor::Black)
        DrawTextureV(this->CavaloPreto, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::CAVALO && peca_atual->getColor() == Cor::White)
        DrawTextureV(this->CavaloBranco, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::REI && peca_atual->getColor() == Cor::Black)
        DrawTextureV(this->ReiPreto, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::REI && peca_atual->getColor() == Cor::White)
        DrawTextureV(this->ReiBranco, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::RAINHA && peca_atual->getColor() == Cor::Black)
        DrawTextureV(this->RainhaPreta, posDesenho, BLACK);
    if (peca_atual->getType() == Tipo::RAINHA && peca_atual->getColor() == Cor::White)
        DrawTextureV(this->RainhaBranca, posDesenho, BLACK);
}

void Interface::ShowPossibleMoves(Piece *currentPiece, Tab *tabuleiroLogico)
{

    int linhaOrigem = currentPiece->GetX();
    int colOrigem = currentPiece->GetY();

    for (int linha = 0; linha < 8; linha++)
    {
        for (int coluna = 0; coluna < 8; coluna++)
        {

            Piece *peca_destino = tabuleiroLogico->getPiece(linha, coluna);
            bool isCapture = false;

            if (peca_destino != nullptr)
            {
                if (peca_destino->getColor() == currentPiece->getColor())
                {
                    continue;
                }
                isCapture = true; // Inimigo!
            }

            if (currentPiece->IsValidMove(linha, coluna, isCapture))
            {
                if (currentPiece->getType() == Tipo::CAVALO ||
                    tabuleiroLogico->IsPathClear(linhaOrigem, colOrigem, linha, coluna))
                {

                    int drawX = 200 + (coluna * this->tamanhoCasa);
                    int drawY = (linha * this->tamanhoCasa);

                    DrawRectangle(drawX + 10, drawY + 10, (this->tamanhoCasa - 20), (this->tamanhoCasa - 20), SKYBLUE);
                }
            }
        }
    }
}

void Interface::DrawGameOverScreen(Cor corVencedora)
{

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));

    const char *textoVitoria = (corVencedora == Cor::White) ? "BRANCAS VENCEM" : "PRETAS VENCEM";
    const char *textoTitulo = "XEQUE-MATE";
    const char *textoDica = "Pressione ENTER para jogar novamente";

    int sizeTitulo = 60;
    int sizeVitoria = 40;
    int sizeDica = 20;

    int posX_Titulo = (screenWidth - MeasureText(textoTitulo, sizeTitulo)) / 2;
    int posX_Vitoria = (screenWidth - MeasureText(textoVitoria, sizeVitoria)) / 2;
    int posX_Dica = (screenWidth - MeasureText(textoDica, sizeDica)) / 2;

    DrawText(textoTitulo, posX_Titulo, screenHeight / 2 - 100, sizeTitulo, RED);
    DrawText(textoVitoria, posX_Vitoria, screenHeight / 2 - 20, sizeVitoria, WHITE);
    DrawText(textoDica, posX_Dica, screenHeight / 2 + 80, sizeDica, LIGHTGRAY);
}

void Interface::DrawCurrentTurn(Cor turnoAtual)
{
    int posX = 20;
    int posY = 50;
    int largura = 160;
    int altura = 80;

    DrawText("TURNO ATUAL:", posX + 5, posY + 10, 20, BLACK);

    if (turnoAtual == Cor::White)
    {
        DrawRectangle(posX + 10, posY + 40, 140, 30, WHITE);
    
        DrawText("BRANCAS", posX + 32, posY + 45, 20, BLACK);
    }
    else
    {
        DrawRectangle(posX + 10, posY + 40, 140, 30, BLACK);
        DrawText("PRETAS", posX + 35, posY + 45, 20, WHITE);
    }
}

int Interface::getX()
{
    return this->fix_x;
}

int Interface::getY()
{
    return this->fix_y;
}

void Interface::DrawBeginWindow() {
    ClearBackground(BLACK);


    const char* titulo = "SIMULADOR DE XADREZ";
    int tamanhoTitulo = 60;
    int larguraTitulo = MeasureText(titulo, tamanhoTitulo);
    int posX_Titulo = (1200 - larguraTitulo) / 2;
    int posY_Titulo = 300; // Pouco acima do centro (400)

    const char* subtitulo = "Pressione [ENTER] para iniciar";
    int tamanhoSubtitulo = 20;
    int larguraSubtitulo = MeasureText(subtitulo, tamanhoSubtitulo);
    int posX_Subtitulo = (1200 - larguraSubtitulo) / 2;
    int posY_Subtitulo = 400; 

    DrawText(titulo, posX_Titulo, posY_Titulo, tamanhoTitulo, RAYWHITE);
    DrawText(subtitulo, posX_Subtitulo, posY_Subtitulo, tamanhoSubtitulo, DARKGRAY);
}