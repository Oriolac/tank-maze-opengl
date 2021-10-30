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
    double velRotate;
    double currentDegree;
    int tile_side_length;
    double x_start;
    double x_finish;
    Direction direction;
    Orientation orientation;
    int time_remaining_movement;
    int time_remaining_rotation;
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
        time_remaining_rotation = 0;
        vX = 0;
        vY = 0;
        velRotate = 0;
    }

    void update_state() {
        x_start = x + variance;
        x_finish = x + tile_side_length - variance;
    };

    void move(Direction new_direction) {
        next_direction = new_direction;
        if (direction == Direction::STOPPED &&
            (next_direction == Direction::TURN_RIGHT || next_direction == Direction::TURN_LEFT)) {
            direction = next_direction;
            orientation = apply_direction(direction, orientation);
            calculate_velocity_rotation();
            time_remaining_rotation = time_remain();
            next_direction = Direction::STOPPED;
        } else if (next_direction == Direction::FORWARD && direction == Direction::STOPPED) {
            calculate_velocity_and_next_tile();
            time_remaining_movement = time_remain();
            direction = new_direction;
        }
    }

    Orientation apply_direction(Direction direction, Orientation curr_orientation) {
        if (direction == Direction::TURN_RIGHT) {
            return apply_direction_on_orientation(curr_orientation, 1, 3);
        } else {
            return apply_direction_on_orientation(curr_orientation, 3, 1);
        }
    }

    Orientation apply_direction_on_orientation(const Orientation &curr_orientation, int a, int b) const {
        switch (orientation){
            case Orientation::DOWN:
            case Orientation::RIGHT:
                return static_cast<Orientation>((static_cast<int>(curr_orientation) + a) % 4);
            default:
                return static_cast<Orientation>((static_cast<int>(curr_orientation) + b) % 4);
        }
    }

    void calculate_velocity_rotation() {
        switch (direction) {
            case Direction::TURN_RIGHT:
                velRotate = (double) 90 / time_remain();
                break;
            case Direction::TURN_LEFT:
                velRotate = (double) (-90) / time_remain();
                break;
            default:
                velRotate = 0;
                break;
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
        } else if ((direction == Direction::TURN_RIGHT || direction == Direction::TURN_LEFT) &&
                   t < this->time_remaining_rotation) {
            currentDegree = currentDegree + velRotate * t;
            this->time_remaining_rotation -= t;
        } else if ((direction == Direction::TURN_RIGHT || direction == Direction::TURN_LEFT) &&
                   t >= this->time_remaining_rotation) {
            currentDegree = currentDegree + time_remaining_rotation * velRotate;
            int noise = (int) abs(currentDegree) % 90;
            if (noise > 45) {
                currentDegree = (int) ((currentDegree + 45) / 90) * 90;
            } else if (noise != 0 && noise <= 45) {
                currentDegree = (int) ((currentDegree - 45) / 90) * 90;
            }
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
        Tank::drawTank(tile_side_length, tile_side_length, tile_side_length, colors, x, y, currentDegree);
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
