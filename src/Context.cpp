//
// Created by oriol on 10/6/21.
//

#include "Context.h"

void Context::move(Direction direction) {
    std::pair<int, int> coords = main_character->getCoords();
    if (check_can_move(direction, coords, getEnemyCharacter())) {
        main_character->move(direction);
    }
}

void Context::move_enemy(Direction direction) {
    std::pair<int, int> coords = enemy_character->getCoords();
    if (check_can_move(direction, coords, getMainCharacter())) {
        enemy_character->move(direction);
    }
    std::pair<int, int> coordsTo = enemy_character->getCoords();

}

bool Context::check_can_move(const Direction &direction, const pair<int, int> &coords, Character* pCharacter) {
    int x;
    int y;
    bool can_move = true;
    switch (direction) {
        case Direction::UP:
            x = coords.first;
            y = coords.second + 1;
            break;
        case Direction::DOWN:
            x = coords.first;
            y = coords.second - 1;
            break;
        case Direction::LEFT:
            x = coords.first - 1;
            y = coords.second;
            break;
        case Direction::RIGHT:
            x = coords.first + 1;
            y = coords.second;
            break;
        default:
            can_move = false;
            break;
    }
    can_move = can_move && !graph->is_wall(x, y);
    pair<int, int> other_coords = pCharacter->getCoords();
    can_move = can_move && !(x == other_coords.first && y == other_coords.second);
    return can_move;
}
