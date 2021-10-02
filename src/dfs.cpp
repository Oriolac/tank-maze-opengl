#include <iostream>
#include <set>


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

void GraphDFS::visit(int x, int y) {
    // Starting at the given index, recursively visits every direction in a
    // randomized order.
    // Set my current location to be an empty passage.
    grid[to_pos(x, y)] = ' ';
    paths.insert(to_pos(x, y));

    // Create an local array containing the 4 directions and shuffle their order.
    int dirs[4] = {NORTH, EAST, SOUTH, WEST};
    for (int &dir: dirs) {
        int r = rand() & 3;
        int temp = dirs[r];
        dirs[r] = dir;
        dir = temp;
    }
    // Loop through every direction and attempt to visit that direction.
    for (int dir: dirs) {
        // dx,dy are offsets from current location. Set them based
        // on the next direction I wish to try.
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
    // Displays the finished maze to the screen.
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            cout << grid[to_pos(x, y)];
        }
        cout << endl;
    }
}

void GraphDFS::start() {
    srand(time(0)); // seed random number generator.
    reset_grid();
    this->visit(1, 1);
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

