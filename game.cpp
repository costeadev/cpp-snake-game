//
// Created by alber on 4/29/26.
//

#include "game.h"
#include "terminal.h"
#include "render.h"
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <iostream>
#include <cstdlib>

Game::Game(size_t rows, size_t cols) : rows(rows), cols(cols) {
    snake.segments = {{1, 3}, {1, 2}, {1, 1}};
    snake.direction = Direction::Down;
    food = spawn_food();
}

void Game::eat() {
    score++;
    snake.segments.push_back(snake.segments.back());
    food = spawn_food();
}

Vec2 Game::spawn_food() const {
    Vec2 f;
    do {
        f.x = (rand() % static_cast<int>(cols - 2) + 1);
        f.y = (rand() % static_cast<int>(rows - 2) + 1);
        if (f.x % 2 == 0) f.x++; // align food horizontally with head
    } while (snake.contains(f.y, f.x));
    return f;
}

bool Game::step() {
    Vec2 next = snake.head() + direction_to_delta(snake.direction);
    if (!in_bounds(next, rows, cols)) return false;

    snake.step();

    if (snake.body_collision()) return false;

    if (snake.head().x == food.x && snake.head().y == food.y)
        eat();

    return true;
}

void run_game(size_t rows, size_t cols, size_t tick_ms) {
    Game game(rows, cols);

    std::atomic<Direction> next_dir = Direction::None;
    std::atomic<bool> quit = false;
    std::mutex mtx;
    std::condition_variable cv;

    std::thread input_thread = start_input_thread(next_dir, quit, cv);

    for (size_t i = 0; i < rows + 1; i++) std::cout << '\n';

    while (!quit) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait_for(lock, std::chrono::milliseconds(tick_ms));
        }

        Direction d = next_dir.exchange(Direction::None);
        if (d != Direction::None) game.snake.turn(d);

        if (!game.step()) quit = true;

        std::cout << "\033[" << rows << "A\r" << std::flush;
        std::cout << "\033[?25l";
        render_frame(game.snake, game.food, rows, cols);
        std::cout << "Score: " << game.score << " " << std::flush;
        // std::cout << "\033[?25h";
    }

    input_thread.join();
}

