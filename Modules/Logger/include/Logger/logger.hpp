#pragma once

#include <memory>
#include <typeinfo>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Logger
{
    /**
     * @brief Sends logs to terminal using spdlog library.
     * 
     * @see https://github.com/gabime/spdlog
     * 
     */
    class Logger
    {
    public:
        /**
         * @brief Get logger with provided name and if it doesn't exist create one.
         * 
         * @param t_name name of the logger (as rvalue).
         * 
         * @return std::shared_ptr to spdlog::logger
         *  
         */
        static std::shared_ptr<spdlog::logger> log(std::string&& t_name)
        {
            auto logger = spdlog::get(t_name);

            if(logger) 
                return logger;
            else 
                return spdlog::stdout_color_mt(t_name);
        }

        /**
         * @brief Get logger with name of provided type.
         * 
         * @tparam T type for the logger
         * 
         * @return std::shared_ptr to spdlog::logger
         * 
         */
        template<typename T>
        static std::shared_ptr<spdlog::logger> log()
        {
            return log(typeid(T).name());
        }


        /**
         * @brief Get logger with provided name and if it doesn't exist create one.
         * 
         * @param t_name name of the logger (as lvalue).
         * 
         * @return std::shared_ptr to spdlog::logger
         *  
         */
        static std::shared_ptr<spdlog::logger> log(std::string const& t_name)
        { 
            return log(std::string(t_name)); 
        }
    };
}