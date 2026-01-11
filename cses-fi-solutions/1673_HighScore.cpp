#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <stack>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    struct Edge
    {
        long long int from;
        long long int to;
        long long int weight;
    };

    vector<Edge> edges;
    long long int n, m;

    cin >> n >> m;

    vector<vector<long long int>> rev_adj(n+1); // Reverse adjacency list to find positive cycles

    for (long long int i = 0; i < m; i++)
    {
        long long int t1, t2, w;
        cin >> t1 >> t2 >> w;
        rev_adj[t2].push_back(t1);
        edges.push_back({t1, t2, w});
    }

    // Find the maximal score from source to destination
    // Use Bellman-Ford algorithm to find the maximum possible score
    // If a positive cycle is found (a cycle which has an increase in score), print -1
    // since it is possible to get an infinite score by following the cycle continuously

    long long int source = 1;
    long long int destination = n;

    const long long int NEG_INF = numeric_limits<long long int>::min();

    vector<long long int> dist(n + 1, NEG_INF);
    dist[source] = 0;

    // Repeat |V| - 1 times
    // Note: Here we have to maximize the score(distance), and not minimize it

    for (int i = 1; i < n; i++)
    {
        for (const auto &edge : edges)
        {
            // For the edge u-v, u itself is not reachable
            if (dist[edge.from] == NEG_INF)
                continue;

            // Perform edge relaxation
            auto new_dist = dist[edge.from] + edge.weight;
            if (new_dist > dist[edge.to])
            {
                dist[edge.to] = new_dist;
            }
        }
    }

    // Now check for a positive cycle (instead of negative cycles, since we are maximizing the
    // score)
    // Just checking for a cycle is not enough, the cycle must be part of some path
    // between the source and destination

    // Create a reverse adjacency list, to check if a vertex is part of a positive cycle, which is
    // also present in some path from source to destination.

    vector<bool> marked(n + 1, false);

    for (const auto &edge : edges)
    {
        // For the edge u-v, u itself is not reachable
        if (dist[edge.from] == NEG_INF)
            continue;

        // Perform edge relaxation
        auto new_dist = dist[edge.from] + edge.weight;
        if (new_dist > dist[edge.to])
        {
            // If a relaxation was performed, then there is a positive weight cycle
            // so we can get an arbitrarily high score, print -1
            // Also check if this cycle lies with the maximal path
            marked[edge.to] = true;
        }
    }

    // Run DFS From the destination vertex
    stack<long long int> stk;
    vector<bool> visited(n + 1, false);
    stk.push(destination);
    while (!stk.empty())
    {
        auto v = stk.top();
        stk.pop();
        if (visited[v])
            continue;
        if (marked[v])
        {
            cout << -1 << endl;
            return 0;
        }
        visited[v] = true;
        for (const auto &adj : rev_adj[v])
        {
            stk.push(adj);
        }
    }

    cout << dist[destination] << endl;
}
