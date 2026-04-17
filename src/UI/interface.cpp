
#include <iostream>
#include "raylib.h"
#include "../../include/UI/Interface.hpp"

Interface::Interface(int tam_casa, int offset){
    tamanhoCasa = tam_casa;
    offsethorizontal = offset;
}



void Interface::DrawTab() {

            ClearBackground(BLACK);

            Vector2 pos_mouse = GetMousePosition();
            Color color_quadrado;
            for (int i = 200; i < (200 + this->offsethorizontal); i+= 100){
                for (int j = 0; j < this->offsethorizontal; j+=100){ 
                    if ((i / this->tamanhoCasa) % 2 == 0){
                        if ((j /this->tamanhoCasa) % 2 == 0){
                            color_quadrado = DARKGRAY;
                        } else {
                            color_quadrado = RAYWHITE;
                        }
                    } else {
                        if ((j /this->tamanhoCasa) % 2 != 0) {
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
                }
            }

}


