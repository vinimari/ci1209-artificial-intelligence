#ifndef TASK1_A_STAR_ALGORITHM_TYPES_H
#define TASK1_A_STAR_ALGORITHM_TYPES_H

#include <string>

struct Position {
    int row, col;

    explicit Position(int r = 0, int c = 0) : row(r), col(c) {}

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};

struct Piece {
    char type;
    Position pos;
    bool isWhite;

    explicit Piece(char t = '_', int r = 0, int c = 0, bool white = true)
        : type(t), pos(r, c), isWhite(white) {}
};

struct Action {
    char piece;
    Position from, to;

    Action(char p, Position f, Position t) : piece(p), from(f), to(t) {}

    std::string toString() const;

};

#endif //TASK1_A_STAR_ALGORITHM_TYPES_H