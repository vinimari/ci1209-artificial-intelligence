#ifndef IA_H
#define IA_H

#include "modelo.h"

Move encontrarMelhorJogada(BoardModel tabuleiro, int profundidade, bool souOnca, const vector<string>& historico);

#endif