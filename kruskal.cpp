#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define edge pair<int, int>
#define coords pair<int, int>
#define GO_UP (- 1)
#define GO_DOWN (+ 1)
#define GO_LEFT (- 1)
#define GO_RIGHT (+ 1)


bool isAround(int pos1, int pos2, int cols);

class Graph {
private:
    vector<pair<int, edge>> initial_graph;
    vector<pair<int, edge>> result_graph;  // mst
    set<int> walls;
    set<int> paths;
    int cols;
    int rows;
    int *parent;
    int V;  // number of vertices/nodes in graph
public:
    Graph(int cols, int rows);

    void addWeightedEdge(int u, int v, int w);

    int find_set(int i);

    void union_set(int u, int v);

    void kruskal();

    void print();

    bool edgeHasWalls(pair<int, int> edge_val);

    void checkAroundNewPath(pair<int, int> &edgePath);

    coords *toCoordinates(int position) const;

    int toPosition(int x, int y) const;

    bool canBePath(int pos1);

    void checkCanBePath(const pair<int, int> &edgePath, const pair<int, int> *coords1, int i, int j);

    bool hasCornerPath(int x, int y, int i, int i1);

    static bool contains(set<int> set1, int pos1);
};

Graph::Graph(int cols, int rows) {
    V = cols * rows;
    this->cols = cols;
    this->rows = rows;
    parent = new int[V];

    for (int i = 0; i < V; i++)
        parent[i] = i;

    initial_graph.clear();
    result_graph.clear();
    walls.clear();
    paths.clear();
}

void Graph::addWeightedEdge(int u, int v, int w) {
    initial_graph.emplace_back(w, edge(u, v));
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
    return walls.find(current_edge.first) != walls.end() || walls.find(current_edge.second) != walls.end();
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
        if (uRep != vRep) {
            result_graph.push_back(initial_graph[i]);
            paths.insert(current_edge.first);
            paths.insert(current_edge.second);
            checkAroundNewPath(current_edge);
            union_set(uRep, vRep);
        }
    }
}

void Graph::print() {
    cout << "Edge :"
         << " Weight" << endl;
    for (auto &i: result_graph) {
        cout << i.second.first << " - " << i.second.second << " : "
             << i.first;
        cout << endl;
    }
}

coords *Graph::toCoordinates(int position) const {
    return new coords(position / cols, position % cols);
}

int Graph::toPosition(int x, int y) const {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return -1;
    return x + y * cols;
}

void Graph::checkAroundNewPath(edge &edgePath) {
    pair<int, int> *coords1 = toCoordinates(edgePath.first);
    pair<int, int> *coords2 = toCoordinates(edgePath.second);
    for (int i = GO_LEFT; i <= GO_RIGHT; i++) {
        for (int j = GO_UP; j <= GO_DOWN; j++) {
            checkCanBePath(edgePath, coords1, i, j);
            checkCanBePath(edgePath, coords2, i, j);
        }
    }
}

void Graph::checkCanBePath(const pair<int, int> &edgePath, const pair<int, int> *coords1, int i, int j) {
    int newX = coords1->first + i;
    int newY = coords1->second + j;
    if (newX < 0 || newX >= cols)
        return;
    if (newY < 0 || newY >= rows)
        return;
    int checkPos = toPosition(newX, newY);
    if (checkPos != edgePath.first && checkPos != edgePath.second && !contains(walls, checkPos) &&
        !contains(paths, checkPos)) {
        if (!canBePath(checkPos)) {
            printf("Added to walls: %i(%i, %i)\n", checkPos, newX, newY);
            walls.insert(checkPos);
        }
    }
}

bool Graph::canBePath(int pos1) {
    pair<int, int> *coordsVal = toCoordinates(pos1);
    bool res = true;
    vector<int> verticals = vector<int>(2);
    verticals.push_back(GO_UP);
    verticals.push_back(GO_DOWN);
    vector<int> horizontals = vector<int>(2);
    verticals.push_back(GO_LEFT);
    verticals.push_back(GO_RIGHT);
    for (int &i: verticals) {
        for (int &j: horizontals) {
            if (hasCornerPath(coordsVal->first, coordsVal->second, i, j)){}
                return false;
        }
    }
    return res;
}

bool Graph::hasCornerPath(int x, int y, int vert, int horiz) {
    int transX = x + horiz;
    int transY = y + vert;
    int pos1 = toPosition(x, transY);
    int pos2 = toPosition(transX, y);
    int pos3 = toPosition(transX, transY);
    return contains(paths, pos1) && contains(paths, pos2) && contains(paths, pos3);
}

bool Graph::contains(set<int> set1, int el) {
    return set1.find(el) != set1.end();
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

Graph createLaberinthWithKrukal(int cols, int rows) {
    Graph g(cols, rows);
    int N = cols * rows;
    srand(time(nullptr));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (isAround(i, j, cols)) {
                int weight_edge = rand() % 5 + 2;
                g.addWeightedEdge(i, j, weight_edge);
            }
        }
    }
    int lastPoint = N - 1;
    addInitialEdges(0, cols, 1, g);
    addInitialEdges(lastPoint, lastPoint - 1, lastPoint - cols, g);
    return g;
}

bool isAround(int pos1, int pos2, int cols) {
    bool isVerticallyAround = pos1 == (pos2 + cols) || pos1 == (pos2 - cols);
    bool isHorizontallyAround = false;
    if (pos1 / cols == pos2 / cols)
        isHorizontallyAround = pos1 == pos2 + 1 || pos1 == pos2 - 1;
    return isVerticallyAround or isHorizontallyAround;
}


