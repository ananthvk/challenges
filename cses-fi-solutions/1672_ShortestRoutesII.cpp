#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long int n, m, q;
    cin >> n >> m >> q;

    // A is a n x n matrix, representing the distance between a pair of vertices
    // Here -1 means that the distance is infinite (to avoid overflow issues)
    vector<vector<long long int>> A(n + 1, vector<long long int>(n + 1, -1));

    for (long long int i = 0; i < m; i++)
    {
        long long int t1, t2, w;
        cin >> t1 >> t2 >> w;
        // Since there can be multiple edges, only set the edge if the weight is lesser
        if (A[t1][t2] == -1 || (A[t1][t2] != -1 && w < A[t1][t2]))
        {
            A[t1][t2] = w;
            // Since this is an undirected graph, also add the other edge
            A[t2][t1] = w;
        }
    }

    // Use the Floyd-Warshall algorithm to solve the problem
    // All pairs shortest path problem
    // Running time of this algorithm is O(|V|^3),
    // We have a matrix of size |V| x |V|, say A, which represents the shortest distance from
    // vertex i to j, for A[i][j]
    // Initially set A[u][v] = weight of edge, for all edges in the graph
    // Then for all vertices, i,j we check if the distance(i, k) + distance(k, j) is less than distance(i, j)
    // i.e. for a pair of vertices, we check if a shorter path exists through all other vertices
    
    // Set the distance from vertex i to i as 0
    for (int i = 1; i <= n; i++)
        A[i][i] = 0;

    for (long long int k = 1; k <= n; k++)
    {
        for (long long int i = 1; i <= n; i++)
        {
            for (long long int j = 1; j <= n; j++)
            {
                // If any of the intermediate distances is infinite, skip
                if (A[i][k] == -1 || A[k][j] == -1)
                    continue;

                auto new_dist = A[i][k] + A[k][j];
                // If there is no known path from i to j, or the new distance is lesser than the
                // previous distance set this as the shortest distance
                if (A[i][j] == -1 || new_dist < A[i][j])
                    A[i][j] = new_dist;
            }
        }
    }

    /*
    cout << "------------------" << endl;
    for (const auto &row : A)
    {
        for (const auto &col : row)
        {
            cout << col << " ";
        }
        cout << endl;
    }
    cout << "------------------" << endl;
    */

    // Process the queries
    for (int i = 0; i < q; i++)
    {
        int t1, t2;
        cin >> t1 >> t2;
        cout << A[t1][t2] << endl;
    }
}