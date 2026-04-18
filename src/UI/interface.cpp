
#include <iostream>
#include "raylib.h"

#include "../../include/UI/Interface.hpp"
#include "../../include/core/Tabuleiro.hpp"


Interface::Interface(int tam_casa, int offset){
    tamanhoCasa = tam_casa;
    offsethorizontal = offset;
    this->PeaoBranco = LoadTexture("../../assets/PeaoBranco");
    this->PeaoPreto = LoadTexture("../../assets/PeaoPreto");
    this->BispoBranco = LoadTexture("../../assets/BispoBranco");
    this->BispoPreto = LoadTexture("../../assets/BispoPreto");
    this->TorreBranco = LoadTexture("../../assets/TorreBranco");
    this->TorrePreta = LoadTexture("../../assets/TorrePreta");
    this->CavaloBranco = LoadTexture("../../assets/CavaloBranco");
    this->CavaloPreto = LoadTexture("../../assets/CavaloPreto");
    this->ReiBranco = LoadTexture("../../assets/ReiBranco");
    this->ReiPreto = LoadTexture("../../assets/ReiPreto");
    this->RainhaBranco = LoadTexture("../../assets/RainhaBranco");
    this->RainhaPreto = LoadTexture("../../assets/RainhaPreto");



}

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
                        Vector2 posDesenho = {(float)i, (float)j};
                        if (peca_atual->getType() == Tipo::PEAO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->PeaoPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::PEAO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->PeaoPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::BISPO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->BispoBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::BISPO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->BispoPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::TORRE && peca_atual->getColor() == Cor::Black) DrawTextureV(this->TorreBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::TORRE && peca_atual->getColor() == Cor::Black) DrawTextureV(this->TorrePreta, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::CAVALO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->CavaloBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::CAVALO && peca_atual->getColor() == Cor::Black) DrawTextureV(this->CavaloPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::REI && peca_atual->getColor() == Cor::Black) DrawTextureV(this->ReiBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::REI && peca_atual->getColor() == Cor::Black) DrawTextureV(this->ReiPreto, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::RAINHA && peca_atual->getColor() == Cor::Black) DrawTextureV(this->RainhaBranco, posDesenho, BLACK);
                        if (peca_atual->getType() == Tipo::RAINHA && peca_atual->getColor() == Cor::Black) DrawTextureV(this->RainhaPreto, posDesenho, BLACK);
                    
                    }
                }
            }

}


