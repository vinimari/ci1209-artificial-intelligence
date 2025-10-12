#include "heuristic.h"
#include <cmath>
#include <algorithm>

int Heuristic::problem1Heuristic(const ChessState& state, Position target) {
    // Encontrar posição do cavalo preto 'k'
    for (int i = 0; i < state.rows; i++) {
        for (int j = 0; j < state.cols; j++) {
            if (state.board[i][j] == 'k') {
                // Distância Manhattan dividida por 3 (aproximação para movimentos de cavalo)
                // Cavalo pode mover-se aproximadamente 3 casas de distância Manhattan por movimento
                return (abs(i - target.row) + abs(j - target.col) + 2) / 3;
            }
        }
    }
    return 0;
}

int Heuristic::problem2Heuristic(const ChessState& state, Position target, bool hasQueen) {
    if (!hasQueen) {
        // Procurar pelo peão
        for (int i = 0; i < state.rows; i++) {
            for (int j = 0; j < state.cols; j++) {
                if (state.board[i][j] == 'p') {
                    // Distância até (1,4) + distância estimada da rainha até o objetivo
                    // (1,4) em índices 1-based = (0,3) em 0-based
                    int pawnDist = abs(i - 0) + abs(j - 3);
                    int queenDist = std::max(abs(0 - target.row), abs(3 - target.col));
                    return pawnDist + queenDist;
                }
            }
        }
    } else {
        // Procurar pela rainha
        for (int i = 0; i < state.rows; i++) {
            for (int j = 0; j < state.cols; j++) {
                if (state.board[i][j] == 'q') {
                    // Rainha pode mover-se na diagonal, então usamos distância Chebyshev
                    return std::max(abs(i - target.row), abs(j - target.col));
                }
            }
        }
    }
    return 0;
}
