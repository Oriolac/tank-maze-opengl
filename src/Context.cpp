//
// Created by oriol on 10/6/21.
//
#include <concepts>
#include <memory>

#include "Context.h"
#include "Character.h"

void Context::move_main(Direction direction) {
    main_character->move(direction);
}

void Context::move_enemy(Direction direction) {
    enemy_character->move(direction);
}

bool Context::check_can_move_if_forward(const pair<int, int> &coords, Character *pCharacter) {
    int x, y;
    bool can_move = true;
    switch (pCharacter->getOrientation()) {
        case Orientation::DOWN:
            x = coords.first;
            y = coords.second + 1;
            break;
        case Orientation::UP:
            x = coords.first;
            y = coords.second - 1;
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
    printf("%i %i to %i %i ISWALL??%i\n", coords.first, coords.second, x, y, graph->is_wall(x, y));
    pair<int, int> other_coords = pCharacter->getCoords();
    can_move = can_move && !(x == other_coords.first && y == other_coords.second);
    return can_move;
}

void Context::integrate(Character *pCharacter, int i) {
    if (pCharacter->getDirection() == Direction::FORWARD) {
        bool hasFinished = pCharacter->integrate(i);
        if (hasFinished) {
            bool is_instance = dynamic_cast<MainCharacter*>(pCharacter) != nullptr;
            is_instance = is_instance && check_can_move_if_forward(pCharacter->getCoords(), getEnemyCharacter());
            is_instance = is_instance || dynamic_cast<EnemyCharacter*>(pCharacter) != nullptr &&
                                         check_can_move_if_forward(pCharacter->getCoords(), getMainCharacter());
            printf("%i HAS FINISHED: %i\n", dynamic_cast<MainCharacter*>(pCharacter) != nullptr, is_instance);
            if (is_instance) {
                printf("CAN MOVE FORWARD\n");
                pCharacter->move(Direction::FORWARD);
            } else {
                printf("CANNOT MOVE FORWARD %i\n", dynamic_cast<MainCharacter*>(pCharacter) != nullptr);
            }
        }
    } else {
        bool hasFinished = pCharacter->integrate(i);
    }


}

