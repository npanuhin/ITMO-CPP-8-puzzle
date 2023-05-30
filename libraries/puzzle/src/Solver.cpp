#include "puzzle/Solver.hpp"

#include <algorithm>
#include <map>
#include <queue>
#include <set>

Solver::Solution::Solution(const std::vector<Board> &moves) : m_moves(moves) {}

std::size_t Solver::Solution::moves() const {
    return m_moves.empty() ? 0 : m_moves.size() - 1;
}
Solver::Solution::const_iterator Solver::Solution::begin() const {
    return m_moves.begin();
}

Solver::Solution::const_iterator Solver::Solution::end() const {
    return m_moves.end();
}

Solver::Solution Solver::solve(const Board &board) {
    if (!board.is_solvable())
        return {};

    std::vector<std::pair<int, int>> adjacent = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    auto score_comp = [](const Board &left, const Board &right) { return left.score() > right.score(); };

    std::priority_queue<Board, std::vector<Board>, decltype(score_comp)> queue(score_comp);
    std::map<Board, Board> parent;
    std::map<Board, unsigned> scores;
    std::set<Board> used;

    queue.push(board);
    scores[board] = 0;

    while (!queue.empty()) {
        auto current = queue.top();
        if (current.is_goal()) {
            break;
        }
        queue.pop();
        used.insert(current);

        auto empty_pos = current.empty_pos();
        for (auto [dx, dy] : adjacent) {
            int y = (int)empty_pos.first + dy;
            int x = (int)empty_pos.second + dx;
            if (0 <= y && y < (int)current.size() && 0 <= x && x < (int)current.size()) {
                auto v = current.swap(empty_pos, {y, x});

                unsigned score = scores[current] + v.score();
                if (used.count(v) && score >= scores[v]) {
                    continue;
                }
                scores[v] = score;
                parent[v] = current;
                if (!used.count(v)) {
                    queue.push(v);
                }
            }
        }
    }

    std::vector<Board> m_moves;

    m_moves.push_back(queue.top());
    while (m_moves.back() != board) {
        m_moves.push_back(parent[m_moves.back()]);
    }
    std::reverse(m_moves.begin(), m_moves.end());

    return Solution(m_moves);
}
