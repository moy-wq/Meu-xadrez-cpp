#pragma once 

#include <raylib.h>

class Interface{
    private:
        int tamanhoCasa;
        int offsethorizontal;

        Texture2D PeaoBranco;
        Texture2D PeaoPreto;
        Texture2D BispoBranco;
        Texture2D BispoPreto;
        Texture2D TorreBranco;
        Texture2D TorrePreta;
        Texture2D CavaloBranco;
        Texture2D CavaloPreto;
        Texture2D ReiBranco;
        Texture2D ReiPreto;
        Texture2D RainhaBranco;
        Texture2D RainhaPreto;


    public:
        Interface(int tamCasa, int offset);
        void DrawTab(Tab& tabuleiroLogico);

        ~Interface();

};

