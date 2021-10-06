//
// Created by oriol on 10/6/21.
//

#ifndef TANK_MAZE_CHARACTER_H
#define TANK_MAZE_CHARACTER_H

class Character {
protected:
    int variance;
    int x;
    int y;
    int y_start;
    int y_finish;
    int x_start;
    int x_finish;
    int x_middle;
public:
    Character(pair<int, int> coords, int tile_side_length) {
        x = coords.first;
        y = coords.second;
        variance = tile_side_length / 5;
        y_start = tile_side_length * y + variance;
        y_finish = tile_side_length * (y + 1) - variance;
        x_start = tile_side_length * x + variance;
        x_finish = tile_side_length * (x + 1) - variance;
        x_middle = (x_start + x_finish) / 2;
    };
};

class MainCharacter : public Character {
public:
    MainCharacter(pair<int, int> coords, int tile_side_length);
};

class EnemyCharacter : public Character {
public:
    EnemyCharacter(pair<int, int> coords, int tile_side_length);
};


#endif //TANK_MAZE_CHARACTER_H
