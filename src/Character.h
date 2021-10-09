//
// Created by oriol on 10/6/21.
//

#define TIME_REMAINING_MAIN 200
#define TIME_REMAINING_ENEMY 200

#ifndef TANK_MAZE_CHARACTER_H
#define TANK_MAZE_CHARACTER_H


#define COLOR_ARG_FACE float redF, float greenF, float blueF
#define COLOR_ARG_BACK float redB, float greenB, float blueB
#define COLOR_PARAM_FACE redF, greenF, blueF
#define COLOR_PARAM_BACK redB, greenB, blueB
#define HEIGHT_TANK 10.0


enum class Direction {
    UP, DOWN, LEFT, RIGHT, QUIET
};

class Character {
protected:
    int variance;
    int xTile, yTile;
    double x, y;
    double vX, vY;
    int tile_side_length;
    double y_start;
    double y_finish;
    double x_start;
    double x_finish;
    double x_middle;
    Direction direction;
    int time_remaining_movement;
public:
    Character(pair<int, int> coords, int tile_side_length) {
        xTile = coords.first;
        yTile = coords.second;
        x = coords.first * tile_side_length;
        y = coords.second * tile_side_length;
        this->tile_side_length = tile_side_length;
        variance = tile_side_length / 5;
        update_state();
        direction = Direction::QUIET;
        time_remaining_movement = 0;
        vX = 0;
        vY = 0;
    }

    void update_state() {
        y_start = y + variance;
        y_finish = y + tile_side_length - variance;
        x_start = x + variance;
        x_finish = x + tile_side_length - variance;
        x_middle = (x_start + x_finish) / 2;
    };

    void move(Direction new_direction) {
        if (direction == Direction::QUIET) {
            direction = new_direction;
            switch (new_direction) {
                case Direction::UP:
                    this->vX = 0;
                    this->vY = (double) tile_side_length / time_remain();
                    this->yTile = yTile + 1;
                    break;
                case Direction::DOWN:
                    this->vX = 0;
                    this->vY = - (double) tile_side_length / time_remain();
                    this->yTile = yTile - 1;
                    break;
                case Direction::LEFT:
                    this->vX = - (double)tile_side_length / time_remain();
                    this->vY = 0;
                    this->xTile = xTile - 1;
                    break;
                case Direction::RIGHT:
                    this->vX = (double) tile_side_length / time_remain();
                    this->vY = 0;
                    this->xTile = xTile + 1;
                    break;
                default:
                    break;
            }
            time_remaining_movement = time_remain();
        }
    };

    void integrate(int t) {
        if (direction != Direction::QUIET && t < this->time_remaining_movement) {
            this->x = x + vX * t;
            this->y = y + vY * t;
            this->time_remaining_movement -= t;
        } else if (direction != Direction::QUIET && t >= this->time_remaining_movement) {
            this->x = x + vX * this->time_remaining_movement;
            this->y = y + vY * this->time_remaining_movement;
            this->direction = Direction::QUIET;
        }
    }

    pair<int, int> getCoords();

    [[nodiscard]] virtual int time_remain() const = 0;

    void draw(COLOR_ARG_FACE, COLOR_ARG_BACK) {
        update_state();
        glBegin(GL_TRIANGLES);
        glColor3f(COLOR_PARAM_FACE);
        glVertex3i(x_middle, y_start, HEIGHT_TANK);
        glColor3f(COLOR_PARAM_BACK);
        glVertex3i(x_finish, y_finish, HEIGHT_TANK);
        glVertex3i(x_start, y_finish, HEIGHT_TANK);
        glEnd();

        glBegin(GL_QUADS);
        glVertex3i(x_middle, y_start, HEIGHT_TANK);
        glVertex3i(x_middle, y_start, 0);
        glVertex3i(x_finish, y_finish, 0);
        glVertex3i(x_finish, y_finish, HEIGHT_TANK);
        glEnd();

        glBegin(GL_QUADS);
        glVertex3i(x_middle, y_start, 0);
        glVertex3i(x_middle, y_start, HEIGHT_TANK);
        glVertex3i(x_start, y_finish, HEIGHT_TANK);
        glVertex3i(x_start, y_finish, 0);
        glEnd();

        glBegin(GL_QUADS);
        glVertex3i(x_start, y_finish, 0);
        glVertex3i(x_start, y_finish, HEIGHT_TANK);
        glVertex3i(x_finish, y_finish, HEIGHT_TANK);
        glVertex3i(x_finish, y_finish, 0);
        glEnd();
    }

};

class MainCharacter : public Character {
public:
    MainCharacter(pair<int, int> coords, int tile_side_length);

    [[nodiscard]] int time_remain() const override {
        return TIME_REMAINING_MAIN;
    }
};

class EnemyCharacter : public Character {
public:
    EnemyCharacter(pair<int, int> coords, int tile_side_length);

    [[nodiscard]] int time_remain() const override {
        return TIME_REMAINING_ENEMY;
    }

};


#endif //TANK_MAZE_CHARACTER_H
