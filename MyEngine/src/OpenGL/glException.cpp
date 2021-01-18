#include "OpenGL/glException.hpp"
#include "glad/glad.h"
#include "Helpers/logger.hpp"

#include <algorithm>
#include <vector>

namespace MyEngine::OpenGL
{
    void GlException::printErrors() const
    {
        for(auto const& error : m_errors) printError(error);
    }

    void GlException::printError(ErrorMessage const& t_error) const
    {
        Helpers::Logger::log<GlException>() -> error(
        "[ERROR (" + std::to_string(t_error.code) + ")]\n"
        "\t- message  : " + codeToString(t_error.code) + "\n"
        "\t- function : " + t_error.function + "\n"
        "\t- location : " + t_error.file + " => " + std::to_string(t_error.line) + "\n");
    }

    void GlException::push(ErrorMessage& t_error)
    {
        m_errors.push_back(t_error);
    }        

    void GlException::glClearError()
    {
        while (glGetError() != GL_NO_ERROR);        
    }

    std::string GlException::codeToString(unsigned int t_code)
    {
        switch (t_code)
        {
        case  GL_INVALID_ENUM:
            return "An unacceptable value is specified for an enumerated argument.";
            break;
        case   GL_INVALID_VALUE:
            return "A numeric argument is out of range.";
            break;
        case   GL_INVALID_OPERATION:
            return "The specified operation is not allowed in the current state.";
            break;
        case   GL_INVALID_FRAMEBUFFER_OPERATION:
            return "The framebuffer object is not complete.";
            break;
        case   GL_OUT_OF_MEMORY:
            return "There is not enough memory left to execute the command.";
            break;
        case   GL_STACK_UNDERFLOW:
            return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
            break;
        case   GL_STACK_OVERFLOW:
            return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
            break;
        default:
            return "Unknown error occurred.";
            break;
        }
    }

    void GlException::glLogErrors(const char* t_function, const char * t_file, int t_line)
    {
        bool isError = false;
        GlException except;

        while(GLenum error = glGetError())
        {
            ErrorMessage err;

            err.code = error;
            err.file = t_file;
            err.function = t_function;
            err.line = t_line;

            except.push(err);

            if(!isError) isError = true;
        }

        if(isError) throw GlException(except);
    }
}