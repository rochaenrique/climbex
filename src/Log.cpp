#include "Log.h"

cbx::Log* cbx::Log::logger = nullptr;

cbx::Log::Log(const std::string& file) 
{
};

cbx::Log::~Log() 
{
    if (logger)
        delete logger;
};
