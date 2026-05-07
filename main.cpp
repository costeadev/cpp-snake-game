
#include "game.h"
#include "terminal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    constexpr size_t cols     = 25;
    constexpr size_t rows     = 18;
    constexpr size_t ticks_ms = 300;

    RawMode raw; // Make terminal raw mode
    srand(time(nullptr));

    run_game(rows, cols, ticks_ms);

    std::cout << "\033[?25h\nGame over!\n";
    return 0;
}
