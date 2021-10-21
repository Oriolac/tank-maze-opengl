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
    FORWARD, TURN_LEFT, TURN_RIGHT, STOPPED
};

inline const char *ToString(Direction v) {
    switch (v) {
        case Direction::FORWARD:
            return "FORWARD";
        case Direction::TURN_LEFT:
            return "TURN_LEFT";
        case Direction::TURN_RIGHT:
            return "TURN_RIGHT";
        case Direction::STOPPED:
            return "STOPPED";
        default:
            return "[Unknown OS_type]";
    }
}

enum class Orientation {
    UP, LEFT, DOWN, RIGHT
};

inline const char *ToString(Orientation v) {
    switch (v) {
        case Orientation::UP:
            return "UP";
        case Orientation::DOWN:
            return "DOWN";
        case Orientation::LEFT:
            return "LEFT";
        case Orientation::RIGHT:
            return "RIGHT";
        default:
            return "[Unknown OS_type]";
    }
}

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
    Orientation orientation;
    int time_remaining_movement;
    Direction next_direction;
public:
    Character(pair<int, int> coords, int tile_side_length) {
        xTile = coords.first;
        yTile = coords.second;
        x = coords.first * tile_side_length;
        y = coords.second * tile_side_length;
        this->tile_side_length = tile_side_length;
        variance = tile_side_length / 5;
        update_state();
        direction = Direction::FORWARD;
        orientation = Orientation::DOWN;
        next_direction = Direction::STOPPED;
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
        next_direction = new_direction;
        if (direction == Direction::STOPPED && (next_direction == Direction::TURN_RIGHT || next_direction == Direction::TURN_LEFT)) {
            direction = next_direction;
            orientation = apply_direction(direction, orientation);
            next_direction = Direction::STOPPED;
        } else if (next_direction == Direction::FORWARD && direction != Direction::FORWARD) {
            calculate_velocity_and_next_tile();
            time_remaining_movement = time_remain();
            direction = new_direction;
        }
    }

    Orientation apply_direction(Direction direction, Orientation curr_orientation) {
        if (direction == Direction::TURN_RIGHT) {
            return static_cast<Orientation>((static_cast<int>(curr_orientation) + 3) % 4);
        } else {
            return static_cast<Orientation>((static_cast<int>(curr_orientation) + 1) % 4);
        }
    }

    void calculate_velocity_and_next_tile() {
        switch (orientation) {
            case Orientation::UP:
                vX = 0;
                vY = (double) tile_side_length / time_remain();
                yTile = yTile + 1;
                break;
            case Orientation::DOWN:
                vX = 0;
                vY = -(double) tile_side_length / time_remain();
                yTile = yTile - 1;
                break;
            case Orientation::LEFT:
                vX = -(double) tile_side_length / time_remain();
                vY = 0;
                xTile = xTile - 1;
                break;
            case Orientation::RIGHT:
                vX = (double) tile_side_length / time_remain();
                vY = 0;
                xTile = xTile + 1;
                break;
            default:
                break;
        }
    };

    bool integrate(int t) {
        if (direction == Direction::FORWARD && t < this->time_remaining_movement) {
            this->x = x + vX * t;
            this->y = y + vY * t;
            this->time_remaining_movement -= t;
        } else if (direction == Direction::FORWARD && t >= this->time_remaining_movement) {
            this->x = x + vX * this->time_remaining_movement;
            this->y = y + vY * this->time_remaining_movement;
            direction = Direction::STOPPED;
            return true;
        } else if (direction == Direction::TURN_RIGHT) {
            direction = Direction::STOPPED;
            return true;
        } else if (direction == Direction::TURN_LEFT) {
            direction = Direction::STOPPED;
            return true;
        }
        return false;
    }

    pair<int, int> getCoords();

    [[nodiscard]] virtual int time_remain() const = 0;

    void draw(COLOR_ARG_FACE, COLOR_ARG_BACK) {
        update_state();
        float colors[3] = {redF, greenF, blueF};
        Tank::drawTank(tile_side_length, tile_side_length, tile_side_length, colors, x, y);
    }

    Orientation getOrientation();

    Direction getDirection();

    void nextMoveNotForward();

    virtual bool isMainCharacter() = 0;

    bool hasNextDirection() {
        return this->next_direction != Direction::STOPPED;
    }

    Direction nextDirection();
};

class MainCharacter : public Character {
public:
    MainCharacter(pair<int, int> coords, int tile_side_length);

    [[nodiscard]] int time_remain() const override {
        return TIME_REMAINING_MAIN;
    }

    bool isMainCharacter() override;
};

class EnemyCharacter : public Character {
public:
    EnemyCharacter(pair<int, int> coords, int tile_side_length);

    [[nodiscard]] int time_remain() const override {
        return TIME_REMAINING_ENEMY;
    }

    bool isMainCharacter() override;
};

#endif //TANK_MAZE_CHARACTER_H
