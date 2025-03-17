#include <cstdio>
#include <iostream>
#include <random>

template<typename T>
inline void EncodeVarint(std::string &buf, T value) {
    T B = (1 << 7) - 1; 
    while(value) {
        char c = value & B;
        if (value > B) {
            c |= (1 << 7);
        }
        value >>= 7;
        buf += c;
    };
}

template<class T>
T DecodeVarint(const std::string &buf) {
    T B = (1 << 7) - 1; 
    T value = 0;
    for (int i = 0; i < buf.size(); i++) {
        char c = buf[i];
        value |= (c & B) << (i * 7);
        if (!(c & (1 << 7))) {
            break;
        }
    }
    return value;
}

// 生成64位随机值的方法
uint64_t rand_uint64() {
    // 使用随机设备作为种子
    std::random_device rd;
    // 使用Mersenne Twister算法作为随机数生成器
    std::mt19937_64 gen(rd());
    // 定义一个64位无符号整数的分布
    std::uniform_int_distribution<uint64_t> dis;
    // 生成并返回一个64位随机值
    return dis(gen);
}


// 测试
#define TEST(case)                                                                          \
    do {                                                                                    \
        char msg[MSG_MAX_SIZE] = {0};                                                       \
        if (case(msg)) {                                                                    \
            std::cout << "Run " << #case << " success" << std::endl;                        \
        } else {                                                                            \
            std::cout << "RUN " << #case << " failed" << ", message: " << msg << std::endl; \
        }                                                                                   \
    } while(false)

const static int MSG_MAX_SIZE = 1000;

bool test1(char* msg) {
    uint64_t origin = rand_uint64();

    std::string buf;
    EncodeVarint(buf, origin);
    uint64_t decode = DecodeVarint<uint64_t>(buf);
    if (decode != origin) {
        snprintf(msg, MSG_MAX_SIZE, "decode[%lu] != origin[%lu]", decode, origin);
        return false;
    }
    return true;
}

bool test2(char* msg) {
    for (int i = 0; i < 1000 * 1000; i++) {
        if (!test1(msg)) {
            return false;
        }
    }
    return true;
}

bool test3(char* msg) {
    for (int i = 0; i < 10 * 1000 * 1000; i++) {
        if (!test1(msg)) {
            return false;
        }
    }
    return true;
}

int main() {
    TEST(test1);
    TEST(test2);
    TEST(test3);
}
