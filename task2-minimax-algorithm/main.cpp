#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include <ctime>
#include <cstdlib>
// Inclui os módulos
#include "modelo.h"
#include "ia.h"

// Inclui a biblioteca C fornecida
extern "C" {
    #include "tabuleiro.h"
}

using namespace std;

int main(int argc, char **argv) {
    srand(time(NULL));
    char buf[512];
    char lado_meu;
    
    // 1. Conecta ao Controlador
    tabuleiro_conecta(argc, argv);

    while(true) {
        // 2. Recebe estado do jogo
        tabuleiro_recebe(buf);
        
        // Separação de strings (Parsing básico da mensagem do controlador)
        char *linha1 = strtok(buf, "\n"); // Lado atual
        char *linha2 = strtok(NULL, "\n"); // Último movimento
        char *strTabuleiro = strtok(NULL, ""); // Desenho do tabuleiro
        
        if (!linha1 || !linha2) break;
        
        sscanf(linha1, "%c", &lado_meu);
        
        // 3. Atualiza Modelo
        BoardModel modelo;
        modelo.parseFromString(strTabuleiro);

        bool souOnca = (lado_meu == 'o');
        int profundidade = 6; 
        
        // Verifica se existem movimentos possíveis antes de chamar a IA
        vector<Move> movimentosCheck;
        if (souOnca) modelo.getOncaMovimentos(movimentosCheck);
        else modelo.getCachorroMovimentos(movimentosCheck);

        if (movimentosCheck.empty()) {
             // Passa a vez ou sinaliza derrota (envia 'n')
             sprintf(buf, "%c n\n", lado_meu);
             tabuleiro_envia(buf);
             continue;
        }

        // 4. Executa a Busca (IA)
        Move melhorJogada = encontrarMelhorJogada(modelo, profundidade, souOnca);

        // 5. Envia Resposta
        string msg = melhorJogada.toString(lado_meu);
        strcpy(buf, msg.c_str());
        tabuleiro_envia(buf);
        
        cout << "Eu sou: " << lado_meu << " | Enviei: " << msg;
    }

    return 0;
}
