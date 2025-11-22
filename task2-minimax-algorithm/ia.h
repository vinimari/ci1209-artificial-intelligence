#ifndef IA_H
#define IA_H

#include "modelo.h"

// Encontra a melhor jogada usando Minimax com poda Alfa-Beta
Move encontrarMelhorJogada(BoardModel tabuleiro, int profundidade, bool souOnca);

#endif
