// Kruskal's algorithm in C++

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define edge pair<int, int>

bool isAround(int i, int j, int xDim, int yDim);


class Graph {
private:
    vector<pair<int, edge>> initial_graph;
    vector<pair<int, edge>> result_graph;  // mst
    set<int> walls;
    set<int> paths;


    int *parent;
    int V;  // number of vertices/nodes in graph
public:
    Graph(int V);

    void addWeightedEdge(int u, int v, int w);

    int find_set(int i);

    void union_set(int u, int v);

    void kruskal();

    void print();

    bool edgeHasWalls(pair<int, int> edge_val);

    void checkAroundWalls(pair<int, int> &pair);
};

Graph::Graph(int V) {
    parent = new int[V];

    for (int i = 0; i < V; i++)
        parent[i] = i;

    initial_graph.clear();
    result_graph.clear();
    walls.clear();
    paths.clear();
}

void Graph::addWeightedEdge(int u, int v, int w) {
    initial_graph.push_back(make_pair(w, edge(u, v)));
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

bool Graph::edgeHasWalls(edge current_edge) {
    return walls.find(current_edge.first) == walls.end() || walls.find(current_edge.second) == walls.end();
}

void Graph::kruskal() {
    int i, uRep, vRep;
    sort(initial_graph.begin(), initial_graph.end());
    for (i = 0; i < initial_graph.size(); i++) {
        edge &current_edge = initial_graph[i].second;
        if (edgeHasWalls(current_edge))
            continue;
        uRep = find_set(current_edge.first);
        vRep = find_set(current_edge.second);
        printf("%i-%i:: uRep: %i, vRep %i\n", current_edge.first, current_edge.second, uRep, vRep);
        if (uRep != vRep) {
            result_graph.push_back(initial_graph[i]);
            paths.insert(current_edge.first);
            paths.insert(current_edge.second);
            checkAroundWalls(current_edge);
            union_set(uRep, vRep);
        }
    }
}

void Graph::print() {
    cout << "Edge :"
         << " Weight" << endl;
    for (int i = 0; i < result_graph.size(); i++) {
        cout << result_graph[i].second.first << " - " << result_graph[i].second.second << " : "
             << result_graph[i].first;
        cout << endl;
    }
}

void Graph::checkAroundWalls(edge &pair) {

}

void addInitialEdges(int point, int point2, int point3, Graph &g) {
    int randNum = rand() % 3;
    switch (randNum) {
        case 2:
            g.addWeightedEdge(point, point2, 1);
            g.addWeightedEdge(point2, point, 1);
        case 1:
            g.addWeightedEdge(point, point3, 1);
            g.addWeightedEdge(point3, point, 1);
            break;
        case 0:
            g.addWeightedEdge(point, point2, 1);
            g.addWeightedEdge(point2, point, 1);
            break;
    }
}

Graph createLaberinthWithKrukal(int xDim, int yDim) {
    int N = xDim * yDim;
    Graph g(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isAround(i, j, xDim, yDim)) {
                int weight_edge = rand() % 5 + 2;
                g.addWeightedEdge(i, j, weight_edge);
            }
        }
    }
    int lastPoint = N - 1;
    srand(time(0));
    addInitialEdges(0, xDim, 1, g);
    addInitialEdges(lastPoint, lastPoint - 1, lastPoint - xDim, g);
    return g;
}

bool isAround(int i, int j, int xDim, int yDim) {
    bool isVerticallyAround = i == j + xDim || i == j - xDim;
    bool isHorizontallyAround = false;
    if (i / yDim == j / yDim)
        isHorizontallyAround = i == j + 1 || i == j - 1;
    return isVerticallyAround or isHorizontallyAround;
}