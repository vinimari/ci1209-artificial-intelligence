#include "heuristica.h"
#include <cstdlib>

int evaluate(const BoardModel& tabuleiro) {
    int vencedor;
    if (tabuleiro.isFim(vencedor)) {
        if (vencedor == 1) return 100000;
        if (vencedor == 2) return -100000;
    }

    int pontuacao = 0;
    
    pontuacao += (tabuleiro.getCachorrosPegos() * 2000);
    
    vector<Move> movimentosOnca;
    tabuleiro.getOncaMovimentos(movimentosOnca);
    pontuacao += (movimentosOnca.size() * 50);

    Coord j = tabuleiro.getOncaPos();
    if (j.r >= 5) pontuacao -= 100;

    // critério de desempate
    pontuacao += (rand() % 10); 

    return pontuacao;
}