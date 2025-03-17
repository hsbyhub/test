//
// Created by symnxie on 2025/3/16.
//
#pragma once

#include "util/time.h"
#include "util/log.h"

// 测试
#define TEST(case)                                                                              \
    do {                                                                                        \
        auto beg_us = NowMicros();                                                              \
        LOG("CASE [%s] RUNNING...", #case);                                                     \
        char msg[100] = {0};                                                                    \
        if (case(msg)) {                                                                        \
            LOG("CASE [%s] SUCCESS, cost[%lluus]", #case, NowMicros()-beg_us);                  \
        } else {                                                                                \
            LOG("CASE [%s] FAILED, cost[%lluus], msg[%s]", #case, NowMicros()-beg_us, msg);     \
            exit(1);                                                                            \
        }                                                                                       \
    } while(false)

#define TEST_ASSERT(a, b)                                           \
do {                                                                \
    if (a != b) {                                                   \
        snprintf(msg, 100, "%s[%lu] != %s[%lu]", #a, a, #b, b);     \
        return false;                                               \
    }                                                               \
} while(false);
