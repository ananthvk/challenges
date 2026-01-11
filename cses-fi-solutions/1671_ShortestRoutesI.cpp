#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class WeightedDirectedGraph
{
    struct Edge
    {
        long long int vertex;
        long long int weight;
    };

    // Adjacency list representation
    vector<vector<Edge>> adj;

  public:
    WeightedDirectedGraph(long long int sz) : adj(sz) {}

    // Adds a weighted directed edge from u->v
    void add(long long int u, long long int v, long long int w)
    {
        if (u < 0 || u >= adj.size() || v < 0 || v >= adj.size())
            throw std::out_of_range("Invalid vertex number");
        adj[u].push_back({v, w});
    }

    const vector<Edge> &adjacent(long long int u) const
    {
        if (u < 0 || u >= adj.size())
            throw std::out_of_range("Invalid vertex number");
        return adj[u];
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long int n, m;
    cin >> n >> m;

    WeightedDirectedGraph g(n);

    for (long long int i = 0; i < m; i++)
    {
        long long int t1, t2, w;
        cin >> t1 >> t2 >> w;
        g.add(t1 - 1, t2 - 1, w);
    }

    // Use Dijkstra's algorithm to solve this problem
    // Note: A decrease-key priority queue is required, but a normal priority queue also works
    // at the cost of a little performance, since useless edges are present in the queue.

    // Pair of distance, vertex,
    priority_queue<pair<long long int, long long int>,
                   std::vector<std::pair<long long int, long long int>>,
                   std::greater<std::pair<long long int, long long int>>>
        pq;

    long long int source = 0;

    // Add the source vertex to priority queue, with distance 0
    pq.push(make_pair(0, source));
    vector<long long int> dist(n, -1);
    vector<bool> visited(n, false);
    dist[source] = 0;

    while (!pq.empty())
    {
        // Choose the vertex with the smallest distance
        auto v = pq.top();
        pq.pop();

        // This node has already been processed
        if (visited[v.second])
            continue;

        // Check all adjacent vertices
        for (const auto &adj : g.adjacent(v.second))
        {
            // If the distance is -1, the vertex is unexplored, i.e. infinite distance, so just set
            // the distance Check if going through v reduces the distance, if so, perform edge
            // relaxation
            if ((dist[adj.vertex] == -1) || (v.first + adj.weight) < dist[adj.vertex])
            {
                dist[adj.vertex] = v.first + adj.weight;
                pq.push(make_pair(dist[adj.vertex], adj.vertex));
            }
        }
        visited[v.second] = true;
    }
    for (const auto &d : dist)
    {
        cout << d << " ";
    }
    cout << endl;
}