// For this problem, use adjacency list representation of graph and BFS to find the shortest path
// (if it exists)
#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>

// The vertices are represented by numbers from [0,n), i.e. 0, 1, 2.... n-1
class UndirectedGraph
{
    // a[i] is a vector which has all vertices adjacent to i
    std::vector<std::vector<int>> adj;

    void remove_single_edge(int u, int v)
    {
        // The vertex does not have any edge
        if (adj[u].empty())
        {
            throw std::logic_error("Edge not present in graph");
        }
        auto iter = std::find(adj[u].begin(), adj[u].end(), v);
        if (iter == adj[u].end())
            throw std::logic_error("Edge not present in graph");

        // Swap the vertex with the last vertex, then pop
        if (adj[u].size() > 1)
        {
            std::swap(*iter, adj[u].back());
        }
        adj[u].pop_back();
    }

  public:
    UndirectedGraph(int size) : adj(size) {}

    // Add an edge to connect u and v
    void add_edge(int u, int v)
    {
        if (u < 0 || u >= adj.size() || v < 0 || v >= adj.size())
            throw std::out_of_range("Invalid vertex number");

        // Don't care about parallel edges / self loop
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Remove an edge u-v from the graph, if the edge is not present an exception is raised
    void remove_edge(int u, int v)
    {
        if (u < 0 || u >= adj.size() || v < 0 || v >= adj.size())
            throw std::out_of_range("Invalid vertex number");

        remove_single_edge(u, v);
        remove_single_edge(v, u);
    }

    // Returns all vertices adjacent to u
    const std::vector<int> &adjacent(int u) const
    {
        if (u < 0 || u >= adj.size())
            throw std::out_of_range("Invalid vertex number");

        return adj[u];
    }

    void debug(int inc = 1) const
    {
        for (size_t i = 0; i < adj.size(); i++)
        {
            std::cout << (i + inc) << ": ";
            for (const auto &e : adj[i])
                std::cout << (e + inc) << " ";
            std::cout << std::endl;
        }
    }

    int size() const { return static_cast<int>(adj.size()); }
};

// Returns a vector which represents a path of vertices from source to target if it exists
// Otherwise, returns an empty vector
auto BFS(UndirectedGraph &g, int source, int target)
{
    if (source < 0 || source >= g.size() || target < 0 || target >= g.size())
        throw std::out_of_range("Invalid vertex number");

    std::vector<bool> visited(g.size(), false);
    std::vector<int> from(g.size(), -1);
    std::queue<int> q;
    std::deque<int> path;

    q.push(source);
    visited[source] = true;
    from[source] = source;

    while (!q.empty())
    {
        int vertex = q.front();
        q.pop();

        if (vertex == target)
        {
            // Found the destination vertex
            while (1)
            {
                path.push_front(vertex);
                vertex = from[vertex];
                if (vertex == source)
                {
                    path.push_front(vertex);
                    break;
                }
            }
            break;
        }

        // Add all non visited adjacent vertices to the queue
        for (const auto &adjacent : g.adjacent(vertex))
        {
            if (!visited[adjacent])
            {
                q.push(adjacent);
                from[adjacent] = vertex;
                visited[adjacent] = true;
            }
        }
    }
    return path;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    UndirectedGraph u(n);
    for (int i = 0; i < m; i++)
    {
        int t1, t2;
        std::cin >> t1 >> t2;
        u.add_edge(t1 - 1, t2 - 1);
    }
    auto path = BFS(u, 0, n - 1);
    if (path.empty())
    {
        std::cout << "IMPOSSIBLE" << std::endl;
    }
    else
    {
        std::cout << path.size() << std::endl;
        for (const auto &v : path)
            std::cout << (v + 1) << " ";
        std::cout << std::endl;
    }
}