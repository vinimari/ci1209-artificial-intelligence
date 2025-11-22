#ifndef HEURISTICA_H
#define HEURISTICA_H

#include "modelo.h"

// Calcula o valor estático de um tabuleiro.
// Positivo bom para Onça, Negativo bom para Cães.
int evaluate(const BoardModel& tabuleiro);

#endif
