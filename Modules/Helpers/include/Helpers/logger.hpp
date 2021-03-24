#pragma once

#include <memory>
#include <typeinfo>
namespace Helpers
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
        enum LogType
        {
            ERROR,
            WARN,
            INFO
        };
        /**
         * @brief Get logger with provided name and if it doesn't exist create one.
         * 
         * @param t_name name of the logger (as rvalue).
         * @param t_type type of lod from enum LogType.
         * @param t_msg message to log.
         * @param t_msgArgs arguments for the message string.
         * 
         */
        template<typename FormatString, typename... Args>
        static void log(std::string&& t_name, LogType t_type, FormatString && t_msg, Args&&...t_msgArgs);

        /**
         * @brief Get logger with name of provided type.
         * 
         * @param t_type type of lod from enum LogType.
         * @param t_msg message to log.
         * @param t_msgArgs arguments for the message string.
         * 
         */
        template<typename T, typename FormatString, typename... Args>
        static void log(LogType t_type, FormatString && t_msg, Args&&...t_msgArgs);

        /**
         * @brief Get logger with provided name and if it doesn't exist create one.
         * 
         * @param t_name name of the logger (as lvalue).
         * @param t_type type of lod from enum LogType.
         * @param t_msg message to log.
         * @param t_msgArgs arguments for the message string.
         * 
         */
        template<typename FormatString, typename... Args>
        static void log(std::string const& t_name, LogType t_type, FormatString && t_msg, Args&&...t_msgArgs);
    };
}