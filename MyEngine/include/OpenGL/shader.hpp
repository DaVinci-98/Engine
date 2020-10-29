#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <iostream>

namespace MyEngine::OpenGL
{
    struct ShaderFile
    {
        std::string m_filepath;
        unsigned int m_type;
    };

    // Responsible for storing shaders and interaction with uniforms.
    class Shader
    {

    public:
        Shader(std::vector<ShaderFile> const& t_files);
        Shader() { };
        ~Shader();

        void bind();
        void unbind();
        bool bound() const { return m_bound; } 

        // set uniform value
        template<typename T>
        void setUniform(std::string const& t_name, T t_value);
        // set uniform vector
        template<int N, typename T> 
        void setUniform(std::string const& t_name, glm::vec<N,T> const& t_vector);
        // set uniform matrix
        template<int N> 
        void setUniform(std::string const& t_name, glm::mat<N,N,float> const& t_matrix);
    private:
        unsigned int attachShader(ShaderFile const& t_file);
        void detachShader(unsigned int t_id);
        unsigned int compileShader(std::string const& t_source, unsigned int t_type) const;        
        std::string readFile(std::string const& t_path) const;
        int getUniformLocation(std::string const& t_name);

        std::unordered_map<std::string, int> m_locations;
        unsigned int m_rendererId = 0;
        bool m_bound = false;
    };
}