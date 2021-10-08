//
// Created by oriol on 10/6/21.
//

#include "Context.h"

void Context::move(Direction direction) {
    std::pair<int, int> coords = main_character->getCoords();
    if (check_can_move(direction, coords)){
        main_character->move(direction);
    }
}

void Context::move_enemy(Direction direction) {
    std::pair<int, int> coords = enemy_character->getCoords();
    printf("enemy from (%i, %i)\n", coords.first, coords.second);
    if (check_can_move(direction, coords)){
        enemy_character->move(direction);
    }
    std::pair<int, int> coordsTo = enemy_character->getCoords();
    printf("enemy to (%i, %i)\n", coordsTo.first, coordsTo.second);

}

bool Context::check_can_move(const Direction &direction, const pair<int, int> &coords) {
    bool can_move;
    switch (direction) {
        case Direction::UP:
            can_move = !graph->is_wall(coords.first, coords.second + 1);
            break;
        case Direction::DOWN:
            can_move = !graph->is_wall(coords.first, coords.second - 1);
            break;
        case Direction::LEFT:
            can_move = !graph->is_wall(coords.first - 1, coords.second);
            break;
        case Direction::RIGHT:
            can_move = !graph->is_wall(coords.first + 1, coords.second);
            break;
        default:
            can_move = false;
            break;
    }
    return can_move;
}
