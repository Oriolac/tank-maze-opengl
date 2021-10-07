//
// Created by oriol on 10/4/21.
//

#ifndef TANK_MAZE_GRAPHINTERFACE_H
#define TANK_MAZE_GRAPHINTERFACE_H


class GraphInterface {

public:
    GraphInterface(int cols, int rows) {
        this->cols = cols % 2 == 1 ? cols : cols + 1;
        this->rows = rows % 2 == 1 ? rows : rows + 1;
    }

    [[nodiscard]] std::pair<int, int> get_main_coords() const {
        return {1, rows-2};
    }
    [[nodiscard]] std::pair<int, int> get_enemy_coords() const {
        return {cols-2, 1};
    }

    virtual void start() = 0;

    virtual int getCols() = 0;

    virtual int getRows() = 0;

    virtual int getNumTiles() = 0;

    virtual bool is_wall(int i) = 0;

    std::pair<int, int> *toCoordinates(int i) {
        return new std::pair<int, int>(i % this->getCols(), i / this->getCols());
    }
    virtual void print() = 0;

    int cols;
    int rows;
};


#endif //TANK_MAZE_GRAPHINTERFACE_H
