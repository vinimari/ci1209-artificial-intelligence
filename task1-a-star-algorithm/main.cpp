#include <iostream>
#include "astar_solver.h"

int main() {
    AStarSolver solver;
    
    std::cout << "=== PROBLEMA 1 ===" << std::endl;
    std::vector<Action> solution1 = solver.solveProblem1();
    
    if (!solution1.empty()) {
        std::cout << "Solução encontrada com " << solution1.size() << " movimentos:" << std::endl;
        for (const Action& action : solution1) {
            std::cout << action.toString() << std::endl;
        }
    } else {
        std::cout << "Solução não encontrada para o problema 1." << std::endl;
    }
    
    std::cout << "\n=== PROBLEMA 2 ===" << std::endl;
    std::vector<Action> solution2 = solver.solveProblem2();
    
    if (!solution2.empty()) {
        std::cout << "Solução encontrada com " << solution2.size() << " movimentos:" << std::endl;
        for (const Action& action : solution2) {
            std::cout << action.toString() << std::endl;
        }
    } else {
        std::cout << "Solução não encontrada para o problema 2." << std::endl;
    }
    
    return 0;
}