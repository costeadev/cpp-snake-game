//
// Created by alber on 4/30/26.
//


#include "snake.h"

Vec2 direction_to_delta(const Direction dir) {
    switch (dir) {
        case Direction::Up:    return {  0,-1};
        case Direction::Down:  return {  0, 1};
        case Direction::Left:  return { -2, 0};
        case Direction::Right: return {  2, 0};
        default:               return {  0, 0};
    }
}

Direction direction_from_key(const char key) {
    switch (key) {
        case 'w': return Direction::Up;
        case 's': return Direction::Down;
        case 'a': return Direction::Left;
        case 'd': return Direction::Right;
        default:  return Direction::None;
    }
}

void Snake::turn(const Direction new_dir) {
    if (!is_reversal(new_dir))
        direction = new_dir;
}

void Snake::step() {
    for (size_t i = segments.size() - 1; i > 0; i--)
        segments[i] = segments[i - 1];
    segments[0] = segments[0] + direction_to_delta(direction);
}

bool Snake::contains(const size_t row, const size_t col) const {
    for (const auto &seg : segments)
        if (seg.y == row && seg.x == col) return true;
    return false;
}

bool Snake::body_collision() const {
    auto head = segments[0];
    for (size_t i = 1; i < segments.size(); i++) {
        if (segments[i].x == head.x && segments[i].y == head.y) return true;
    }
    return false;
}

bool Snake::is_reversal(const Direction new_dir) const {
    return (direction == Direction::Up    && new_dir == Direction::Down)  ||
           (direction == Direction::Down  && new_dir == Direction::Up)    ||
           (direction == Direction::Left  && new_dir == Direction::Right) ||
           (direction == Direction::Right && new_dir == Direction::Left);
}

bool in_bounds(const Vec2 &pos, const size_t rows, const size_t cols) {
    return pos.x > 0 && pos.x < static_cast<int>(cols) - 1 &&
           pos.y > 0 && pos.y < static_cast<int>(rows) - 1;
}
