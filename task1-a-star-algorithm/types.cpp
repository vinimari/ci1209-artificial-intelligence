#include "types.h"

std::string Action::toString() const {
    return std::string(1, piece) + " " +
           std::to_string(from.row + 1) + " " + std::to_string(from.col + 1) + " " +
           std::to_string(to.row + 1) + " " + std::to_string(to.col + 1);
}