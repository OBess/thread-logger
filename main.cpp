// C++
#include <iostream>
#include <memory>

// Custom
#include "include/factory/console_creator.hpp"
#include "include/factory/file_creator.hpp"

int main()
{
   
   // Test 1 - console logger
   auto console_cr = std::make_unique<console_creator<console_logger>>();
   auto console = console_cr->getLogger();
   console->Log("Start work");
   console->Log("Did something");
   console->Log("End work");
   console->Log("Message ", "with ", "variability size of", "values", " and ", 'i', 'n', " this ", "text are ", 10, " values.");
   console->Log(12, ' ', 3.5);

   // Test 2 - file logger
   auto file_cr = std::make_unique<file_creator<file_logger>>("log.txt");
   auto file = file_cr->getLogger();
   file->Log("Start work");
   file->Log("Did something");
   file->Log("End work");
   file->Log("Message ", "with ", "variability size of", "values", " and ", 'i', 'n', " this ", "text are ", 10, " values.");
   file->Log(12, ' ', 3.5);

   // Clear data
   delete console;
   delete file;

   return EXIT_SUCCESS;
}