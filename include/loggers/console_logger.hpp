#pragma once
#ifndef CONSOLE_LOGGER_HPP
#define CONSOLE_LOGGER_HPP

// C++
#include <iostream>
#include <chrono>
#include <ctime>

// Custom
#include "logger.hpp"

class console_logger : public logger<console_logger>
{
public:
   ~console_logger() = default;

private:
   void open()
   {
      std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      std::cout << m_level++ << ", " << std::ctime(&time) << '[' << std::endl;
   }

   template <typename... Args>
   void write(Args &&...message)
   {
      (std::cout << '\t' << ... << message) << std::endl;
   }

   void close()
   {
      std::cout << ']' << std::endl;
   }

   friend logger<console_logger>;

   static int m_level;
};

int console_logger::m_level = 1;

#endif //CONSOLE_LOGGER_HPP