#include "glad/gl.h"

#include "OpenGL/shader.hpp"
#include "OpenGL/glException.hpp"
#include "Logger/logger.hpp"

#include <exception>
#include <algorithm>
#include <array>

namespace MyEngine::OpenGL
{
    Shader::Shader(std::vector<Shader::ShaderFile> const& t_files)
    {
        std::vector<unsigned int> idList;
        GL_CALL(m_rendererId = glCreateProgram());

        for(auto const& file : t_files) 
        {
            ShaderText shader { readFile(file.m_filepath), file.m_type };
            idList.push_back(attachShader(shader)); 
            Logger::Logger::log<Shader>() -> info(
                "[Load] [" + file.m_filepath + "]: Done");
        }

        GL_CALL(glLinkProgram(m_rendererId));
        GL_CALL(glValidateProgram(m_rendererId));

        for(auto const& id : idList) 
            detachShader(id);

        Logger::Logger::log<Shader>() -> info(
            "[Load] [" + std::to_string(m_rendererId)  + "]: Done");
    }

    Shader::Shader(std::vector<Shader::ShaderText> const& t_shaders)
    {
        std::vector<unsigned int> idList;
        GL_CALL(m_rendererId = glCreateProgram());

        for(auto const& shader : t_shaders) 
            idList.push_back(attachShader(shader)); 


        GL_CALL(glLinkProgram(m_rendererId));
        GL_CALL(glValidateProgram(m_rendererId));

        for(auto const& id : idList) 
            detachShader(id);

        Logger::Logger::log<Shader>() -> info(
            "[Load] [" + std::to_string(m_rendererId)  + "]: Done");
    }

    Shader::~Shader()
    {
        try
        {
            Logger::Logger::log<Shader>() -> info(
                "[Destroy] [" + std::to_string(m_rendererId) + "]: Start");
            GL_CALL(glDeleteProgram(m_rendererId));
            Logger::Logger::log<Shader>() -> info(
                "[Destroy] [" + std::to_string(m_rendererId) + "]: Done");
        }
        catch(GlException const& e)
        {
            e.printErrors();
        }      
    }

    unsigned int Shader::attachShader(Shader::ShaderText const& t_shader)
    {
        if(t_shader.m_shaderText == "") throw std::exception();

        unsigned int id = compileShader(t_shader.m_shaderText, t_shader.m_type);
        if(id == 0) throw std::exception();

        GL_CALL(glAttachShader(m_rendererId, id));
        return id;
    }

    void Shader::detachShader(unsigned int t_id)
    {
        GL_CALL(glDetachShader(m_rendererId, t_id));
        GL_CALL(glDeleteShader(t_id));
    }

    std::string Shader::readFile(std::string const& t_path) const
    {
        std::array<char, 512> str;
        std::string out = "";

        FILE* src = fopen(t_path.c_str(), "r");

        if(src == nullptr)
        {
            Logger::Logger::log<Shader>() -> error(
                "[readFile()]: Could not open file.");
            return "";
        } 

        while(fgets(str.data(), str.size(), src))
        {
            out += std::string(str.data());
        }

        fclose(src);
        return out;
    }

    unsigned int Shader::compileShader(std::string const& t_source, GLenum t_type) const
    {
        unsigned int id = glCreateShader(t_type);
        const char* src = t_source.c_str();
        
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if(result == GL_FALSE)
        {
            int len;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

            char message[len];
            glGetShaderInfoLog(id, len, &len, message);

            Logger::Logger::log<Shader>() -> error(
                "[compileShader()]: {0}", std::string(message));

            glDeleteShader(id);

            return 0;
        }

        return id;
    }

    void Shader::bind()
    {
        GL_CALL(glUseProgram(m_rendererId));
    }

    void Shader::unbind()
    {
        GL_CALL(glUseProgram(0));
    }

    int Shader::getUniformLocation(std::string const& t_name)
    {
        if(m_locations.find(t_name) != m_locations.end()) return m_locations[t_name];

        GL_CALL(int location = glGetUniformLocation(m_rendererId, t_name.c_str()));
        if(location < 0)
            Logger::Logger::log<Shader>() -> error(
                "[getUniformLocation()]: Invalid uniform name - {0}", t_name);
        m_locations[t_name] = location;
        return location;
    }

    template<int N, typename T> 
    void Shader::setUniform(const std::string& name, const glm::vec<N,T>& vector)
    {
        throw std::exception();
    }
    template<int N> 
    void Shader::setUniform(const std::string& name, const glm::mat<N,N,float>& matrix)
    {
        throw std::exception();
    }
    template<typename T>
    void Shader::setUniform(const std::string& name, T value)
    {
        throw std::exception();
    }

//########################################################################################
//------------------------------------- float --------------------------------------------
//########################################################################################

    template<>
    void Shader::setUniform<float>(const std::string& name, float value)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform1f(location, value));
    }

    template<> 
    void Shader::setUniform<4, float>(const std::string& name, const glm::vec<4,float>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform4f(location, vector[0], vector[1], vector[2], vector[3]));
    }
    template<> 
    void Shader::setUniform<3, float>(const std::string& name, const glm::vec<3,float>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform3f(location, vector[0], vector[1], vector[2]));
    }
    template<> 
    void Shader::setUniform<2, float>(const std::string& name, const glm::vec<2,float>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform2f(location, vector[0], vector[1]));
    }
    

    template<> 
    void Shader::setUniform<4>(const std::string& name, const glm::mat4& matrix)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
    }
    template<> 
    void Shader::setUniform<3>(const std::string& name, const glm::mat3& matrix)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]));
    }
    template<> 
    void Shader::setUniform<2>(const std::string& name, const glm::mat2& matrix)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniformMatrix2fv(location, 1, GL_FALSE, &matrix[0][0]));
    }


//########################################################################################
//----------------------------------- unsigned int ---------------------------------------
//########################################################################################

    template<>
    void Shader::setUniform<unsigned int>(const std::string& name, unsigned int value)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform1ui(location, value));
    }

    template<> 
    void Shader::setUniform<4, unsigned int>(const std::string& name, const glm::vec<4,unsigned int>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform4ui(location, vector[0], vector[1], vector[2], vector[3]));
    }
    template<> 
    void Shader::setUniform<3, unsigned int>(const std::string& name, const glm::vec<3,unsigned int>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform3ui(location, vector[0], vector[1], vector[2]));
    }
    template<> 
    void Shader::setUniform<2, unsigned int>(const std::string& name, const glm::vec<2,unsigned int>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform2ui(location, vector[0], vector[1]));
    }

//########################################################################################
//-------------------------------------- int ---------------------------------------------
//########################################################################################

    template<>
    void Shader::setUniform<int>(const std::string& name, int value)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform1i(location, value));
    }

    template<> 
    void Shader::setUniform<4, int>(const std::string& name, const glm::vec<4,int>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform4i(location, vector[0], vector[1], vector[2], vector[3]));
    }
    template<> 
    void Shader::setUniform<3, int>(const std::string& name, const glm::vec<3,int>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform3i(location, vector[0], vector[1], vector[2]));
    }
    template<> 
    void Shader::setUniform<2, int>(const std::string& name, const glm::vec<2,int>& vector)
    {
        int location = getUniformLocation(name);
        GL_CALL(glUniform2i(location, vector[0], vector[1]));
    }
}