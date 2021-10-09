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
        this->cols = cols;
        this->rows = rows;
    }

    void reset_grid();

    int is_in_bounds(int x, int y);

    void dfs(int x, int y);

    void print() override;

    void start() override {
        srand(time(nullptr));
        reset_grid();
        this->dfs(1, 1);
        this->add_extra_paths();
        if (this->getCols() % 2 == 0) {
            int lastCol = getCols() - 2;
            add_union_path_to_enemy_point(lastCol, getRows() - 3);
            for (int j = 1; j < getRows() - 3; j++) {
                int pos = to_pos(lastCol, j);
                int posup = to_pos(lastCol, j - 1);
                int posdown = to_pos(lastCol, j + 1);
                int posleft = to_pos(lastCol - 1, j);
                bool all_walls = is_wall(posup) && is_wall(posdown) && !is_wall(posleft);
                bool no_center_wall = is_wall(posleft) && !is_wall(posup);
                if ((all_walls && rand() % 3 != 0) || (no_center_wall)) {
                    grid[pos] = ' ';
                    paths.insert(pos);
                }
            }
        }
        if (this->getRows() % 2 == 0) {
            int lastRow = getRows() - 2;
            for (int i = 1; i < getCols() - 3; i++) {
                int pos = to_pos(i, lastRow);
                int posleft = to_pos(i - 1, lastRow);
                int posright = to_pos(i + 1, lastRow);
                int posup = to_pos(i, lastRow - 1);
                if (is_wall(posleft) && is_wall(posright) && !is_wall(posup) && rand() % 2 == 0) {
                    grid[pos] = ' ';
                    paths.insert(pos);
                }
            }
        }
    }

    void add_union_path_to_enemy_point(int union_x, int union_y) {
        int pos = to_pos(getCols() - 2, getRows() - 2);
        grid[pos] = ' ';
        paths.insert(pos);
        int posfinal_left = to_pos(getCols() - 3, getRows() - 2);
        if (is_wall(posfinal_left)) {
            pos = to_pos(union_x, union_y);
            grid[pos] = ' ';
            paths.insert(pos);
        }
    }

    int getNumTiles() override {
        return getCols() * getRows();
    }

    bool is_wall(int i) override {
        return !contains(paths, i);
    }

    bool contains(set<int> set1, int el);

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

    bool are_coords_on_frame_walls(const pair<int, int> *coords);

    bool check_can_be_path_near_xframe_walls(int tile);
};

void GraphDFS::reset_grid() {
    for (int i = 0; i < getCols() * getRows(); ++i) {
        grid[i] = '#';
    }
    if (getRows() % 2 == 0) {
        int pos = to_pos(getCols() - 2, getRows() - 2);
        grid[pos] = ' ';
        paths.insert(pos);
    }
}


int GraphDFS::is_in_bounds(int x, int y) {
    // Returns "true" if x and y are both in-bounds.
    if (x < 0 || x + 1 >= getCols()) return false;
    if (y < 0 || y + 1 >= getRows()) return false;
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
    for (int y = getRows() - 1; y >= 0; y--) {
        for (int x = 0; x < getCols(); ++x) {
            cout << grid[to_pos(x, y)];
        }
        cout << endl;
    }
    cout << "\n";
}


bool GraphDFS::contains(std::set<int> set1, int el) {
    return set1.find(el) != set1.end();
}


void GraphDFS::add_extra_paths() {
    int sqrt_tiles = (int) sqrt(getNumTiles());
    int limit = 0;
    if (sqrt_tiles < 7) {
        limit = 0;
    } else {
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
    if (are_coords_on_frame_walls(coords))
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

bool GraphDFS::are_coords_on_frame_walls(const pair<int, int> *coords) {
    bool on_frame_x = coords->first == 0 || coords->first == getCols() - 1;
    bool on_frame_y = coords->second == 0 || coords->second == this->getRows() - 1;
    return on_frame_x || on_frame_y;
}

bool GraphDFS::check_can_be_path_near_xframe_walls(int tile) {
    pair<int, int> *coords = toCoordinates(tile);
    if (are_coords_on_frame_walls(coords))
        return false;
    int right = to_pos(coords->first + 1, coords->second);
    int left = to_pos(coords->first - 1, coords->second);
    int down = to_pos(coords->first, coords->second + 1);
    int up = to_pos(coords->first, coords->second - 1);
    bool result = (contains(paths, right) || contains(paths, left)) && !contains(paths, up) && !contains(paths, down);
    return result;
}

