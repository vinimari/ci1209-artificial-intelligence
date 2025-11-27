#ifndef IA_H
#define IA_H

#include "modelo.h"
int minimax(BoardModel& tabuleiro, int profundidade, int alpha, int beta, bool maxOnca, int profundidadeInicial, const vector<string>& historico);
Move encontrarMelhorJogada(BoardModel tabuleiro, int profundidade, bool souOnca, const vector<string>& historico);

#endif