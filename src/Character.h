//
// Created by oriol on 10/6/21.
//

#define TIME_REMAINING_MAIN 200
#define TIME_REMAINING_ENEMY 200

#ifndef TANK_MAZE_CHARACTER_H
#define TANK_MAZE_CHARACTER_H


#define COLOR_ARG_FACE float redF, float greenF, float blueF


enum class Direction {
    FORWARD, TURN_LEFT, TURN_RIGHT, TURN_UP, TURN_DOWN, STOPPED
};


inline const char *ToString(Direction v) {
    switch (v) {
        case Direction::FORWARD:
            return "FORWARD\n";
        case Direction::TURN_LEFT:
            return "TURN_LEFT\n";
        case Direction::TURN_RIGHT:
            return "TURN_RIGHT\n";
        case Direction::TURN_UP:
            return "TURN_UP\n";
        case Direction::TURN_DOWN:
            return "TURN_DOWN\n";
        case Direction::STOPPED:
            return "STOPPED\n";
        default:
            return "[Unknown OS_type]\n";
    }
}

enum class Orientation {
    UP, RIGHT, DOWN, LEFT
};


inline const char *ToString(Orientation v) {
    switch (v) {
        case Orientation::UP:
            return "UP\n";
        case Orientation::DOWN:
            return "DOWN\n";
        case Orientation::LEFT:
            return "LEFT\n";
        case Orientation::RIGHT:
            return "RIGHT\n";
        default:
            return "[Unknown OS_type]\n";
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
        if(!is_same_direction(new_direction, orientation) && !is_inverse(new_direction, orientation)){
            next_direction = new_direction;
            if (direction == Direction::STOPPED &&
                (next_direction == Direction::TURN_RIGHT || next_direction == Direction::TURN_LEFT
                 || next_direction == Direction::TURN_UP || next_direction == Direction::TURN_DOWN)) {
                direction = next_direction;
                calculate_velocity_rotation();
                orientation = get_new_orientation(direction, orientation);
                time_remaining_rotation = time_remain();
                next_direction = Direction::STOPPED;
            } else if (next_direction == Direction::FORWARD && direction == Direction::STOPPED) {
                printf("direaction: %s", ToString(next_direction));
                printf("orientation: %s", ToString(orientation));
                calculate_velocity_and_next_tile();
                time_remaining_movement = time_remain();
                direction = new_direction;
            }
        }
    }

    bool is_same_direction(Direction direction, Orientation orientation){
        return (direction == Direction::TURN_UP && orientation == Orientation::UP) || (direction == Direction::TURN_DOWN && orientation == Orientation::DOWN)
        || (direction == Direction::TURN_RIGHT && orientation == Orientation::RIGHT)  || (direction == Direction::TURN_LEFT && orientation == Orientation::LEFT);
    }

    bool is_inverse(Direction direction, Orientation curr_orientation){
        return (curr_orientation == Orientation::UP && direction == Direction::TURN_DOWN)
                || (curr_orientation == Orientation::DOWN && direction == Direction::TURN_UP)
                || (curr_orientation == Orientation::RIGHT && direction == Direction::TURN_LEFT)
                || (curr_orientation == Orientation::LEFT && direction == Direction::TURN_RIGHT);
    }


    Orientation get_new_orientation(Direction direction, Orientation curr_orientation){
        if(!is_inverse(direction, curr_orientation)){
            if (direction == Direction::TURN_RIGHT){
                return Orientation::RIGHT;
            }else if (direction == Direction::TURN_LEFT){
                return Orientation::LEFT;
            }else if (direction == Direction::TURN_UP){
                return Orientation::UP;
            }else{
                return  Orientation::DOWN;
            }
        }else{
            return curr_orientation;
        }
    }

    void calculate_velocity_rotation() {
        if (!is_inverse(direction, orientation)){
            velRotate = (double) (rotation_sign(direction, orientation) * 90) / time_remain();
        }else{
            velRotate = 0;
        }
    }

    int rotation_sign(Direction direction, Orientation curr_orientation){
        if ((curr_orientation == Orientation::UP && direction == Direction::TURN_LEFT)
            || (curr_orientation == Orientation::LEFT && direction == Direction::TURN_DOWN)
            || (curr_orientation == Orientation::DOWN && direction == Direction::TURN_RIGHT)
            || (curr_orientation == Orientation::RIGHT && direction == Direction::TURN_UP)){
            return 1;
        }
        return -1;
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
        } else if ((direction == Direction::TURN_UP || direction == Direction::TURN_DOWN || direction == Direction::TURN_RIGHT || direction == Direction::TURN_LEFT) &&
                   t < this->time_remaining_rotation) {
            currentDegree = currentDegree + velRotate * t;
            this->time_remaining_rotation -= t;
        } else if ((direction == Direction::TURN_UP || direction == Direction::TURN_DOWN || direction == Direction::TURN_RIGHT || direction == Direction::TURN_LEFT) &&
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

    void draw(COLOR_ARG_FACE) {
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
