#include <iostream>
#include <set>
#include <valarray>


using namespace std;
#define MAX_GRID_LENGTH (100*100)
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


class GraphDFS {
private:
    int GRID_WIDTH;
    int GRID_HEIGHT;
    char grid[MAX_GRID_LENGTH];
    std::set<int> paths;
public:
    GraphDFS(int cols, int rows);

    void reset_grid();

    int to_pos(int x, int y);

    int is_in_bounds(int x, int y);

    void visit(int x, int y);

    void print();

    void start();

    int getNumTiles();

    bool isWall(int i);

    bool contains(set<int> set1, int el);

    pair<int, int> *toCoordinates(int i);

    int getCols();

    int getRows();

    void addWalls();

    bool checkCanBePath(int tile);

    int is_in_bounds(int pos);
};

GraphDFS::GraphDFS(int cols, int rows) {
    this->GRID_WIDTH = cols % 2 == 1 ? cols : cols + 1;
    this->GRID_HEIGHT = rows % 2 == 1 ? rows : rows + 1;
}

void GraphDFS::reset_grid() {
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; ++i) {
        grid[i] = '#';
    }
}

int GraphDFS::to_pos(int x, int y) {
    // Converts the two-dimensional index pair (x,y) into a
    // single-dimensional index. The result is y * ROW_WIDTH + x.
    return y * GRID_WIDTH + x;
}

int GraphDFS::is_in_bounds(int x, int y) {
    // Returns "true" if x and y are both in-bounds.
    if (x < 0 || x >= GRID_WIDTH) return false;
    if (y < 0 || y >= GRID_HEIGHT) return false;
    return true;
}

int GraphDFS::is_in_bounds(int pos) {
    // Returns "true" if x and y are both in-bounds.
    pair<int, int> *coords = toCoordinates(pos);
    return is_in_bounds(coords->first, coords->second);
}

void GraphDFS::visit(int x, int y) {
    grid[to_pos(x, y)] = ' ';
    paths.insert(to_pos(x, y));

    int dirs[4] = {NORTH, EAST, SOUTH, WEST};
    for (int &dir: dirs) {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dir;
        dir = temp;
    }
    for (int dir: dirs) {
        int dx = 0, dy = 0;
        switch (dir) {
            case NORTH:
                dy = -1;
                break;
            case SOUTH:
                dy = 1;
                break;
            case EAST:
                dx = 1;
                break;
            case WEST:
                dx = -1;
                break;
        }
        int x2 = x + (dx * 2);
        int y2 = y + (dy * 2);
        if (is_in_bounds(x2, y2)) {
            if (grid[to_pos(x2, y2)] == '#') {
                int pos = to_pos(x2 - dx, y2 - dy);
                grid[pos] = ' ';
                paths.insert(pos);
                visit(x2, y2);
            }
        }
    }
}

void GraphDFS::print() {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cout << grid[to_pos(x, y)];
        }
        cout << endl;
    }
}

void GraphDFS::start() {
    srand(time(nullptr));
    reset_grid();
    this->visit(1, 1);
    this->addWalls();
}

int GraphDFS::getNumTiles() {
    return this->GRID_WIDTH * this->GRID_HEIGHT;
}

bool GraphDFS::isWall(int i) {
    return !contains(paths, i);
}

bool GraphDFS::contains(std::set<int> set1, int el) {
    return set1.find(el) != set1.end();
}

pair<int, int> *GraphDFS::toCoordinates(int i) {
    return new std::pair<int, int>(i % this->GRID_WIDTH, i / this->GRID_WIDTH);
}

int GraphDFS::getCols() {
    return GRID_WIDTH;
}

int GraphDFS::getRows() {
    return GRID_HEIGHT;
}

void GraphDFS::addWalls() {
    for (int i = 0; i < (int) sqrt(getNumTiles())/3; i++) {
        int random_tile = rand() % getNumTiles();
        while (contains(paths, random_tile) || !checkCanBePath(random_tile)) {
            random_tile = rand() % getNumTiles();
        }
        paths.insert(random_tile);
        printf("%i\n", random_tile);
    }
}

bool GraphDFS::checkCanBePath(int tile) {
    pair<int, int> *coords = toCoordinates(tile);
    if (coords->first == 0 || coords->first == this->GRID_WIDTH-1)
        return false;
    if (coords->second == 0 || coords->second == this->GRID_HEIGHT-1)
        return false;
    int right = to_pos(coords->first + 1, coords->second);
    int left = to_pos(coords->first - 1, coords->second);
    int down = to_pos(coords->first, coords->second + 1);
    int up = to_pos(coords->first, coords->second - 1);
    if (!(is_in_bounds(right) && is_in_bounds(left) && is_in_bounds(down) && is_in_bounds(up)))
        return false;
    bool result = contains(paths, right) && contains(paths, left) && !contains(paths, up) && !contains(paths, down);
    result = result || !contains(paths, right) && !contains(paths, left) && contains(paths, up) && contains(paths, down);
    return result;
}

