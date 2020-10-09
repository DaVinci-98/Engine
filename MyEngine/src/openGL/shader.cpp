#include "glad/glad.h"

#include "openGL/shader.hpp"
#include "openGL/glException.hpp"

#include <exception>
#include <iostream>
#include <algorithm>

namespace MyEngine
{
    Shader::Shader(std::vector<ShaderFile> const& t_files)
    {
        std::vector<unsigned int> idList;
        GL_CALL(m_rendererId = glCreateProgram());

        for(auto const& file : t_files) 
            idList.push_back(attachShader(file)); 


        GL_CALL(glLinkProgram(m_rendererId));
        GL_CALL(glValidateProgram(m_rendererId));

        for(auto const& id : idList) 
            detachShader(id);
    }

    Shader::~Shader()
    {
        try
        {
            GL_CALL(glDeleteProgram(m_rendererId));
        }
        catch(GlException const& e)
        {
            e.printErrors();
        }      
    }

    unsigned int Shader::attachShader(ShaderFile const& t_file)
    {
        std::string shader = readFile(t_file.m_filepath);
        if(shader == "") throw std::exception();

        unsigned int id = compileShader(shader, t_file.m_type);
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
            std::cout<<"[ERROR]"<<std::endl;
            std::cout << "- function : Shader -> attachShader -> readFile." << std::endl;
            std::cout << "- message  : " << "Could not open file." << std::endl;
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

            std::cout << "[ERROR]" <<std::endl;
            std::cout << "- function : Compile shader." << std::endl;
            std::cout << "- message  : " << message << std::endl;

            glDeleteShader(id);

            return 0;
        }

        return id;
    }

    void Shader::bind()
    {
        if(m_bound) return;
        GL_CALL(glUseProgram(m_rendererId));
        m_bound = true;
    }

    void Shader::unbind()
    {
        if(!m_bound) return;
        GL_CALL(glUseProgram(0));
        m_bound = false;
    }

    int Shader::getUniformLocation(std::string const& t_name)
    {
        if(m_locations.find(t_name) != m_locations.end()) return m_locations[t_name];

        GL_CALL(int location = glGetUniformLocation(m_rendererId, t_name.c_str()));
        if(location < 0)
        {
            std::cout << "[ERROR]" << std::endl;
            std::cout << "- message : Invalid uniform" << std::endl;
            std::cout << "- name    : " << t_name << std::endl;
        }
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