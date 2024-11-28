#pragma once

#include <string>

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

            static void Send(const std::string& msg);

        private: 
            Log(const std::string& file);

            static Log* logger;
    };
}
