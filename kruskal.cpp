// Kruskal's algorithm in C++

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define edge pair<int, int>

bool isAround(int i, int j, int xDim, int yDim);

class Graph {
private:
    vector<pair<int, edge > > G;  // graph
    vector<pair<int, edge > > T;  // mst
    int *parent;
    int V;  // number of vertices/nodes in graph
public:
    Graph(int V);

    void addWeightedEdge(int u, int v, int w);

    int find_set(int i);

    void union_set(int u, int v);

    void kruskal();

    void print();
};

Graph::Graph(int V) {
    parent = new int[V];

    for (int i = 0; i < V; i++)
        parent[i] = i;

    G.clear();
    T.clear();
}

void Graph::addWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}

int Graph::find_set(int i) {
    if (i == parent[i])
        return i;
    else
        // Else if i is not the parent of itself
        // Then i is not the representative of his set,
        // so we recursively call Find on its parent
        return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}

void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end());  // increasing weight
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]);  // add to tree
            union_set(uRep, vRep);
        }
    }
}

void Graph::print() {
    cout << "Edge :"
         << " Weight" << endl;
    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : "
             << T[i].first;
        cout << endl;
    }
}

Graph createLaberinthWithKrukal(int xDim, int yDim) {
    int N = xDim * yDim;
    Graph g(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isAround(i, j, xDim, yDim)) {
                g.addWeightedEdge(i, j, 1);
                printf("isAround %i, %i\n", i, j);
            }
        }
    }
    return g;
}

bool isAround(int i, int j, int xDim, int yDim) {
    bool isVerticallyAround = i == j + xDim || i == j - xDim;
    bool isHorizontallyAround = false;
    if (i / yDim == j / yDim)
        isHorizontallyAround = i == j + 1 || i == j - 1;
    return isVerticallyAround or isHorizontallyAround;
}