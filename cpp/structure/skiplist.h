//
// Created by symnxie on 2025/3/17.
//

#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <cmath>

#include "util/time.h"
#include "util/random.h"

class SkipList {
public:
    const static int kMaxHeight = 30;  // 最大高度

private:
    struct Node {
        Node(uint64_t key, uint64_t value, int height) : key(key), value(value) {
            next.resize(height, nullptr);
        }
        ~Node() {
            std::vector<Node*> tmp;
            next.swap(tmp);
        }

        const uint64_t key;
        uint64_t value;
        std::vector<Node*> next;
    };

public:
    explicit SkipList(int branching = 4);

    ~SkipList();

    void Put(uint64_t key, uint64_t value);

    uint64_t Get(uint64_t key);

    // TODO: for test
    int TestPutIter() { return test_put_iter_;}
    int TestGetIter() { return test_get_iter_;}
    void TestDump(std::ostream& os);

private:
    int GenarateHeight();

private:
    Node* head_;
    int max_height_;
    XorShift128Plus rng_;
    int branching_;

    // TODO: for test
    int test_get_iter_ = 0;
    int test_put_iter_ = 0;
};