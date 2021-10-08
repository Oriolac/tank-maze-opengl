//
// Created by oriol on 10/6/21.
//
#include <GL/glut.h>
#include "Character.h"
#include "utils/graphics.h"


std::pair<int, int> Character:: getCoords() {
    return {this->xTile, this->yTile};
}

MainCharacter::MainCharacter(std::pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    draw();
}

void MainCharacter::draw() {
    update_state();
    glBegin(GL_TRIANGLES);
    glColor3f(COLORTUP_MAIN_FACE_VERTEX);
    glVertex3i(x_middle, y_start, 0);
    glColor3f(COLORTUP_MAIN_BACK_VERTEX);
    glVertex3i(x_finish, y_finish, 0);
    glColor3f(COLORTUP_MAIN_BACK_VERTEX);
    glVertex3i(x_start, y_finish, 0);
    glEnd();
}

EnemyCharacter::EnemyCharacter(pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    draw();
}

void EnemyCharacter::draw() {
    update_state();
    glMatrixMode(GL_MODELVIEW);
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    glColor3f(COLORTUP_ENEMY_FACE_VERTEX);
    glVertex3i(x_middle, y_finish, 0);
    glColor3f(COLORTUP_ENEMY_BACK_VERTEX);
    glVertex3i(x_start, y_start, 0);
    glColor3f(COLORTUP_ENEMY_BACK_VERTEX);
    glVertex3i(x_finish, y_start, 0);
    glEnd();
}
