//
// Created by symnxie on 2025/3/17.
//

#include <random>
#include <vector>
#include <cmath>

#include "skiplist.h"
#include "util/time.h"
#include "util/random.h"
#include "util/test.h"

// 测试可用性
bool test_usable(char* msg) {
    XorShift128Plus rng(NowMicros(), NowMicros());
    SkipList l;
    for (int i = 0; i < 1000; i++) {
        uint64_t key = rng.Next();
        uint64_t value = rng.Next();
        l.Put(key, value);
        uint64_t get_value = l.Get(key);
        TEST_ASSERT(get_value, value);
    }
    return true;
}

// 测试写性能
bool test_put_performance(char* msg) {
    // 生成随机数据
    static XorShift128Plus rng(NowMicros(), NowMicros());
    uint64_t kMaxKeyCountTimes = 7;
    int max_key_count = 1;
    for (int i = 0; i < kMaxKeyCountTimes; i++) {max_key_count *= 10; }
    std::vector<std::pair<uint64_t, uint64_t>> kvs(max_key_count, {0, 0});
    for (std::pair<uint64_t, uint64_t> &kv : kvs) {
        kv = {rng.Next(), rng.Next()};
    }

    // 开始测试写性能
    uint64_t count = 1;
    for (int j = 0; j < kMaxKeyCountTimes; j++) {
        count *= 10;

        for (int branching = 2; branching <= 10; branching++) {
            SkipList sl(branching);
            uint64_t beg_us = NowMicros();
            for (uint64_t i = 0; i < count; i++) {
                sl.Put(kvs[i].first, kvs[i].second);
            }
            LOG("Test PUT performance keys[%d] branching[%d] end, cost[%f], iter[%llu]", count, branching, (NowMicros()-beg_us)/1000000.0, sl.TestPutIter());
        }
        LOG("==========================================================================");
    }

    return true;
}

// 测试写性能
bool test_get_performance(char* msg) {
    // 生成随机数据
    static XorShift128Plus rng(NowMicros(), NowMicros());
    uint64_t kMaxKeyCountTimes = 7;
    int max_key_count = 1;
    for (int i = 0; i < kMaxKeyCountTimes; i++) {max_key_count *= 10; }
    std::vector<std::pair<uint64_t, uint64_t>> kvs(max_key_count, {0, 0});
    for (std::pair<uint64_t, uint64_t> &kv : kvs) {
        kv = {rng.Next(), rng.Next()};
    }

    // 开始测试写性能
    uint64_t count = 1;
    for (int j = 0; j < kMaxKeyCountTimes; j++) {
        count *= 10;

        for (int branching = 2; branching <= 10; branching++) {
            SkipList sl(branching);
            for (uint64_t i = 0; i < count; i++) {
                sl.Put(kvs[i].first, kvs[i].second);
            }

            uint64_t beg_us = NowMicros();
            for (uint64_t i = 0; i < count; i++) {
                uint64_t get_value = sl.Get(kvs[i].first);
                TEST_ASSERT(get_value, kvs[i].second);
            }
            LOG("Test GET performance keys[%d] branching[%d] end, cost[%f], iter[%llu]", count, branching, (NowMicros()-beg_us)/1000000.0, sl.TestGetIter());
        }
        LOG("==========================================================================");
    }

    return true;
}

int main() {
    TEST(test_usable);
    TEST(test_put_performance);
    TEST(test_get_performance);
}
