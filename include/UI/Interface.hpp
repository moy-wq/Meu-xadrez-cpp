#include <raylib.h>
#include "../core/Tabuleiro.hpp"

class Interface{
    private:
        int tamanhoCasa;
        int offsethorizontal;

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

        ~Interface();

};

