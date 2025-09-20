#ifndef TASK1_A_STAR_ALGORITHM_CHESS_STATE_H
#define TASK1_A_STAR_ALGORITHM_CHESS_STATE_H

#include "types.h"
#include <vector>

class ChessState {
public:
    std::vector<std::vector<char>> board;
    int rows, cols;
    std::vector<Action> path;
    int g_cost;
    int h_cost;

    ChessState(int r, int c);

    std::string getStateKey() const;
    int getTotalCost() const;
    bool operator>(const ChessState& other) const;
    void printBoard() const;
    bool isValidPosition(int r, int c) const;
    std::vector<Position> getValidMoves(Position pos, char piece) const;

private:
    std::vector<Position> getKnightMoves(Position pos) const;
    std::vector<Position> getBishopMoves(Position pos) const;
    std::vector<Position> getRookMoves(Position pos) const;
    std::vector<Position> getPawnMoves(Position pos) const;
    std::vector<Position> getQueenMoves(Position pos) const;
};

#endif //TASK1_A_STAR_ALGORITHM_CHESS_STATE_H