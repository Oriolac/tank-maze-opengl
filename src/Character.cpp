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
            return {0, 1, 0};
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
    isDead = false;
    time_death_remain = TIME_REMAINING_DEATH;
}

bool EnemyCharacter::isMainCharacter() {
    return false;
}

void EnemyCharacter::die_and_go_home() {
    time_death_remain = TIME_REMAINING_DEATH;
    isDead = true;
    glDisable(this->light);
}


void Character::drawLight() {
    if (isDead)
        return;
    std::vector<GLfloat> orientation = this->getLightDirection();
    GLfloat lightOrientation[] = {orientation[0], orientation[1], orientation[2]};
    glLightfv(this->light, GL_SPOT_DIRECTION, lightOrientation); // direction

    glLightf(light, GL_SPOT_CUTOFF, 50); // degrees
    glLightf(light, GL_SPOT_EXPONENT, 20);
    glLightf(light, GL_CONSTANT_ATTENUATION, 0.3);

    float position[4];
    position[0] = x + 20;
    position[1] = y + 20;
    position[2] = 1;
    position[3] = 1;
    glLightfv(light, GL_POSITION, position);
    GLfloat color[] = {1,1,1,1};
    glLightfv(light, GL_DIFFUSE, color);

    glEnable(light);
}