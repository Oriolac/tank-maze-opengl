//
// Created by quimpm on 17/10/21.
//

#ifndef TANK_MAZE_OPENGL_TANK_H
#define TANK_MAZE_OPENGL_TANK_H


class Tank{
    public:
        static void drawTank(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos, float current_degree);
    private:
        static void drawWheels(int size_x, int size_y, int size_z);
        static void drawBase(int size_x, int size_y, int size_z, float color[3]);
        static void drawCavin(int size_x, int size_y, int size_z, float color[3]);
        static void drawCannon(int size_x, int size_y, int size_z);
};


#endif //TANK_MAZE_OPENGL_TANK_H
