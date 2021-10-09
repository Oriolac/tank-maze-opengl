//
// Created by oriol on 10/4/21.
//

#ifndef TANK_MAZE_GRAPHINTERFACE_H
#define TANK_MAZE_GRAPHINTERFACE_H


class GraphInterface {

public:
    GraphInterface(int cols, int rows) {
        this->cols = cols;
        this->rows = rows;
    }

    virtual void start() = 0;

    virtual int getCols() = 0;


    std::pair<int, int> get_main_coords() {
        return {1, 1};
    }
    [[nodiscard]] std::pair<int, int> get_enemy_coords() {
        return {getCols()-2, getRows()-2};
    }

    virtual int getRows() = 0;

    virtual int getNumTiles() = 0;

    virtual bool is_wall(int i) = 0;

    std::pair<int, int> *toCoordinates(int i) {
        return new std::pair<int, int>(i % this->getCols(), i / this->getCols());
    }

    virtual void print() = 0;

    int to_pos(int x, int y) {
        return y * getCols() + x;
    }

    int cols;
    int rows;
};


#endif //TANK_MAZE_GRAPHINTERFACE_H
