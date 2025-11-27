#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <string> 

#include "modelo.h"
#include "ia.h"

extern "C" {
    #include "tabuleiro.h"
}

using namespace std;

int main(int argc, char **argv) {
    srand(time(NULL));
    char buf[512];
    char lado_meu;
    
    tabuleiro_conecta(argc, argv);

    vector<string> historico;

    while(true) {
        tabuleiro_recebe(buf);
        
        char *linha1 = strtok(buf, "\n");
        char *linha2 = strtok(NULL, "\n");
        char *strTabuleiro = strtok(NULL, ""); 
        
        if (!linha1 || !linha2) break;
        
        sscanf(linha1, "%c", &lado_meu);
        
        BoardModel modelo;
        modelo.parseFromString(strTabuleiro);

        historico.push_back(modelo.toHashString());
        
        if (historico.size() > 12) {
            historico.erase(historico.begin());
        }

        bool souOnca = (lado_meu == 'o');
        int profundidade = 8; // gracas a Make/Unmake. se nãoera perto de 6
        
        vector<Move> movimentosCheck;
        if (souOnca) modelo.getOncaMovimentos(movimentosCheck);
        else modelo.getCachorroMovimentos(movimentosCheck);

        if (movimentosCheck.empty()) {
             sprintf(buf, "%c n\n", lado_meu);
             tabuleiro_envia(buf);
             continue;
        }

        Move melhorJogada = encontrarMelhorJogada(modelo, profundidade, souOnca, historico);

        string msg = melhorJogada.toString(lado_meu);
        strcpy(buf, msg.c_str());
        tabuleiro_envia(buf);
        
        cout << "Eu sou: " << lado_meu << " | Enviei: " << msg;
    }

    return 0;
}