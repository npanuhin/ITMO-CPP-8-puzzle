#ifndef PUZZLE_SOLVER_HPP
#define PUZZLE_SOLVER_HPP

#include "puzzle/Board.hpp"

class Solver {
    class Solution {
    public:
        std::size_t moves() const { return 0; }

        using const_iterator = std::vector<Board>::const_iterator;

        const_iterator begin() const { return m_moves.begin(); }

        const_iterator end() const { return m_moves.end(); }

    private:
        // FIXME:
        std::vector<Board> m_moves;
    };

public:
    static Solution solve(const Board& initial);
};

#endif  // PUZZLE_SOLVER_HPP
