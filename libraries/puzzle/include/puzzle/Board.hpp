#ifndef PUZZLE_BOARD_HPP
#define PUZZLE_BOARD_HPP

#include <string>
#include <vector>

class Board {
public:
    static Board create_goal(unsigned size);

    static Board create_random(unsigned size);

    Board() = default;

    explicit Board(const std::vector<std::vector<unsigned>>& data);

    std::size_t size() const;

    bool is_goal() const;

    unsigned hamming() const;

    unsigned manhattan() const;

    std::string to_string() const;

    bool is_solvable() const;

    friend bool operator==(const Board& /*lhs*/, const Board& /*rhs*/) { return true; }

    friend bool operator!=(const Board& /*lhs*/, const Board& /*rhs*/) { return false; }

    friend std::ostream& operator<<(std::ostream& out, const Board& board) { return out << board.to_string(); }
};

#endif  // PUZZLE_BOARD_HPP
