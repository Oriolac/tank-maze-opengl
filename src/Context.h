//
// Created by oriol on 10/6/21.
//

#ifndef TANK_MAZE_CONTEXT_H
#define TANK_MAZE_CONTEXT_H


class Context {
private:
    GraphInterface *graph;
    MainCharacter *main_character;
    EnemyCharacter *enemy_character;
    int last_time_t;
public:
    Context(GraphInterface *graphInt, MainCharacter *main_char, EnemyCharacter *enemyCharacter) {
        this->graph = graphInt;
        this->main_character = main_char;
        this->enemy_character = enemyCharacter;
        last_time_t = 0;
    }

    int get_last_time() {
        return last_time_t;
    }

    void set_last_time(int t) {
        this->last_time_t = t;
    }

    MainCharacter *getMainCharacter() const {
        return main_character;
    }

    EnemyCharacter *getEnemyCharacter() const {
        return enemy_character;
    }
};


#endif //TANK_MAZE_CONTEXT_H
