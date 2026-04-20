
#include <iostream>
#include "raylib.h"

#include "../../include/UI/Interface.hpp"
#include "../../include/core/Tabuleiro.hpp"


Interface::Interface(int tam_casa, int offset){
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

Interface::~Interface(){};

void Interface::DrawTab(Tab& tabuleiroLogico) {
            ClearBackground(BLACK);


            Vector2 pos_mouse = GetMousePosition();
            Color color_quadrado;

            for (int i = 200; i < (200 + this->offsethorizontal); i+= this-> tamanhoCasa){
                for (int j = 0; j < this->offsethorizontal; j+=this-> tamanhoCasa){ 

                    int colunaMatriz = (i - 200) / this->tamanhoCasa;
                    int linhaMatriz = j / this->tamanhoCasa;

                    Piece* peca_atual = tabuleiroLogico.getPiece(linhaMatriz, colunaMatriz);

                    if ((i / this->tamanhoCasa) % 2 == 0){
                        if ((j /this->tamanhoCasa) % 2 == 0){
                            color_quadrado = DARKGRAY;
                        } else {
                            color_quadrado = RAYWHITE;
                        }
                    } else {
                        if ((j /tamanhoCasa) % 2 != 0) {
                            color_quadrado = DARKGRAY;
                        } else { 
                            color_quadrado = RAYWHITE;
                        }
                    } 
                    
                    DrawRectangle(i,j, 100,100, color_quadrado); 

                    if (pos_mouse.x >= i && pos_mouse.x < (i + this->tamanhoCasa) 
                        && pos_mouse.y >= j && pos_mouse.y < (j + this->tamanhoCasa)){
                            DrawRectangle(i + 10,j + 10, (this->tamanhoCasa - 20), (this->tamanhoCasa - 20), SKYBLUE);
                        }

                
                    if (peca_atual != nullptr){ 
                        Vector2 posDesenho = {(float)i + 10, (float)j + 10};
                        if (peca_atual->getType() == Tipo::PEAO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->PeaoPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::PEAO && peca_atual->getColor() == Cor::White) DrawTextureV(this->PeaoBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::BISPO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->BispoPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::BISPO && peca_atual->getColor() == Cor::White) DrawTextureV(this->BispoBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::TORRE && peca_atual->getColor() == Cor::Black) DrawTextureV(this->TorrePreta, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::TORRE && peca_atual->getColor() == Cor::White) DrawTextureV(this->TorreBranca, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::CAVALO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->CavaloPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::CAVALO && peca_atual->getColor() == Cor::White) DrawTextureV(this->CavaloBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::REI && peca_atual->getColor() == Cor::Black) DrawTextureV(this->ReiPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::REI && peca_atual->getColor() == Cor::White) DrawTextureV(this->ReiBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::RAINHA && peca_atual->getColor() == Cor::Black) DrawTextureV(this->RainhaPreta, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::RAINHA && peca_atual->getColor() == Cor::White) DrawTextureV(this->RainhaBranca, posDesenho, BLACK);
                    
                    }
                }
            }

}


