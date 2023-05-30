#include "puzzle/Board.hpp"

#include <algorithm>
#include <random>

Board Board::create_goal(const unsigned size) {
    std::vector<std::vector<unsigned>> data(size, std::vector<unsigned>(size));
    unsigned value = 1;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            data[i][j] = value++;
        }
    }
    data[size - 1][size - 1] = 0;
    return Board(data);
}

Board Board::create_random(const unsigned size) {
    std::vector<unsigned> shuffled(size * size);
    std::iota(shuffled.begin(), shuffled.end(), 0);
    std::shuffle(shuffled.begin(), shuffled.end(), std::mt19937{std::random_device{}()});

    std::vector<std::vector<unsigned>> data(size, std::vector<unsigned>(size));
    for (size_t i = 0, k = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            data[i][j] = shuffled[k++];
        }
    }
    return Board(data);
}

Board::Board(const std::vector<std::vector<unsigned>>& data, const unsigned moves)
    : m_table(data), m_moves_count(moves) {
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data.size(); j++) {
            if (data[i][j] == 0) {
                m_empty_pos = std::make_pair(i, j);
                break;
            }
        }
    }
}

std::size_t Board::size() const {
    return m_table.size();
}

unsigned Board::moves() const {
    return m_moves_count;
}

bool Board::is_goal() const {
    return hamming() == 0;
}

unsigned Board::hamming() const {
    unsigned count  = 0;
    unsigned target = 1;
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            if (m_table[i][j] != target++) {
                count++;
            }
        }
    }
    if (size() > 0 && m_table[size() - 1][size() - 1] == 0) {
        count -= 1;
    }
    return count;
}

unsigned Board::manhattan() const {
    unsigned summ   = 0;
    unsigned target = 1;
    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            if (m_table[i][j] != target++ && m_table[i][j] != 0) {
                unsigned should_be_in_row = abs((int)((m_table[i][j] - 1) / size()) - (int)i);
                unsigned should_be_in_col = abs((int)((m_table[i][j] - 1) % size()) - (int)j);
                summ += should_be_in_row + should_be_in_col;
            }
        }
    }
    return summ;
}

unsigned Board::score() const {
    // return (unsigned)(moves() / 2.8) + manhattan();
    return moves() + (unsigned)(2.85 * manhattan());
}

std::string Board::to_string() const {
    std::string result;
    for (const auto& row : m_table) {
        for (auto item : row) {
            result += (item ? std::to_string(item) : "_") + ' ';
        }
        result += '\n';
    }
    return result;
}

bool Board::is_solvable() const {
    if (is_goal())
        return true;

    bool parity = (size() % 2 == 0) && (m_empty_pos.first % 2 == 0);

    for (size_t i = 0; i < size(); i++) {
        for (size_t j = 0; j < size(); j++) {
            if (!m_table[i][j])
                continue;

            for (size_t y = i; y < size(); y++) {
                for (size_t x = 0; x < size(); x++) {
                    if (!m_table[y][x])
                        continue;

                    if (y > i || x > j) {
                        parity ^= (m_table[i][j] > m_table[y][x]);
                    }
                }
            }
        }
    }
    return !parity;
}

std::pair<unsigned, unsigned> Board::empty_pos() const {
    return m_empty_pos;
}

Board Board::swap(std::pair<unsigned, unsigned> a, std::pair<unsigned, unsigned> b) const {
    auto result = m_table;
    std::swap(result[a.first][a.second], result[b.first][b.second]);
    return Board(result, moves() + 1);
}

const std::vector<unsigned>& Board::operator[](const std::size_t i) const {
    return m_table[i];
}

bool operator==(const Board& lhs, const Board& rhs) {
    return lhs.m_table == rhs.m_table;
}

bool operator!=(const Board& lhs, const Board& rhs) {
    return lhs.m_table != rhs.m_table;
}

bool operator<(const Board& lhs, const Board& rhs) {
    for (size_t i = 0; i < lhs.size(); i++) {
        for (size_t j = 0; j < lhs.size(); j++) {
            if (lhs[i][j] != rhs[i][j]) {
                return lhs[i][j] < rhs[i][j];
            }
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& out, const Board& board) {
    return out << board.to_string();
}
