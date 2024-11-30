#pragma once

#include <string>
#include <iostream>

namespace cbx { 
    class Log
    {
        public: 
            Log()                       = delete;
            Log(const Log&)             = delete;
            Log(Log&&)                  = delete;
            Log operator=(const Log&)   = delete;

            ~Log(); 

            static void Init(const std::string& file) { logger = new Log(file); };
            static Log* Get() { return logger; };

            template <typename T>
            static inline void Send(T&& msg) { std::cout << msg << std::endl; };

            template<typename... T>
            static void Send(std::format_string<T...> fmt, T&&... args)
            {
                std::cout << std::format(fmt, std::forward<T>(args)...) << std::endl;
            };

        private: 
            Log(const std::string& file);

            static Log* logger;
    };
}

#ifdef CBX_DEBUG
#define CBX_LOG(...) cbx::Log::Send(__VA_ARGS__)
#else
#define CBX_LOG(...) 
#endif
