//
// Created by oriol on 10/6/21.
//

#include <memory>

#ifndef TANK_MAZE_CONTEXT_H
#define TANK_MAZE_CONTEXT_H


class Context {
private:
    std::shared_ptr<GraphInterface> graph;
    MainCharacter *main_character;
    EnemyCharacter *enemy_character;
public:
    Context(std::shared_ptr<GraphInterface> graphInt, MainCharacter *main_char, EnemyCharacter *enemyCharacter) {
        this->graph = graphInt;
        this->main_character = main_char;
        this->enemy_character = enemyCharacter;
    }


    MainCharacter *getMainCharacter() const {
        return main_character;
    }

    EnemyCharacter *getEnemyCharacter() const {
        return enemy_character;
    }

    void move(Direction direction);

    bool check_can_move(const Direction &direction, const pair<int, int> &coords);
};


#endif //TANK_MAZE_CONTEXT_H
