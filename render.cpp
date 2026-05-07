//
// Created by alber on 4/29/26.
//

#include "render.h"
#include <iostream>

void render_frame(const Snake &snake, const Vec2 food, const size_t rows, const size_t cols) {
    // Build the grid/frame
    Frame frame(rows, std::vector<Cell>(cols, Glyph::Empty));

    // Draw vertical borders
    for (size_t i = 0; i < rows; i++) {
        frame[i][0]        = Glyph::Left_Border;
        frame[i][cols - 1] = Glyph::Right_Border;
    }

    // Draw horizontal
    for (size_t j = 1; j < cols; j++) {
        frame[0][j] = frame[rows - 1][j] = Glyph::Left_Border;
    }

    // Make border cut
    frame[0][0] = frame[rows - 1][0] = Glyph::Empty;

    // Draw food
    frame[food.y][food.x] = Glyph::Food;

    // Stamp snake segments - head gets a different glyph
    for (size_t i = 0; i < snake.segments.size(); i++) {
        const auto &seg = snake.segments[i];
        frame[seg.y][seg.x] = (i == 0) ? Glyph::Head : Glyph::Body;
    }

    // Print in one pass
    for (const auto &row :  frame) {
        for (const auto &cell : row)
            std::cout << cell;
        std::cout << '\n';
    }
}
