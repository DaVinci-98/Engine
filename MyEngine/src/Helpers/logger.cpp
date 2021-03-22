#include "Helpers/logger.hpp"

#include "Helpers/type.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Helpers
{
    namespace
    {
        template<typename FormatString, typename... Args>
        void logWithSpdlog(std::shared_ptr<spdlog::logger> t_logger, Logger::LogType t_type, FormatString const& t_msg, Args&&...t_msgArgs)
        {
            switch (t_type)
            {
            case Logger::LogType::ERROR:
                t_logger -> error(t_msg, std::forward<Args>(t_msgArgs)...);
                break;
            case Logger::LogType::INFO:
                t_logger -> info(t_msg, std::forward<Args>(t_msgArgs)...);
                break;
            case Logger::LogType::WARN:
                t_logger -> warn(t_msg, std::forward<Args>(t_msgArgs)...);
                break;
            }
        }

        std::shared_ptr<spdlog::logger> getLogger(std::string const& t_name)
        {
            auto logger = spdlog::get(t_name);
            if(!logger) 
                logger = spdlog::stdout_color_mt(t_name);
            return logger;
        }
    }

    template<typename FormatString, typename... Args>
    void Logger::log(std::string && t_name, LogType t_type, FormatString && t_msg, Args&&...t_msgArgs)
    { 
        auto logger = getLogger(t_name);
        logWithSpdlog(logger, t_type, t_msg, std::forward<Args>(t_msgArgs)...);
    }

    template<typename FormatString, typename... Args>
    void Logger::log(std::string const& t_name, LogType t_type, FormatString && t_msg, Args&&...t_msgArgs)
    { 
        auto logger = getLogger(t_name);
        logWithSpdlog(logger, t_type, t_msg, std::forward<Args>(t_msgArgs)...);
    }

    template<typename T, typename FormatString, typename... Args>
    void Logger::log(LogType t_type, FormatString && t_msg, Args&&...t_msgArgs)
    { 
        log(getTypeName<T>(), t_type, std::move(t_msg), std::forward<Args>(t_msgArgs)...); 
    }
}