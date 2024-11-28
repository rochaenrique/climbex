#include "Log.h"
#include <iostream>

cbx::Log* cbx::Log::logger = nullptr;

cbx::Log::Log(const std::string& file) 
{
};

cbx::Log::~Log() 
{
    if (logger)
        delete logger;
};

void cbx::Log::Send(const std::string& msg) 
{
    std::cout << msg << std::endl; 
};
