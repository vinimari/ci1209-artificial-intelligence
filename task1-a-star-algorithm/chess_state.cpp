// chess_state.cpp
#include "chess_state.h"
#include <iostream>
#include <string>

ChessState::ChessState(int r, int c) : rows(r), cols(c), g_cost(0), h_cost(0) {
    board.resize(rows, std::vector<char>(cols, '_'));
}

std::string ChessState::getStateKey() const {
    std::string key;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            key += board[i][j];
        }
    }
    return key;
}

int ChessState::getTotalCost() const {
    return g_cost + h_cost;
}

bool ChessState::operator>(const ChessState& other) const {
    return getTotalCost() > other.getTotalCost();
}

void ChessState::printBoard() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}

bool ChessState::isValidPosition(int r, int c) const {
    return r >= 0 && r < rows && c >= 0 && c < cols && board[r][c] != '#';
}

std::vector<Position> ChessState::getValidMoves(Position pos, char piece) const {
    std::vector<Position> moves;

    switch (piece) {
        case 'k': // Cavalo preto (Knight)
        case 'c': // Cavalo branco (White Knight)
            return getKnightMoves(pos);
        case 'b': // Bispo (Bishop)
            return getBishopMoves(pos);
        case 't': // Torre (Rook)
            return getRookMoves(pos);
        case 'p': // Peão (Pawn)
            return getPawnMoves(pos);
        case 'q': // Rainha (Queen)
            return getQueenMoves(pos);
    }
    return moves;
}

std::vector<Position> ChessState::getKnightMoves(Position pos) const {
    std::vector<Position> moves;
    int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; i++) {
        int nr = pos.row + dr[i];
        int nc = pos.col + dc[i];
        if (isValidPosition(nr, nc) && board[nr][nc] == '_') {
            moves.push_back(Position(nr, nc));
        }
    }
    return moves;
}

std::vector<Position> ChessState::getBishopMoves(Position pos) const {
    std::vector<Position> moves;
    int dr[] = {-1, -1, 1, 1};
    int dc[] = {-1, 1, -1, 1};

    for (int d = 0; d < 4; d++) {
        int nr = pos.row + dr[d];
        int nc = pos.col + dc[d];
        while (isValidPosition(nr, nc)) {
            if (board[nr][nc] == '_') {
                moves.push_back(Position(nr, nc));
            } else {
                break;
            }
            nr += dr[d];
            nc += dc[d];
        }
    }
    return moves;
}

std::vector<Position> ChessState::getRookMoves(Position pos) const {
    std::vector<Position> moves;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int d = 0; d < 4; d++) {
        int nr = pos.row + dr[d];
        int nc = pos.col + dc[d];
        while (isValidPosition(nr, nc)) {
            if (board[nr][nc] == '_') {
                moves.push_back(Position(nr, nc));
            } else {
                break;
            }
            nr += dr[d];
            nc += dc[d];
        }
    }
    return moves;
}

std::vector<Position> ChessState::getPawnMoves(Position pos) const {
    std::vector<Position> moves;
    // Peão move apenas para frente (assumindo movimento para cima)
    int nr = pos.row - 1;
    if (isValidPosition(nr, pos.col) && board[nr][pos.col] == '_') {
        moves.push_back(Position(nr, pos.col));
    }
    return moves;
}

std::vector<Position> ChessState::getQueenMoves(Position pos) const {
    std::vector<Position> moves;
    auto rookMoves = getRookMoves(pos);
    auto bishopMoves = getBishopMoves(pos);
    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());
    return moves;
}