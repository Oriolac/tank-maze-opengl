//
// Created by quimpm on 17/10/21.
//

#ifndef TANK_MAZE_OPENGL_TANK_H
#define TANK_MAZE_OPENGL_TANK_H


class Tank{
    public:
        static void drawTank(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos);
    private:
        static void drawWheels(int size_x, int size_y, int size_z, float x_pos, float y_pos);
        static void drawBase(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos);
        static void drawCavin(int size_x, int size_y, int size_z, float color[3], float x_pos, float y_pos);
        static void drawCannon(int size_x, int size_y, int size_z, float x_pos, float y_pos);
};


#endif //TANK_MAZE_OPENGL_TANK_H
