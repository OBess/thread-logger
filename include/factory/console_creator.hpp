#pragma once
#ifndef CONSOLE_CREATOR_HPP
#define CONSOLE_CREATOR_HPP

// Custom
#include "creator.hpp"
#include "../loggers/console_logger.hpp"

template <class T>
class console_creator : public creator<T>
{
public:
   logger<T> *getLogger() const override
   {
      return new console_logger();
   }
};

#endif //CONSOLE_CREATOR_HPP