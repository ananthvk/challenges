#include <iostream>
#include <iterator>
#include <sstream>
#include <stack>
#include <vector>
using grid = std::vector<std::vector<char>>;

std::ostream &operator<<(std::ostream &os, const grid &g)
{
    for (const auto &row : g)
    {
        for (const auto &col : row)
        {
            os << col;
        }
        os << std::endl;
    }
    return os;
}

void DFS(const grid &g, int m, int n, int start_row, int start_col, std::vector<std::vector<bool>> &visited)
{
    std::stack<std::pair<int, int>> stk;
    stk.push(std::make_pair(start_row, start_col));
    while (!stk.empty())
    {
        auto t = stk.top();
        stk.pop();
        // Process the node
        visited[t.first][t.second] = true;

        // Push all adjacent floors
        int row = t.first;
        int col = t.second;
        for (int i = -1; i <= 1; i += 2)
        {
            int nr = row + i;
            int nc = col + i;
            if (nr >= 0 && nr < m && g[nr][col] == '.')
            {
                if (!visited[nr][col])
                {
                    stk.push(std::make_pair(nr, col));
                }
            }
            if (nc >= 0 && nc < n && g[row][nc] == '.')
            {
                if (!visited[row][nc])
                {
                    stk.push(std::make_pair(row, nc));
                }
            }
        }
    }
}

int number_of_rooms(const grid &g, int m, int n)
{
    // Here is my approach:
    // rooms = 0
    // For each square in the grid
    //     If the square is not visited and it is a floor (.)
    //         rooms += 1
    //         Perform DFS(square) and mark all adjacent floors as visited
    int rooms = 0;
    // 0 means unvisited, 1 means visited
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

    for (int row = 0; row < m; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (g[row][col] == '.' && !visited[row][col])
            {
                rooms++;
                DFS(g, m, n, row, col, visited);
            }
        }
    }

    return rooms;
}

int main()
{
    int rows, cols;
    std::string line;
    grid g;
    std::cin >> rows >> cols;

    std::cin.ignore();

    for (int i = 0; i < rows; i++)
    {
        std::getline(std::cin, line);
        std::vector<char> row;
        row.reserve(cols);
        std::stringstream ss(line);
        std::copy(std::istream_iterator<char>(ss), std::istream_iterator<char>(),
                  std::back_inserter(row));
        g.push_back(row);
    }

    std::cout << number_of_rooms(g, rows, cols) << std::endl;
}