//
// Created by symnxie on 2025/3/17.
//

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cstdarg>
#include <cstring>

// 宏简化日志调用
#define LOG(format, ...) Log(__FILE__, __LINE__, format, ##__VA_ARGS__)

// 日志方法
void Log(const char* file, int line, const char* format, ...) {
    // 获取当前时间
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_tm = *std::localtime(&now_time_t);

    // 获取毫秒部分
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

    // 格式化时间
    char time_str[20];
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &now_tm);

    // 提取文件名（去掉路径）
    const char* filename = std::strrchr(file, '/');
    if (!filename) {
        filename = std::strrchr(file, '\\');
    }
    filename = filename ? filename + 1 : file;

    // 格式化日志前缀（时间、文件名、行号）
    std::ostringstream prefix_stream;
    prefix_stream << "[" << time_str << "." << std::setfill('0') << std::setw(3) << milliseconds.count() << "] "
                  << "[" << filename << ":" << line << "] ";

    // 处理可变参数
    va_list args;
    va_start(args, format);

    // 计算格式化后的字符串长度
    va_list args_copy;
    va_copy(args_copy, args);
    int length = std::vsnprintf(nullptr, 0, format, args_copy);
    va_end(args_copy);

    // 分配缓冲区并格式化字符串
    std::string message(length + 1, '\0');
    std::vsnprintf(&message[0], length + 1, format, args);
    va_end(args);

    // 输出日志
    std::cout << prefix_stream.str() << message << std::endl << std::flush;
}