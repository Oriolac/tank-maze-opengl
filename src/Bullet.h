//
// Created by oriol on 30/11/21.
//

#ifndef TANK_MAZE_OPENGL_BULLET_H
#define TANK_MAZE_OPENGL_BULLET_H


#include "Character.h"

class Bullet {
protected:
    double x;
    double y;
    Orientation orientation;
    int xTile, yTile;
    double vX, vY;
    int time_remaining;
    int vertical;
    int horizontal;
public:
    Bullet(int x, int y, int tile_side_length, Orientation orientation);
    static int time_remain();

    bool integrate(int t);

    void draw();

    int tile_side_length;

    pair<int, int> getCoords();

    void go_on();
};


#endif //TANK_MAZE_OPENGL_BULLET_H
