#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>
using grid = std::vector<std::vector<char>>;

// row, col
struct square
{
    int row;
    int col;

    square operator+(const square &other) const
    {
        square result;
        result.row = row + other.row;
        result.col = col + other.col;
        return result;
    }

    bool operator<(const square &other) const { return row < other.row && col < other.col; }

    bool operator==(const square &other) const { return row == other.row && col == other.col; }

    bool operator!=(const square &other) const { return !operator==(other); }
};

std::vector<square> directions = {
    {1, 0},  // DOWN
    {-1, 0}, // UP
    {0, 1},  // RIGHT
    {0, -1}  // LEFT
};

std::string directions_mapping = "DURL";

// Returns true if the square lies within the grid
bool is_valid(const grid &g, square s)
{
    int rows = g.size();
    int cols = g[0].size();
    return s.row >= 0 && s.col >= 0 && s.row < rows && s.col < cols;
}

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

void BFS(const grid &g, square start)
{
    std::queue<square> q;
    std::vector<std::vector<bool>> visited(g.size(), std::vector<bool>(g[0].size(), false));

    // Holds the direction from the parent to reach the current square
    grid from_grid(g.size(), std::vector<char>(g[0].size(), ' '));
    std::vector<std::vector<square>> from_square(g.size(), std::vector<square>(g[0].size()));
    square node;
    bool found_B = false;
    from_square[start.row][start.col] = start;


    // Mark the starting square as visited
    visited[start.row][start.col] = true;
    q.push(start);
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        if (g[node.row][node.col] == 'B')
        {
            // Reached the destination
            found_B = true;
            break;
        }
        // Add all adjacent non visited squares to the queue
        for (int i = 0; i < directions.size(); i++)
        {
            auto direction = directions[i];
            auto adj = node + direction;
            if (is_valid(g, adj) && g[adj.row][adj.col] != '#' && !visited[adj.row][adj.col])
            {
                visited[adj.row][adj.col] = true;
                //std::cout << "(" << adj.row << ", " << adj.col << ") <- (" << node.row << ", "
                //          << node.col << ")" << std::endl;
                from_square[adj.row][adj.col] = node;
                from_grid[adj.row][adj.col] = directions_mapping[i];
                q.push(adj);
            }
        }
    }
    if (!found_B)
    {
        std::cout << "NO" << std::endl;
    }
    else
    {
        std::cout << "YES" << std::endl;
        // Backtrack from B to A
        std::stack<char> path;
        while (true)
        {
            path.push(from_grid[node.row][node.col]);
            node = from_square[node.row][node.col];
            //std::cout << node.row << " " << node.col << std::endl;
            if (node == start)
                break;
        }
        std::cout << path.size() << std::endl;
        while(!path.empty()){
            std::cout << path.top();
            path.pop();
        }
        std::cout << std::endl;
    }
}

void solution(const grid &g)
{
    // First find the coordinates for start (A)
    square start;
    for (int i = 0; i < g.size(); i++)
    {
        for (int j = 0; j < g[0].size(); j++)
        {
            if (g[i][j] == 'A')
            {
                start = {i, j};
                break;
            }
        }
    }
    BFS(g, start);
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
    solution(g);
}