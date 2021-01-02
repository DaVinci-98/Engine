#pragma once

#include <exception>
#include <string>
#include <vector>

#define GL_CALL(x) \
    MyEngine::OpenGL::GlException::glClearError();\
    x;\
    MyEngine::OpenGL::GlException::glLogErrors(#x, __FILE__, __LINE__);


namespace MyEngine::OpenGL
{
    /**
     * @brief Holds error informations for GlException
     * 
     */
    struct ErrorMessage
    {
        unsigned int code;
        int line;
        std::string function;
        std::string file;
    };

    /**
     * @brief Exception in OpenGL abstractions.
     * 
     */
    class GlException : std::exception
    {
    public:
        GlException() { }
        ~GlException() { }

        /**
         * @brief Print all stored errors.
         * 
         */
        void printErrors() const;
        /**
         * @brief Add an ErrorMessage to this exception.
         * 
         */
        void push(ErrorMessage& t_error); 

        /**
         * @brief Clear all error messages from openGL.
         * 
         */
        static void glClearError();
        /**
         * @brief Used to gather currently present error messages from openGL.
         * 
         * @throws GlException if any were present.
         * 
         * @param t_function function in which glLogErrors() was called
         * @param t_file file from which glLogErrors() was called
         * @param t_line line from which glLogErrors() was called
         */
        static void glLogErrors(const char* t_function, const char * t_file, int t_line);
        /**
         * @brief Turn openGL error code into string message.
         * 
         * @param t_code openGL error code
         */
        static std::string codeToString(unsigned int t_code);
    private:
        /**
         * @brief Print singular error using spdlog.
         * 
         */
        void printError(ErrorMessage const& t_error) const;
        std::vector<ErrorMessage> m_errors;
    };

}
