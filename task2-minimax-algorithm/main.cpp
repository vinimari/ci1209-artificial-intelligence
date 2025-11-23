#include <iostream>
#include <vector>
#include <cstring>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <string> // Necessário para string

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

    // --- MUDANÇA 1: Criar o vetor de histórico fora do loop ---
    vector<string> historico;

    while(true) {
        // 2. Recebe estado do jogo
        tabuleiro_recebe(buf);
        
        // Separação de strings
        char *linha1 = strtok(buf, "\n");
        char *linha2 = strtok(NULL, "\n");
        char *strTabuleiro = strtok(NULL, ""); 
        
        if (!linha1 || !linha2) break;
        
        sscanf(linha1, "%c", &lado_meu);
        
        // 3. Atualiza Modelo
        BoardModel modelo;
        modelo.parseFromString(strTabuleiro);

        // --- MUDANÇA 2: Atualizar o histórico ---
        // Adiciona o hash do tabuleiro atual ao histórico
        historico.push_back(modelo.toHashString());
        
        // Limita o tamanho do histórico para não crescer infinitamente (ex: últimos 12 estados)
        // Isso permite repetição se o ciclo for muito longo, mas evita loops curtos imediatos.
        if (historico.size() > 12) {
            historico.erase(historico.begin());
        }

        bool souOnca = (lado_meu == 'o');
        int profundidade = 8; // Com a otimização Make/Unmake, podemos tentar 8!
        
        // Verifica se existem movimentos possíveis antes de chamar a IA
        vector<Move> movimentosCheck;
        if (souOnca) modelo.getOncaMovimentos(movimentosCheck);
        else modelo.getCachorroMovimentos(movimentosCheck);

        if (movimentosCheck.empty()) {
             sprintf(buf, "%c n\n", lado_meu);
             tabuleiro_envia(buf);
             continue;
        }

        // --- MUDANÇA 3: Passar o histórico para a IA ---
        Move melhorJogada = encontrarMelhorJogada(modelo, profundidade, souOnca, historico);

        // 5. Envia Resposta
        string msg = melhorJogada.toString(lado_meu);
        strcpy(buf, msg.c_str());
        tabuleiro_envia(buf);
        
        cout << "Eu sou: " << lado_meu << " | Enviei: " << msg;
    }

    return 0;
}