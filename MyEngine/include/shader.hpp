#pragma once

#include "glException.hpp"

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <iostream>

struct ShaderFile
{
    std::string m_filepath;
    unsigned int m_type;
};


namespace MyEngine
{
    class Shader
    {
    public:
        Shader(std::vector<ShaderFile> const& t_files);
        Shader() { };
        ~Shader();

        void init(std::vector<ShaderFile> const& t_files);
        void bind();
        void unbind();
        bool bound() const { return m_bound; } 

        template<typename T>
        void setUniform(std::string const& t_name, T t_value);
        template<int N, typename T> 
        void setUniform(std::string const& t_name, glm::vec<N,T> const& t_vector);
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