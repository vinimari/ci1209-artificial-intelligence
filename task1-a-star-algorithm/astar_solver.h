#ifndef TASK1_A_STAR_ALGORITHM_ASTAR_SOLVER_H
#define TASK1_A_STAR_ALGORITHM_ASTAR_SOLVER_H

#include "priority_queue.h"
#include "chess_state.h"
#include "types.h"
#include <unordered_set>

class AStarSolver {
private:
    PriorityQueue<ChessState> openSet;
    std::unordered_set<std::string> closedSet;

    std::vector<Action> aStar(ChessState initial, Position target, int problem);
    bool isGoalState(const ChessState& state, Position target, int problem);
    std::vector<ChessState> generateSuccessors(const ChessState& current, Position target, int problem);

public:
    std::vector<Action> solveProblem1();
    std::vector<Action> solveProblem2();
};

#endif //TASK1_A_STAR_ALGORITHM_ASTAR_SOLVER_H