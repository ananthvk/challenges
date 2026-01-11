#include <iostream>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>

// For this problem, use Disjoint set union data structure (Union-Find)
// Perform Union-Find and find the total number of disjoint components, let this be d
// The number of roads necessary is equal to d - 1, i.e one edge which between each disjoint
// component To print the required roads, take the root of each component, and connect it with the
// root of the next component

// Create a union find data structure with path compression and by rank

class UnionFind
{
    // At the beginning, each vertex is disjoint and has values 0, 1, 2, 3 ....
    // If j = arr[i], It means that i's parent is j
    std::vector<size_t> vertices;

    // Holds the size of subtree for each node, for example a[1] is the size of subtree which has 1
    // as its root, initially set to 1
    std::vector<size_t> subtree_size;

    size_t n_components;

  public:
    UnionFind(size_t n) : vertices(n), subtree_size(n, 1), n_components(n)
    {
        std::iota(vertices.begin(), vertices.end(), 0);
    }

    // Union operation
    // Connects vertex p and q
    void connect(size_t u, size_t v)
    {
        // Check if p and q are valid vertices
        if (u < 0 || u >= vertices.size() || v < 0 || v >= vertices.size())
            throw std::domain_error("Invalid vertex, should be between [0, |V|)");

        size_t u_root = find(u);
        size_t v_root = find(v);

        // The components are already connected
        if (u_root == v_root)
            return;

        // The components are not connected, we are going to merge two components into one
        // Reduce the number of components by 1
        --n_components;

        // Performs union by size to improve complexity
        // We need to make the smaller tree a subtree of the larger tree
        if (subtree_size[u_root] < subtree_size[v_root])
        {
            std::swap(u_root, v_root);
        }

        // u_root is the tree with larger size
        vertices[v_root] = u_root;
        subtree_size[u_root] += subtree_size[v_root];
    }

    // Returns a component id, of which this vertex is a part of, also performs path compression
    size_t find(size_t u)
    {
        if (u < 0 || u >= vertices.size())
        {
            throw std::domain_error("Invalid vertex, should be between [0, |V|)");
        }
        // When a[i] is equal to i, this is the topmost root of the tree
        while (u != vertices[u])
        {
            // Path compression
            vertices[u] = vertices[vertices[u]];
            u = vertices[u];
        }
        return u;
    }

    // Returns the number of components
    size_t components() const { return n_components; }

    void dbg()
    {
        std::copy(vertices.begin(), vertices.end(), std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
        std::copy(subtree_size.begin(), subtree_size.end(),
                  std::ostream_iterator<size_t>(std::cout, " "));
        std::cout << std::endl;
    }

    // Get all root vertices in the component tree
    std::vector<size_t> get_roots() const
    {
        std::vector<size_t> result;
        for (size_t i = 0; i < vertices.size(); i++)
        {
            if (i == vertices[i])
                result.push_back(i);
        }
        return result;
    }
};

int main()
{
    int m, n;
    std::cin >> n >> m;
    UnionFind uf(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        // 1-indexed to 0-indexed
        uf.connect(u - 1, v - 1);
    }
    std::cout << uf.components() - 1 << std::endl;
    auto components = uf.get_roots();

    for (size_t i = 1; i < components.size(); i++)
    {
        std::cout << (components[i - 1] + 1) << " " << (components[i] + 1) << std::endl;
    }
}
