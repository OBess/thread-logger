#pragma once

// C++
#include <thread>
#include <mutex>
#include <cstdio>
#include <ctime>
#include <sstream>
#include <string>

// Custom
#include "tqueue.hpp"

#define Log(param) Logger logger(__FILE__, __FUNCTION__, __LINE__, (param))

class Logger
{
private:
    static inline custom::tqueue<std::string> q;

public:
    template <typename T>
    Logger(const char *file, const char *function, int line, const T &param)
    {
        std::stringstream ss;
        ss << "tid [ " << std::hex << std::this_thread::get_id() << " ] [ " << currentDateTime() << "|" << file << '|' << function << ':' << std::dec << line << " ] " << param;
        q.push(ss.str());
    }

    static const std::string getMsg() noexcept
    {
        return q.pop();
    }

    static bool queueEmpty() noexcept
    {
        return q.empty();
    }

    static bool queueEmptySleep() noexcept
    {
        while (queueEmpty())
        {
        }

        return q.empty();
    }

    static void setMaxSize(size_t size) noexcept
    {
        q.setMaxSize(size);
    }

    static const std::string currentDateTime() noexcept
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);

        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }
};