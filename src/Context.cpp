//
// Created by oriol on 10/6/21.
//
#include <memory>

#include "Context.h"
#include "Character.h"
#include "Bullet.h"

void Context::move_main(Direction direction) {
    if (direction == Direction::FORWARD && main_character->getDirection() == Direction::STOPPED)
        return;
    if (direction != Direction::FORWARD || check_can_go_forward(getMainCharacter()))
        main_character->move(direction);
}

void Context::move_enemy(Direction direction) {
    if (enemy_character->is_dead())
        return;
    if (direction == Direction::FORWARD && enemy_character->getDirection() == Direction::STOPPED)
        return;
    if (direction != Direction::FORWARD || check_can_go_forward(getEnemyCharacter())) {
        enemy_character->move(direction);
    }
}

bool
Context::check_can_move_if_forward(const pair<int, int> &coords, Character *pCharacter, Character *otherCharacter) {
    int x, y;
    bool can_move = true;
    switch (pCharacter->getOrientation()) {
        case Orientation::DOWN:
            x = coords.first;
            y = coords.second - 1;
            break;
        case Orientation::UP:
            x = coords.first;
            y = coords.second + 1;
            break;
        case Orientation::LEFT:
            x = coords.first - 1;
            y = coords.second;
            break;
        case Orientation::RIGHT:
            x = coords.first + 1;
            y = coords.second;
            break;
        default:
            can_move = false;
            break;
    }
    can_move = can_move && !graph->is_wall(x, y);
    pair<int, int> other_coords = otherCharacter->getCoords();
    can_move = can_move && (otherCharacter->is_dead() || !(x == other_coords.first && y == other_coords.second));
    return can_move;
}

void Context::integrate(Character *pCharacter, int i) {
    if (pCharacter->getDirection() != Direction::STOPPED) {
        bool hasFinished = pCharacter->integrate(i);
        if (hasFinished) {
            if (pCharacter->hasNextDirection() && pCharacter->nextDirection() != Direction::FORWARD) {
                pCharacter->nextMoveNotForward();
            } else if (check_can_go_forward(pCharacter)) {
                pCharacter->move(Direction::FORWARD);
            }
        }
    } else {
        pCharacter->integrate(i);
    }
}

bool Context::check_can_go_forward(Character *pCharacter) {
    bool res = pCharacter->isMainCharacter() &&
               check_can_move_if_forward(pCharacter->getCoords(), getMainCharacter(), getEnemyCharacter());
    res = res || !pCharacter->isMainCharacter() &&
                 check_can_move_if_forward(pCharacter->getCoords(), getEnemyCharacter(), getMainCharacter());
    return res;
}

void Context::shoot() {
    if (bullet != nullptr)
        return;
    Orientation orientation = main_character->getOrientation();
    std::pair<int, int> coord = main_character->getCoords();
    Bullet newBullet = Bullet(coord.first, coord.second, main_character->tile_side_length, orientation);
    bullet = make_shared<Bullet>(newBullet);
    printf("SHOOT\n");
}


bool Context::has_shoot_enemy(pair<int, int> tile) {
    pair<int, int> enemy = enemy_character->getCoords();
    return enemy == tile;
}

void Context::remove_shoot() {
    bullet = nullptr;
}

void Context::integrateBullet(int i) {
    if (bullet == nullptr)
        return;
    bool hasFinished = bullet->integrate(i);
    if (hasFinished) {
        std::pair<int, int> bulletCoords = bullet->getCoords();
        if (graph->is_wall(bulletCoords.first, bulletCoords.second)) {
            remove_shoot();
        } else if (has_shoot_enemy(bulletCoords)) {
            enemy_character->die_and_go_home();
            enemy_character->set_character_fields(graph->get_enemy_coords(), this->tile_side_length);
            remove_shoot();
        } else {
            bullet->go_on();
        }
    }
}


void Context::drawBullet() {
    if (bullet == nullptr)
        return;
    bullet->draw();
}

