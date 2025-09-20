#ifndef TASK1_A_STAR_ALGORITHM_HEURISTIC_H
#define TASK1_A_STAR_ALGORITHM_HEURISTIC_H

#include "chess_state.h"
#include "types.h"

class Heuristic {
public:
    static int problem1Heuristic(const ChessState& state, Position target);
    static int problem2Heuristic(const ChessState& state, Position target, bool hasQueen);
};

#endif //TASK1_A_STAR_ALGORITHM_HEURISTIC_H