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

    [[nodiscard]] std::pair<int, int> get_initial_pos() const {
        return {1, rows-2};
    }
    [[nodiscard]] std::pair<int, int> get_last_pos() const {
        return {cols-2, 1};
    }

    virtual void start() = 0;

    virtual int getCols() = 0;

    virtual int getRows() = 0;

    virtual int getNumTiles() = 0;

    virtual bool isWall(int i) = 0;

    virtual std::pair<int, int> *toCoordinates(int i) = 0;

    virtual void print() = 0;

    int cols;
    int rows;
};


#endif //TANK_MAZE_GRAPHINTERFACE_H
