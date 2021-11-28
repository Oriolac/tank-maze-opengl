//
// Created by oriol on 10/6/21.
//

#ifndef TANK_MAZE_GRAPHICS_H
#define TANK_MAZE_GRAPHICS_H

#define COLOR_WALL Color(0.55, 0.55, 0.7)
#define COLOR_PATH Color(0.55, 0.9, 0.55)
#define COLORTUP_MAIN_FACE_VERTEX 0.1, 0.2, 0.4
#define COLORTUP_ENEMY_FACE_VERTEX 0.4, 0.2, 0.1


struct Color {
    float red;
    float green;
    float blue;
    Color(float r, float g, float b) {
        red=r;
        green=g;
        blue=b;
    }
};

#endif //TANK_MAZE_GRAPHICS_H
