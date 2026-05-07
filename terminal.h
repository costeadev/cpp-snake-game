//
// Created by alber on 4/29/26.
//

#pragma once
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <atomic>
#include <condition_variable>
#include <thread>
#include "snake.h"

struct RawMode {
    termios saved;
    RawMode();
    ~RawMode();
};

bool input_available(size_t timeout_ms);

std::thread start_input_thread(std::atomic<Direction> &next_dir,
                               std::atomic<bool> &quit,
                               std::condition_variable &cv);