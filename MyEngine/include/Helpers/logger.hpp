#pragma once

#include <memory>
#include <typeinfo>

#include "Helpers/type.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Helpers
{
    class Logger
    {
    public:
        static std::shared_ptr<spdlog::logger> log(std::string&& t_name)
        {
            auto logger = spdlog::get(t_name);

            if(logger) 
                return logger;
            else 
                return spdlog::stdout_color_mt(t_name);
        }

        template<typename T>
        static std::shared_ptr<spdlog::logger> log()
        {
            return log(getTypeName<T>());
        }


        static std::shared_ptr<spdlog::logger> log(std::string const& t_name)
        { 
            return log(std::string(t_name)); 
        }
    };
}