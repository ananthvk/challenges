// In this problem, we have to find a Hamiltonian cycle (but not the complete one, only a subset of
// vertices) This makes the solution easier, use DFS to find a cycle, then print that cycle
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <string>
#include <vector>
using graph = std::vector<std::vector<int>>;

bool DFS(graph &g, int u, std::vector<bool> &g_visited)
{
    struct Vertice
    {
        int parent;
        int v;
    };

    std::stack<Vertice> stk;
    std::vector<int> parent_array(g.size(), -1);
    parent_array[u] = u;
    stk.push({-1, u});

    while (!stk.empty())
    {
        auto v = stk.top();
        stk.pop();

        if (g_visited[v.v])
        {
            continue;
        }

        g_visited[v.v] = true;

        for (const auto &adjacent : g[v.v])
        {
            // std::cout << v.v << " -> " << adjacent << " Visited: " << g_visited[adjacent]
            //           << " Parent: " << v.parent << std::endl;
            if (adjacent == v.parent)
                continue;
            stk.push({v.v, adjacent});
            parent_array[adjacent] = v.v;
            if (g_visited[adjacent] && adjacent != v.parent)
            {
                auto init = adjacent;
                std::stack<int> soln;
                v.v = adjacent;
                std::set<int> cycle;
                while (true)
                {
                    // std::cout << "PUSH " << v.v << std::endl;
                    soln.push(v.v);
                    cycle.insert(v.v);
                    v.v = parent_array[v.v];
                    if (cycle.find(v.v) != cycle.end())
                    {
                        break;
                    }
                }
                soln.push(init);
                std::cout << (soln.size()) << std::endl;
                // auto start = soln.top();
                while (!soln.empty())
                {
                    std::cout << (soln.top() + 1) << ((soln.size() != 1) ? " " : "");
                    soln.pop();
                }
                std::cout << std::endl;

                return true;
            }
        }
    }
    return false;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    graph g;
    g.resize(n);
    for (int i = 0; i < m; i++)
    {
        int t1, t2;
        std::cin >> t1 >> t2;
        // Because this is an undirected graph
        t1--;
        t2--;
        g[t1].push_back(t2);
        g[t2].push_back(t1);
    }
    std::vector<bool> visited(g.size(), false);

    // Detect a cycle using DFS
    for (int i = 0; i < n; i++)
    {
        // If a vertex does not have any edges, skip it
        if (g[i].empty())
            continue;
        if (visited[i])
            continue;
        if (DFS(g, i, visited))
        {
            return 0;
        }
    }
    std::cout << "IMPOSSIBLE" << std::endl;
}
