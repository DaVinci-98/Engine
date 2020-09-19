#pragma once

#include <exception>
#include <string>
#include <vector>

#define GL_CALL(x) \
    MyEngine::GlException::glClearError();\
    x;\
    MyEngine::GlException::glLogErrors(#x, __FILE__, __LINE__);


namespace MyEngine
{
    struct ErrorMessage
    {
        unsigned int code;
        int line;
        std::string function;
        std::string file;
    };

    class GlException : std::exception
    {
    public:
        GlException() { }
        ~GlException() { }

        void printErrors() const;
        void push(ErrorMessage& t_error); 

        static void glClearError();
        static void glLogErrors(const char* t_function, const char * t_file, int t_line);
        static std::string codeToString(unsigned int t_code);
    private:
        void printError(ErrorMessage const& t_error) const;
        std::vector<ErrorMessage> m_errors;
    };

}
