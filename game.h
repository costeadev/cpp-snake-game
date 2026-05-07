//
// Created by alber on 4/29/26.
//

#pragma once
#include "snake.h"

struct Game {
    Snake snake;
    Vec2 food{};
    size_t rows, cols;
    int score = 0;

    Game(size_t rows, size_t cols);
    bool step();

private:
    void eat();
    Vec2 spawn_food() const;
};

void run_game(size_t rows, size_t cols, size_t tick_ms);