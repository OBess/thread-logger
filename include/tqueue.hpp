#pragma once

// C++
#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>

namespace custom
{
    namespace
    {
        std::mutex q_operations_mutex;
        std::condition_variable cv;
    }

    template <typename T>
    class tqueue
    {
    public:
        tqueue(size_t maxSize = 5)
            : m_maxSize(maxSize)
        {
        }

        ~tqueue()
        {
            cv.notify_all();
        }

        // Main operations
        void push(const T &msg) noexcept
        {
            std::unique_lock lk(q_operations_mutex);

            cv.wait(lk, [this]
                    { return m_storage.size() < m_maxSize; });

            m_storage.push(msg);
        }

        T pop() noexcept
        {
            if (empty())
                return T{};

            q_operations_mutex.lock();

            auto copy = m_storage.front();
            m_storage.pop();

            q_operations_mutex.unlock();
            cv.notify_one();

            return copy;
        }

        // Getters & Setters
        size_t getMaxSize() const noexcept
        {
            return m_maxSize;
        }

        void setMaxSize(size_t size) noexcept
        {
            m_maxSize = size;
        }

        bool empty() const noexcept
        {
            return m_storage.empty();
        }

    private:
        std::queue<T> m_storage;
        size_t m_maxSize;
    };
}