#ifndef PUZZLE_SOLVER_HPP
#define PUZZLE_SOLVER_HPP

#include "puzzle/Board.hpp"

class Solver {
    class Solution {
    public:
        std::size_t moves() const;

        using const_iterator = std::vector<Board>::const_iterator;

        const_iterator begin() const;

        const_iterator end() const;

    private:
        std::vector<Board> m_moves;

        friend class Solver;

        Solution() = default;

        explicit Solution(const std::vector<Board>& moves);
    };

public:
    static Solution solve(const Board& initial);
};

#endif  // PUZZLE_SOLVER_HPP
