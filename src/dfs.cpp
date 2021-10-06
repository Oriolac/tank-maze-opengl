#include <iostream>
#include <set>
#include <valarray>
#include "utils/GraphInterface.h"


using namespace std;
#define MAX_GRID_LENGTH (100*100)
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


class GraphDFS : public GraphInterface {
private:
    char grid[MAX_GRID_LENGTH]{};
    std::set<int> paths;
public:
    GraphDFS(int cols, int rows) : GraphInterface(cols, rows) {
        this->cols = cols % 2 == 1 ? cols : cols + 1;
        this->rows = rows % 2 == 1 ? rows : rows + 1;
    }

    void reset_grid();

    int to_pos(int x, int y);

    int is_in_bounds(int x, int y);

    void dfs(int x, int y);

    void print() override;

    void start() override {
        srand(time(nullptr));
        reset_grid();
        this->dfs(1, 1);
        this->add_extra_paths();
    }

    int getNumTiles() override {
        return getCols() * getRows();
    }

    bool isWall(int i) override {
        return !contains(paths, i);
    }

    bool contains(set<int> set1, int el);

    pair<int, int> *toCoordinates(int i) override {
        return new std::pair<int, int>(i % this->getCols(), i / this->getCols());
    }

    int getCols() override {
        return cols;
    }

    int getRows() override {
        return rows;
    }

    void add_extra_paths();

    bool check_can_be_path(int tile);

    int is_in_bounds(int pos);

    int cols;
    int rows;
};

void GraphDFS::reset_grid() {
    for (int i = 0; i < getCols() * getRows(); ++i) {
        grid[i] = '#';
    }
}

int GraphDFS::to_pos(int x, int y) {
    // Converts the two-dimensional index pair (x,y) into a
    // single-dimensional index. The result is y * ROW_WIDTH + x.
    return y * getCols() + x;
}

int GraphDFS::is_in_bounds(int x, int y) {
    // Returns "true" if x and y are both in-bounds.
    if (x < 0 || x >= getCols()) return false;
    if (y < 0 || y >= getRows()) return false;
    return true;
}

int GraphDFS::is_in_bounds(int pos) {
    // Returns "true" if x and y are both in-bounds.
    pair<int, int> *coords = toCoordinates(pos);
    return is_in_bounds(coords->first, coords->second);
}

void GraphDFS::dfs(int x, int y) {
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
                dfs(x2, y2);
            }
        }
    }
}

void GraphDFS::print() {
    for (int y = getRows() - 1; y >= 0 ; y--) {
        for (int x = 0; x < getCols(); ++x) {
            cout << grid[to_pos(x, y)];
        }
        cout << endl;
    }
}


bool GraphDFS::contains(std::set<int> set1, int el) {
    return set1.find(el) != set1.end();
}


void GraphDFS::add_extra_paths() {
    int sqrt_tiles = (int) sqrt(getNumTiles());
    int limit = 0;
    switch (sqrt_tiles) {
        case 3:
        case 5:
            limit = 0;
            break;
        default:
            limit = sqrt_tiles > 8 ? (int) 7 * sqrt_tiles / 8 - 3 : 2;
    }
    for (int i = 0; i < limit; i++) {
        int random_tile = rand() % getNumTiles();
        while (contains(paths, random_tile) || !check_can_be_path(random_tile)) {
            random_tile = rand() % getNumTiles();
        }
        grid[random_tile] = ' ';
        paths.insert(random_tile);
    }
}

bool GraphDFS::check_can_be_path(int tile) {
    pair<int, int> *coords = toCoordinates(tile);
    if (coords->first == 0 || coords->first == this->getCols() - 1)
        return false;
    if (coords->second == 0 || coords->second == this->getRows() - 1)
        return false;
    int right = to_pos(coords->first + 1, coords->second);
    int left = to_pos(coords->first - 1, coords->second);
    int down = to_pos(coords->first, coords->second + 1);
    int up = to_pos(coords->first, coords->second - 1);
    if (!(is_in_bounds(right) && is_in_bounds(left) && is_in_bounds(down) && is_in_bounds(up)))
        return false;
    bool result = contains(paths, right) && contains(paths, left) && !contains(paths, up) && !contains(paths, down);
    result =
            result || !contains(paths, right) && !contains(paths, left) && contains(paths, up) && contains(paths, down);
    return result;
}

