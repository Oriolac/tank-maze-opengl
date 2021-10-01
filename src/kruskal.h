#define edge std::pair<int, int>
#define coords std::pair<int, int>

class Graph {
private:
    std::vector<std::pair<int, edge>> initial_graph;
    std::vector<std::pair<int, edge>> result_graph;  // mst
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

    coords *toCoordinates(int position) const;

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
};

