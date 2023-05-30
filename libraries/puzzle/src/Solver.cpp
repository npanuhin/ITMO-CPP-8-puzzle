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
    std::set<Board> visited;

    queue.push(board);
    scores[board] = 0;

    while (!queue.empty()) {
        auto current = queue.top();
        if (current.is_goal()) {
            break;
        }
        queue.pop();
        visited.insert(current);

        auto empty_pos = current.empty_pos();
        for (auto [dx, dy] : adjacent) {
            int y = (int)empty_pos.first + dy;
            int x = (int)empty_pos.second + dx;
            if (0 <= y && y < (int)current.size() && 0 <= x && x < (int)current.size()) {
                auto v = current.swap(empty_pos, {y, x});

                unsigned score = scores[current] + v.score();
                if (visited.contains(v) && score >= scores[v]) {
                    continue;
                }
                scores[v] = score;
                parent[v] = current;
                if (!visited.contains(v)) {
                    queue.push(v);
                }
            }
        }
    }

    std::vector<Board> moves;

    moves.push_back(queue.top());
    while (moves.back().moves() != 0) {
        moves.push_back(parent[moves.back()]);
    }
    std::reverse(moves.begin(), moves.end());

    return Solution(moves);
}
