//
// Created by oriol on 10/6/21.
//
#include <GL/glut.h>
#include "Character.h"
#include "utils/graphics.h"

MainCharacter::MainCharacter(std::pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    glBegin(GL_TRIANGLES);
    glColor3f(COLORTUP_MAIN_FACE_VERTEX);
    glVertex2i(x_middle, y_start);
    glColor3f(COLORTUP_MAIN_BACK_VERTEX);
    glVertex2i(x_finish, y_finish);
    glColor3f(COLORTUP_MAIN_BACK_VERTEX);
    glVertex2i(x_start, y_finish);
    glEnd();
}

EnemyCharacter::EnemyCharacter(pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    glBegin(GL_TRIANGLES);
    glColor3f(COLORTUP_ENEMY_FACE_VERTEX);
    glVertex2i(x_middle, y_finish);
    glColor3f(COLORTUP_ENEMY_BACK_VERTEX);
    glVertex2i(x_finish, y_start);
    glColor3f(COLORTUP_ENEMY_BACK_VERTEX);
    glVertex2i(x_start, y_start);
    glEnd();
}
