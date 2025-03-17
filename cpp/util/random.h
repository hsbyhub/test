//
// Created by symnxie on 2025/3/16.
//
#pragma once

#include <chrono>

class XorShift128Plus {
public:
    // 初始化种子，建议使用高精度时间戳作为种子
    XorShift128Plus(uint64_t seed1 = 0, uint64_t seed2 = 0) {
        if (seed1 == 0 && seed2 == 0) {
            // 使用当前时间作为种子
            uint64_t now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            // 拆分为两个不同的种子
            state_[0] = now;
            state_[1] = now ^ 0x5DEECE66DULL;
        } else {
            state_[0] = seed1;
            state_[1] = seed2;
        }
    }
    // 生成下一个 64 位随机数
    uint64_t Next() {
        uint64_t s1 = state_[0];
        const uint64_t s0 = state_[1];
        state_[0] = s0;
        s1 ^= s1 << 23;  // a
        state_[1] = s1 ^ s0 ^ (s1 >> 17) ^ (s0 >> 26);  // b, c
        return state_[1] + s0;
    }
private:
    uint64_t state_[2];
};

