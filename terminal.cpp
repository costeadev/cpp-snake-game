//
// Created by alber on 4/30/26.
//

#include "terminal.h"

RawMode::RawMode() {
    tcgetattr(STDIN_FILENO, &saved);
    termios t = saved;
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

RawMode::~RawMode() { tcsetattr(STDIN_FILENO, TCSANOW, &saved); }

bool input_available(size_t timeout_ms) {
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    return select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv) > 0;
}

std::thread start_input_thread(std::atomic<Direction> &next_dir,
                               std::atomic<bool> &quit,
                               std::condition_variable &cv) {
    return std::thread([&]() {
        while (!quit) {
            if (input_available(100)) {
                Direction last = Direction::None;
                bool should_quit = false;
                while (input_available(0)) {
                    char key = getchar();
                    if (key == 'p') { should_quit = true; break; }
                    Direction d = direction_from_key(key);
                    if (d != Direction::None) last = d;
                }
                if (should_quit) { quit = true; cv.notify_one(); return; }
                if (last != Direction::None) next_dir = last;
            }
        }
    });
}
