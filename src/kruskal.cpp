#include <algorithm>
#include <iostream>
#include <vector>
#include <set>


class Graph {
private:
    std::vector<std::pair<int, std::pair<int, int>>> initial_graph;
    std::vector<std::pair<int, std::pair<int, int>>> result_graph;  // mst
    std::set<int> walls;
    std::set<int> paths;
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

    void printResult();

    bool edgeHasWalls(std::pair<int, int> edge_val);

    void checkAroundNewPath(std::pair<int, int> &edgePath);

    std::pair<int, int> *toCoordinates(int position) const;

    int toPosition(int x, int y) const;

    bool canBePath(int pos1);

    void checkCanBePath(const std::pair<int, int> &edgePath, const std::pair<int, int> *coords1, int i, int j);

    bool hasCornerPath(int x, int y, int i, int i1);

    static bool contains(std::set<int> set1, int pos1);

    void printMaze();

    void addWall(int i);

    void printInitial();

    bool isAround(int pos1, int pos2);

    bool isWall(int i);

    void addPath(int i);

    void checkArroundTilePath(const std::pair<int, int> &edgePath, const std::pair<int, int> *coords1);

    bool canFormASquare(std::pair<int, int> &pair);

    bool canFormASquareHorizontally(int first, int second);

    bool isPath(int i);

    bool canFormASquareHorizontally(const std::pair<int, int> *aCoords, const std::pair<int, int> *bCoords, int i);

    bool canFormASquareVertically(std::pair<int, int> *pPair, std::pair<int, int> *pPair1, int i);

    int getCols();

    int getRows();

    int getNumTiles();
};



#define GO_UP (- 1)
#define GO_DOWN (+ 1)
#define GO_LEFT (- 1)
#define GO_RIGHT (+ 1)
#define DEBUG 0
#define debug_print(args ...) if (DEBUG) printf(args)

bool isAround(int pos1, int pos2, int cols);

#define PATH_CHAR ' '

#define WALL_CHAR 'X'

Graph &initInnerWalls(int cols, Graph &g, int N);

void initOuterWalls(int cols, int rows, Graph &g);

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
    initial_graph.emplace_back(w, std::pair<int, int>(u, v));
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

bool Graph::edgeHasWalls(std::pair<int, int> current_edge) {
    return walls.find(current_edge.first) != walls.end() || walls.find(current_edge.second) != walls.end();
}

void Graph::kruskal() {
    int i, uRep, vRep;
    sort(initial_graph.begin(), initial_graph.end());
    for (i = 0; i < initial_graph.size(); i++) {
        std::pair<int, int> &current_edge = initial_graph[i].second;
        if (edgeHasWalls(current_edge) || canFormASquare(current_edge))
            continue;
        uRep = find_set(current_edge.first);
        vRep = find_set(current_edge.second);
        debug_print("p(%i, %i): %i-%i\n", current_edge.first, current_edge.second, uRep, vRep);
        if (uRep != vRep) {
            debug_print("\tAdded\n");
            result_graph.push_back(initial_graph[i]);
            paths.insert(current_edge.first);
            paths.insert(current_edge.second);
            checkAroundNewPath(current_edge);
            union_set(uRep, vRep);
        }
    }
    for (i = 0; i < this->V; i++) {
        if (!isPath(i) && !isWall(i))
            this->addWall(i);
    }
}

void Graph::printResult() {
    std::cout << "Edge :"
         << " Weight" << std::endl;
    for (auto &i: result_graph) {
        std::cout << i.second.first << " - " << i.second.second << " : "
             << i.first;
        std::cout << std::endl;
    }
}

void Graph::printInitial() {
    std::cout << "Edge :"
         << " Weight" << std::endl;
    for (auto &i: initial_graph) {
        std::cout << i.second.first << " - " << i.second.second << " : "
             << i.first;
        std::cout << std::endl;
    }
}

void Graph::printMaze() {
    char map[rows][cols];
    for (int pos: paths) {
        std::pair<int, int> *coord = toCoordinates(pos);
        map[coord->second][coord->first] = PATH_CHAR;
    }
    for (int pos: walls) {
        std::pair<int, int> *coord = toCoordinates(pos);
        map[coord->second][coord->first] = WALL_CHAR;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}


std::pair<int, int> *Graph::toCoordinates(int position) const {
    return new std::pair<int, int>(position % cols, position / cols);
}

int Graph::toPosition(int x, int y) const {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return -1;
    return x + y * cols;
}

void Graph::checkAroundNewPath(std::pair<int, int> &edgePath) {
    std::pair<int, int> *coords1 = toCoordinates(edgePath.first);
    std::pair<int, int> *coords2 = toCoordinates(edgePath.second);
    checkArroundTilePath(edgePath, coords1);
    checkArroundTilePath(edgePath, coords2);
}

void Graph::checkArroundTilePath(const std::pair<int, int> &edgePath, const std::pair<int, int> *coords1) {
    for (int i = GO_LEFT; i <= GO_RIGHT; i++) {
        for (int j = GO_UP; j <= GO_DOWN; j++) {
            checkCanBePath(edgePath, coords1, i, j);
        }
    }
}

void Graph::checkCanBePath(const std::pair<int, int> &edgePath, const std::pair<int, int> *coords1, int i, int j) {
    int newX = coords1->first + i;
    int newY = coords1->second + j;
    int checkPos = toPosition(newX, newY);
    if (checkPos == -1)
        return;
    debug_print("\tChecking p(%i, %i)=%i\n", newX, newY, checkPos);
    if (checkPos != edgePath.first && checkPos != edgePath.second) {
        if (!contains(walls, checkPos) && !contains(paths, checkPos)) {
            if (!canBePath(checkPos)) {
                debug_print("Added to walls: %i(%i, %i)\n", checkPos, newX, newY);
                walls.insert(checkPos);
            }
        }
    }
}

bool Graph::canBePath(int pos1) {
    std::pair<int, int> *coordsVal = toCoordinates(pos1);
    bool res = true;
    std::vector<int> verticals = std::vector<int>(2);
    verticals.push_back(GO_UP);
    verticals.push_back(GO_DOWN);
    std::vector<int> horizontals = std::vector<int>(2);
    verticals.push_back(GO_LEFT);
    verticals.push_back(GO_RIGHT);
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i != 0 && j != 0 && hasCornerPath(coordsVal->first, coordsVal->second, i, j)) {
                return false;
            }
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
    debug_print("\t\t(%i, %i) + (%i, %i) = (%i, %i) -> (%i/%s %i/%s %i/%s)\n", x, y, horiz, vert, transX, transY, pos1,
           contains(paths, pos1)?"true":"false", pos2, contains(paths, pos2)?"true":"false", pos3, contains(paths, pos3)?"true":"false");
    return contains(paths, pos1) && contains(paths, pos2) && contains(paths, pos3);
}

