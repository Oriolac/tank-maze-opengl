//
// Created by oriol on 10/6/21.
//

#define TIME_REMAINING 1000

#ifndef TANK_MAZE_CHARACTER_H
#define TANK_MAZE_CHARACTER_H
enum class Direction {
    UP, DOWN, LEFT, RIGHT, QUIET
};

class Character {
protected:
    int variance;
    int x, y;
    int vX, vY;
    int tile_side_length;
    int y_start;
    int y_finish;
    int x_start;
    int x_finish;
    int x_middle;
    Direction direction;
    int time_remaining_movement;
public:
    Character(pair<int, int> coords, int tile_side_length) {
        x = coords.first;
        y = coords.second;
        this->tile_side_length = tile_side_length;
        variance = tile_side_length / 5;
        y_start = tile_side_length * y + variance;
        y_finish = tile_side_length * (y + 1) - variance;
        x_start = tile_side_length * x + variance;
        x_finish = tile_side_length * (x + 1) - variance;
        x_middle = (x_start + x_finish) / 2;
        direction = Direction::QUIET;
        time_remaining_movement = 0;
        vX = 0;
        vY = 0;
    };

    void move(Direction new_direction) {
        if (direction == Direction::QUIET) {
            direction = new_direction;
            switch (direction) {
                case Direction::UP:
                    vX = 0;
                    vY = tile_side_length / TIME_REMAINING;
                    break;
                case Direction::DOWN:
                    vX = 0;
                    vY = -tile_side_length / TIME_REMAINING;
                    break;
                case Direction::LEFT:
                    vX = -tile_side_length / TIME_REMAINING;
                    vY = 0;
                    break;
                case Direction::RIGHT:
                    vX = tile_side_length / TIME_REMAINING;
                    vY = 0;
                    break;
                default:
                    break;
            }
            time_remaining_movement = TIME_REMAINING;
        }
    };

    void integrate(int t) {
        if (direction != Direction::QUIET && t < time_remaining_movement) {
            x = x + vX * t;
            y = y + vY * t;
            time_remaining_movement -= t;
        } else if (direction != Direction::QUIET) {
            x = x + vX * time_remaining_movement;
            y = y + vY * time_remaining_movement;
            direction = Direction::QUIET;
        }
    }

};

class MainCharacter : public Character {
public:
    MainCharacter(pair<int, int> coords, int tile_side_length);

    void draw();
};

class EnemyCharacter : public Character {
public:
    EnemyCharacter(pair<int, int> coords, int tile_side_length);

    void draw();

};


#endif //TANK_MAZE_CHARACTER_H
