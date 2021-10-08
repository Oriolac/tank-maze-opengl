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

bool Context::check_can_move(const Direction &direction, const pair<int, int> &coords) {
    printf("check can move from(%i,%i)\n", coords.first, coords.second);
    bool can_move;
    switch (direction) {
        case Direction::UP:
            printf("to(%i,%i)\n", coords.first, coords.second+1);
            can_move = !graph->is_wall(coords.first, coords.second + 1);
            break;
        case Direction::DOWN:
            printf("to(%i,%i)\n", coords.first, coords.second-1);
            can_move = !graph->is_wall(coords.first, coords.second - 1);
            break;
        case Direction::LEFT:
            printf("to(%i,%i)\n", coords.first-1, coords.second);
            can_move = !graph->is_wall(coords.first - 1, coords.second);
            break;
        case Direction::RIGHT:
            printf("to(%i,%i)\n", coords.first+1, coords.second);
            can_move = !graph->is_wall(coords.first + 1, coords.second);
            break;
        default:
            can_move = false;
            break;
    }
    return can_move;
}
