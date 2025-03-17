//
// Created by symnxie on 2025/3/16.
//
#pragma once

#include <cstdint>
#include <sys/time.h>

uint64_t NowMicros() {
    static constexpr uint64_t kUsecondsPerSecond = 1000 * 1000;
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * kUsecondsPerSecond + tv.tv_usec;
}

