#pragma once
#ifndef CREATOR_HPP
#define CREATOR_HPP

// Custom
#include "../loggers/logger.hpp"

template<class T>
class creator
{
public:
   virtual ~creator() = default;
   virtual logger<T> *getLogger() const = 0;
};

#endif //CREATOR_HPP