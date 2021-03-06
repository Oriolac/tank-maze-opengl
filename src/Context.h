//
// Created by oriol on 10/6/21.
//

#include <memory>
#include "Bullet.cpp"

#ifndef TANK_MAZE_CONTEXT_H
#define TANK_MAZE_CONTEXT_H


class Context {
private:
    std::shared_ptr<GraphInterface> graph;
    MainCharacter *main_character;
    EnemyCharacter *enemy_character;
    std::shared_ptr<Bullet> bullet;
    int tile_side_length;
public:
    Context(std::shared_ptr<GraphInterface> graphInt, MainCharacter *main_char, EnemyCharacter *enemyCharacter, int side_length) {
        this->graph = graphInt;
        this->main_character = main_char;
        this->enemy_character = enemyCharacter;
        bullet = nullptr;
        this->tile_side_length = side_length;
    }


    MainCharacter *getMainCharacter() const {
        return main_character;
    }

    EnemyCharacter *getEnemyCharacter() const {
        return enemy_character;
    }

    void move_main(Direction direction);

    void move_enemy(Direction direction);

    void integrate(Character *pCharacter, int i);

    bool check_can_move_if_forward(const pair<int, int> &coords, Character *pCharacter, Character *otherCharacter);

    bool check_can_go_forward(Character *pCharacter);

    void shoot();

    void remove_shoot();

    void integrateBullet(int i);

    void drawBullet();

    bool has_shoot_enemy(pair<int, int> tile);

};


#endif //TANK_MAZE_CONTEXT_H
