//
// Created by oriol on 30/11/21.
//

#include "Bullet.h"

Bullet::Bullet(int x, int y, int tile_side_length, Orientation orientation) {
    this->xTile = x;
    this->yTile = y;
    this->x = (float) (xTile * tile_side_length);
    this->y = (float) (yTile * tile_side_length);
    this->tile_side_length = tile_side_length;
    this->orientation = orientation;
    this->time_remaining = time_remain();
    this->vertical = 0;
    this->horizontal = 0;
    switch (orientation) {
        case Orientation::UP:
            this->vertical = 1;
            break;
        case Orientation::DOWN:
            this->vertical = -1;
            break;
        case Orientation::LEFT:
            this->horizontal = -1;
            break;
        case Orientation::RIGHT:
            this->horizontal = 1;
            break;
    }
    this->vX = ((float) tile_side_length) / ((float) time_remaining) * (double )horizontal;
    this->vY = ((float) tile_side_length) / ((float) time_remaining) * (double) vertical;
}

int Bullet::time_remain() {
    return 50;
}

bool Bullet::integrate(int t) {
    if (t < this->time_remaining) {
        this->x = x + vX * t;
        this->y = y + vY * t;
        this->time_remaining -= t;
    } else if (t >= this->time_remaining) {
        this->x = x + vX * this->time_remaining;
        this->y = y + vY * this->time_remaining;
        this->xTile += horizontal;
        this->yTile += vertical;
        return true;
    }
    return false;
}

void Bullet::go_on() {
    this->time_remaining = time_remain();
}

void Bullet::draw() {
    float color[] = {0.2,0.2,1};
    setMaterial(color);
    glPushMatrix();
    GLUquadricObj *quadratic;
    glTranslatef(x, y, 20);
    glPushMatrix();
    glTranslatef(tile_side_length / 2, tile_side_length / 2, 35);
    quadratic = gluNewQuadric();
    gluSphere(quadratic, 5, 32, 32);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

std::pair<int, int> Bullet::getCoords() {
    return {this->xTile, this->yTile};
}