//
// Created by oriol on 10/6/21.
//

#ifndef TANK_MAZE_GRAPHICS_H
#define TANK_MAZE_GRAPHICS_H

#define COLOR_WALL Color(0.55, 0.55, 0.7)
#define COLOR_PATH Color(0.55, 0.9, 0.55)
#define COLORTUP_WALL_SIDE 0.3, 0.2, 0.6
#define COLOR_MAIN_CHARACTER_INITIAL_POS Color(0.2, 0.8, 0.2)
#define COLOR_ENEMY_CHARACTER_LAST_POS Color(0.8, 0.2, 0.2)
#define COLORTUP_MAIN_FACE_VERTEX 0.2, 0.2, 1
#define COLORTUP_MAIN_BACK_VERTEX 0.1, 0.1, 0.4
#define COLORTUP_ENEMY_FACE_VERTEX 1, 0.6, 0.2
#define COLORTUP_ENEMY_BACK_VERTEX 1, 0.8, 0.6


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
