#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

// C++
#include <utility>

template <class T>
class logger
{
public:
   virtual ~logger() = default;

   template <typename... Args>
   void Log(Args &&...message)
   {
      static_cast<T *>(this)->open();
      static_cast<T *>(this)->write(std::forward<Args>(message)...);
      static_cast<T *>(this)->close();
   }

protected:
   void open(){};
   template <typename... Args>
   void write(Args &&...message) {};
   void close(){};
};

#endif //LOGGER_HPP