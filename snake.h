//
// Created by alber on 4/29/26.
//

#pragma once
#include <vector>

enum Direction { Up, Down, Left, Right, None };

struct Vec2 {
    int x;
    int y;
    Vec2 operator+(const Vec2 &d) const {
        return {x + d.x, y + d.y};
    }
};

Vec2 direction_to_delta(Direction dir);
Direction direction_from_key(char key);

struct Snake {
    std::vector<Vec2> segments;
    Direction direction = Direction::Down;

    Vec2 &head() { return segments.front(); }
    const Vec2 &head() const { return segments.front(); }

    void turn(Direction new_dir);
    void step();
    bool contains(size_t row, size_t col) const;
    bool body_collision() const;

private:
    bool is_reversal(Direction new_dir) const;
};

bool in_bounds(const Vec2 &pos, size_t rows, size_t cols);