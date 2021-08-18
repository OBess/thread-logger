// C++
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

// Custom
#include "include/logger.hpp"

using namespace std::chrono_literals;

// Def
void writeToTxt(const std::string &path);
void addMsgs(const size_t &amount);

int main()
{
   // Init
   Logger::setMaxSize(6);

   // Update
   std::thread sender(addMsgs, 25);
   std::thread sender2(addMsgs, 20);
   std::thread sender3(addMsgs, 44);
   std::thread writer(writeToTxt, "text.txt");

   // Joins
   sender.join();
   sender2.join();
   sender3.join();
   writer.join();

   return EXIT_SUCCESS;
}

// Impl
void writeToTxt(const std::string &path)
{
   std::ofstream file(path);

   while (!Logger::queueEmptySleep())
   {
      auto tmp = Logger::getMsg();
      file << tmp << '\n';
      // std::cout << tmp << std::endl;
      std::this_thread::sleep_for(50ms);
   }
}

void addMsgs(const size_t &amount)
{
   for (size_t i = 0; i < amount; ++i)
   {
      Log("Sender " + std::to_string(i));
      std::this_thread::sleep_for(25ms);
   }
}