bool Graph::contains(std::set<int> set1, int el) {
    return set1.find(el) != set1.end();
}

void Graph::addWall(int i) {
    walls.insert(i);
}

void addInitialEdges(int point, int point2, int point3, Graph &g) {
    int randNum = rand() % 2;
    switch (randNum) {
        case 1:
            if (!g.isWall(point3)) {
                g.addWeightedEdge(point, point3, 1);
                g.addWeightedEdge(point3, point, 1);
            }
            break;
        case 0:
            if (!g.isWall(point2)) {
                g.addWeightedEdge(point, point2, 1);
                g.addWeightedEdge(point2, point, 1);
            }
            break;
    }
}

bool Graph::isAround(int pos1, int pos2) {
    bool isVerticallyAround = pos1 == (pos2 + cols) || pos1 == (pos2 - cols);
    bool isHorizontallyAround = false;
    if (pos1 / cols == pos2 / cols)
        isHorizontallyAround = pos1 == pos2 + 1 || pos1 == pos2 - 1;
    return isVerticallyAround or isHorizontallyAround;
}

bool Graph::isWall(int i) {
    return contains(walls, i);
}

bool Graph::isPath(int i) {
    return contains(paths, i);
}

void Graph::addPath(int i) {
    this->paths.insert(i);
}

bool Graph::canFormASquare(std::pair<int, int> &pair) {
    if (pair.first == pair.second - 1 || pair.first == pair.second + 1)
        return canFormASquareHorizontally(pair.first, pair.second);
    std::pair<int, int> *aCoords = toCoordinates(pair.first);
    std::pair<int, int> *bCoords = toCoordinates(pair.second);
    return canFormASquareVertically(aCoords, bCoords, 1) || canFormASquareVertically(aCoords, bCoords, - 1);
}

bool Graph::canFormASquareHorizontally(int first, int second) {
    std::pair<int, int> *aCoords = toCoordinates(first);
    std::pair<int, int> *bCoords = toCoordinates(second);
    return canFormASquareHorizontally(aCoords, bCoords, 1) || canFormASquareHorizontally(aCoords, bCoords, -1);
}

bool Graph::canFormASquareHorizontally(const std::pair<int, int> *aCoords, const std::pair<int, int> *bCoords, int i) {
    return isPath(toPosition(aCoords->first, aCoords->second + i)) && isPath(toPosition(bCoords->first, bCoords->second + i));
}

bool Graph::canFormASquareVertically(std::pair<int, int> *aCoords, std::pair<int, int> *bCoords, int i) {
    return isPath(toPosition(aCoords->first + i, aCoords->second)) && isPath(toPosition(bCoords->first + i, bCoords->second));
}

int Graph::getCols() {
    return this->cols;
}


int Graph::getRows() {
    return this->rows;
}

int Graph::getNumTiles() {
    return this->V;
}

Graph createLaberinthWithKruskal(int cols, int rows) {
    cols = cols + 2;
    rows = rows + 2;
    Graph g(cols, rows);
    int N = cols * rows;
    initOuterWalls(cols, rows, g);
    srand(time(nullptr));
    g = initInnerWalls(cols, g, N);
    return g;
}

void initOuterWalls(int cols, int rows, Graph &g) {
    for (int i = 0; i < cols; i++) {
        g.addWall(i);
        g.addWall(i + cols * (rows - 1));
    }
    for (int i = 0; i < rows; i++) {
        g.addWall(i * cols);
        g.addWall(i * cols + (cols - 1));
    }
}

Graph &initInnerWalls(int cols, Graph &g, int N) {
    for (int i = cols + 1; i < N - cols - 1; i++) {
        for (int j = cols + 1; j < N - cols - 1; j++) {
            if (g.isAround(i, j) && !g.isWall(i) && !g.isWall(j)) {
                int weight_edge = rand() % 5 + 2;
                g.addWeightedEdge(i, j, weight_edge);
            }
        }
    }
    int lastPoint = N - 2 - cols;
    addInitialEdges(cols + 1, cols * 2 + 1, cols + 2, g);
    addInitialEdges(lastPoint, lastPoint - 1, lastPoint - cols, g);
    g.addPath(cols+1);
    g.addPath(lastPoint);
    return g;
}


