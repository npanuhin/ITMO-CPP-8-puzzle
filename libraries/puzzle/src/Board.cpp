#include "puzzle/Board.hpp"

Board Board::create_goal(const unsigned /*size*/) {
    return {};
}

Board Board::create_random(const unsigned /*size*/) {
    return {};
}

Board::Board(const std::vector<std::vector<unsigned>>& /*data*/) {}

std::size_t Board::size() const {
    return 0;
}

bool Board::is_goal() const {
    return true;
}

unsigned Board::hamming() const {
    return 0;
}

unsigned Board::manhattan() const {
    return 0;
}

std::string Board::to_string() const {
    return "<empty>";
}

bool Board::is_solvable() const {
    return true;
}
