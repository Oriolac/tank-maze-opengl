//
// Created by oriol on 10/6/21.
//

#include "utils/tank.cpp"
#include <GL/glut.h>
#include "Character.h"
#include "utils/graphics.h"

std::vector<GLfloat> Character::getLightDirection() {
    switch (this->orientation) {
        case Orientation::UP:
            return {1, 1, 0};
        case Orientation::DOWN:
            return {0, -1, 0};
        case Orientation::RIGHT:
            return {1, 0, 0};
        case Orientation::LEFT:
            return {-1, 0, 0};
        default:
            return {0, 1, 0};
    }
}

std::pair<int, int> Character::getCoords() {
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
    draw(COLORTUP_MAIN_FACE_VERTEX);
    currentDegree = 270;
    light = GL_LIGHT1;
}

EnemyCharacter::EnemyCharacter(pair<int, int> coords, int tile_side_length) : Character(coords, tile_side_length) {
    draw(COLORTUP_ENEMY_FACE_VERTEX);
    orientation = Orientation::UP;
    currentDegree = 90;
    light = GL_LIGHT2;
}

bool EnemyCharacter::isMainCharacter() {
    return false;
}



void Character::drawLight() {
    std::vector<GLfloat> orientation = this->getLightDirection();
    GLfloat lightOrientation[] = {orientation[0], orientation[1], orientation[2]};
    glLightfv(this->light, GL_SPOT_DIRECTION, lightOrientation); // direction

    glLightf(light, GL_SPOT_CUTOFF, 20); // degrees
    glLightf(light, GL_SPOT_EXPONENT, 10);

    pair<int, int> coords = this->getCoords();
    float position[4];
    float plusY = orientation[1] == 1 ? 45: 0;
    position[0] = x + 40;
    position[1] = y+ 40 + 20;
    position[2] = 0;
    position[3] = 1;
    glLightfv(light, GL_POSITION, position);
    GLfloat color[] = {0.8,0.8,0.8,1};
    glLightfv(light, GL_DIFFUSE, color);

    glEnable(light);
}