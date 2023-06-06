#ifndef PUZZLE_BOARD_HPP
#define PUZZLE_BOARD_HPP

#include <optional>
#include <string>
#include <vector>

class Board {
public:
    static Board create_goal(unsigned size);

    static Board create_random(unsigned size);

    Board() = default;

    explicit Board(const std::vector<std::vector<unsigned>>& data, const unsigned moves = 0);

    std::size_t size() const;

    unsigned moves() const;

    bool is_goal() const;

    unsigned hamming() const;

    unsigned manhattan() const;

    unsigned score() const;

    std::string to_string() const;

    bool is_solvable() const;

    std::pair<unsigned, unsigned> empty_pos() const;

    Board swap(std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned>) const;

    const std::vector<unsigned>& operator[](const std::size_t i) const;

    friend bool operator==(const Board& lhs, const Board& rhs);

    friend bool operator!=(const Board& lhs, const Board& rhs);

    friend bool operator<(const Board& lhs, const Board& rhs);

    friend std::ostream& operator<<(std::ostream& out, const Board& board);

private:
    std::vector<std::vector<unsigned>> m_table;
    std::pair<unsigned, unsigned> m_empty_pos;
    unsigned m_moves_count = 0;

    mutable std::optional<unsigned> m_score = std::nullopt;
    mutable std::optional<unsigned> m_hamming = std::nullopt;
};

#endif  // PUZZLE_BOARD_HPP
