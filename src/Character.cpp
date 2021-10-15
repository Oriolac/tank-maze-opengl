//
// Created by oriol on 10/6/21.
//
#include <GL/glut.h>
#include "Character.h"
#include "utils/graphics.h"


std::pair<int, int> Character:: getCoords() {
    return {this->xTile, this->yTile};
}

Orientation Character::getOrientation() {
    return this->orientation;
}

Direction Character::getDirection() {
    return this->direction;
}

bool MainCharacter::isMainCharacter() {
    return true;
}

void Character::nextMoveNotForward() {
    Direction new_direction = next_direction == Direction::FORWARD ? Direction::STOPPED : next_direction;
    this->next_direction = Direction::STOPPED;
    move(new_direction);
}

Direction Character::nextDirection() {
    return this->next_direction;
}

MainCharacter::MainCharacter(std::pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    draw(COLORTUP_MAIN_FACE_VERTEX, COLORTUP_MAIN_BACK_VERTEX);
}

EnemyCharacter::EnemyCharacter(pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    draw(COLORTUP_ENEMY_FACE_VERTEX, COLORTUP_MAIN_BACK_VERTEX);
    orientation = Orientation::UP;
}

bool EnemyCharacter::isMainCharacter() {
    return false;
}
