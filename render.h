//
// Created by alber on 4/29/26.
//

#pragma once
#include <string>

#include "snake.h"

using Cell = std::string;
using Frame = std::vector<std::vector<Cell>>;

namespace Glyph {
    constexpr auto Empty  = "  ";
    constexpr auto Left_Border = "◼ ";
    constexpr auto Right_Border = " ◼";
    constexpr auto Head   = "😎";
    constexpr auto Body   = "🞿";
    constexpr auto Food   = "🍎";
}

void render_frame(const Snake &snake, Vec2 food, size_t rows, size_t cols);