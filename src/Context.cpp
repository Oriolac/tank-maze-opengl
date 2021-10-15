//
// Created by oriol on 10/6/21.
//
#include <concepts>
#include <memory>

#include "Context.h"
#include "Character.h"

void Context::move_main(Direction direction) {
    if (direction == Direction::FORWARD && main_character->getDirection() == Direction::STOPPED)
        return;
    if (direction != Direction::FORWARD || check_can_go_forward(getMainCharacter()))
        main_character->move(direction);
}

void Context::move_enemy(Direction direction) {
    if (direction == Direction::FORWARD && enemy_character->getDirection() == Direction::STOPPED)
        return;
    if (direction != Direction::FORWARD || check_can_go_forward(getEnemyCharacter()))
        enemy_character->move(direction);
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
    can_move = can_move && !(x == other_coords.first && y == other_coords.second);
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

