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
    draw(COLORTUP_MAIN_FACE_VERTEX, COLORTUP_MAIN_BACK_VERTEX);
}

EnemyCharacter::EnemyCharacter(pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    draw(COLORTUP_ENEMY_FACE_VERTEX, COLORTUP_MAIN_BACK_VERTEX);
}
