#include <cstdio>
#include <vector>
#include <iostream>
#include "utils/GraphInterface.h"

class GraphDfsHeur : public GraphInterface {
public:

    std::vector<std::vector<char>> maze;

    GraphDfsHeur(int cols, int rows) : GraphInterface(cols, rows) {

    }

    void initMaze();

    std::vector<std::vector<char>> createMaze();

    void print() override;

private:
    std::vector<std::pair<int, int>> getPossibleNextDirections(std::pair<int, int> curr_node);

    bool inScope(std::pair<int, int> curr_node, std::pair<int, int> direction);

    bool nextIsWall(std::pair<int, int> curr_node, std::pair<int, int> direction);

    bool randomJoinPaths(std::pair<int, int> curr_node, std::pair<int, int> direction);

    bool checkNoBlocks(std::pair<int, int> curr_node, std::pair<int, int> direction);

    bool checkTopRightCorner(std::pair<int, int> next_node);

    bool checkTopLeftCorner(std::pair<int, int> next_node);

    bool checkDownRightCorner(std::pair<int, int> next_node);

    bool checkDownLeftCorner(std::pair<int, int> next_node);

    std::pair<int, int> getDirection(std::pair<int, int> curr_direction, std::vector<std::pair<int, int>> possible_directions);

    std::vector<std::pair<int, int>> all_directions();

    int getCols() override {
        return cols;
    }

    int getRows() override {
        return rows;
    }

    void start() override {
        srand(time(nullptr));
        initMaze();
        createMaze();
    }

    int getNumTiles() override {
        return this->getRows() * this->getCols();
    }

    bool isWall(int i) override {
        std::pair<int, int> *coords = toCoordinates(i);
        return maze[coords->second][coords->first] == '#';
    }

};

void GraphDfsHeur::initMaze() {
    for (int i = 0; i < this->rows; i++) {
        std::vector<char> row = {};
        for (int j = 0; j < this->cols; j++) {
            row.push_back('#');
        }
        this->maze.push_back(row);
    }
}

void GraphDfsHeur::print() {
    for (std::vector<char> row: this->maze) {
        for (char cell: row) {
            printf("%c", cell);
        }
        printf("\n");
    }
}

std::vector<std::vector<char>> GraphDfsHeur::createMaze() {
    std::vector<std::pair<int, int>> visited;
    std::pair<int, int> next_node;
    std::pair<int, int> curr_node = {1, 1};
    std::pair<int, int> curr_direction = {-1, 0};
    std::vector<std::pair<int, int>> possibleDirections;
    this->maze[curr_node.second][curr_node.first] = ' ';
    visited.push_back(curr_node);
    while (visited.size() != 0) {
        curr_node = visited[visited.size() - 1];
        visited.pop_back();
        possibleDirections = getPossibleNextDirections(curr_node);
        if (possibleDirections.size() != 0) {
            curr_direction = getDirection(curr_direction, possibleDirections);
            next_node = {curr_node.first + curr_direction.first, curr_node.second + curr_direction.second};
            this->maze[next_node.second][next_node.first] = ' ';
            visited.push_back(curr_node);
            visited.push_back(next_node);
        }
    }

    return this->maze;
}

std::vector<std::pair<int, int>> GraphDfsHeur::getPossibleNextDirections(std::pair<int, int> curr_node) {
    std::vector<std::pair<int, int>> possible_directions;
    for (std::pair<int, int> direction: all_directions()) {
        if (inScope(curr_node, direction) && nextIsWall(curr_node, direction) && checkNoBlocks(curr_node, direction) &&
            randomJoinPaths(curr_node, direction)) {
            possible_directions.push_back(direction);
        }
    }
    return possible_directions;
}

std::vector<std::pair<int, int>> GraphDfsHeur::all_directions(){
    return {
            std::pair<int, int>{1, 0},
            std::pair<int, int>{-1, 0},
            std::pair<int, int>{0, 1},
            std::pair<int, int>{0, -1}
    };
}

bool GraphDfsHeur::inScope(std::pair<int, int> curr_node, std::pair<int, int> direction) {
    return (curr_node.second + direction.second * 2 >= 0) && (curr_node.second + direction.second * 2 < this->rows) &&
           (curr_node.first + direction.first * 2 >= 0) && (curr_node.first + direction.first * 2 < this->cols);
}

bool GraphDfsHeur::randomJoinPaths(std::pair<int, int> curr_node, std::pair<int, int> direction) {
    if (this->maze[curr_node.second + direction.second * 2][curr_node.first + direction.first * 2] == ' ') {
        int res = rand() % 10;
        if (res < 9) {
            return false;
        }
    }
    return true;
}

bool GraphDfsHeur::nextIsWall(std::pair<int, int> curr_node, std::pair<int, int> direction) {
    return this->maze[curr_node.second + direction.second][curr_node.first + direction.first] == '#';
}

bool GraphDfsHeur::checkNoBlocks(std::pair<int, int> curr_node, std::pair<int, int> direction) {
    std::pair<int, int> next_node = {curr_node.first + direction.first, curr_node.second + direction.second};
    return !checkTopLeftCorner(next_node) && !checkDownLeftCorner(next_node) && !checkTopRightCorner(next_node) &&
           !checkDownRightCorner(next_node);
}

bool GraphDfsHeur::checkTopLeftCorner(std::pair<int, int> next_node) {
    return this->maze[next_node.second][next_node.first - 1] == ' ' &&
           this->maze[next_node.second - 1][next_node.first - 1] == ' ' &&
           this->maze[next_node.second - 1][next_node.first] == ' ';
}

bool GraphDfsHeur::checkTopRightCorner(std::pair<int, int> next_node) {
    return this->maze[next_node.second][next_node.first+1] == ' ' && this->maze[next_node.second-1][next_node.first+1] == ' ' and this->maze[next_node.second-1][next_node.first] == ' ';
}

bool GraphDfsHeur::checkDownLeftCorner(std::pair<int, int> next_node) {
    return this->maze[next_node.second][next_node.first-1] == ' ' && this->maze[next_node.second+1][next_node.first-1] == ' ' and this->maze[next_node.second+1][next_node.first] == ' ';
}

bool GraphDfsHeur::checkDownRightCorner(std::pair<int, int> next_node) {
    return this->maze[next_node.second][next_node.first+1] == ' ' && this->maze[next_node.second+1][next_node.first+1] == ' ' and this->maze[next_node.second+1][next_node.first] == ' ';
}

std::pair<int, int>
GraphDfsHeur::getDirection(std::pair<int, int> curr_direction, std::vector<std::pair<int, int>> possible_directions) {
    std::vector<std::pair<int, int>> list_directions;
    for (std::pair<int, int> direction: possible_directions) {
        if (direction.first == curr_direction.first && direction.second == curr_direction.second) {
            list_directions.push_back(direction);
            list_directions.push_back(direction);
            list_directions.push_back(direction);
            list_directions.push_back(direction);
        } else {
            list_directions.push_back(direction);
        }
    }
    int res = rand() % list_directions.size();
    return list_directions[res];
}
