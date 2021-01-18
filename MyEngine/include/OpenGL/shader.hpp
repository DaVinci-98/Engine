#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <unordered_map>

namespace MyEngine::OpenGL
{
    /**
     * @brief Responsible for storing and interaction with uniforms.
     * 
     */
    class Shader
    {
    public:
        enum ShaderType
        {
            FRAGMENT = 0x8B30,
            VERTEX = 0x8B31
        };

        struct ShaderFile
        {
            std::string m_filepath;
            ShaderType m_type;
        };

        struct ShaderText
        {
            std::string m_shaderText;
            ShaderType m_type;
        };

        /**
         * @brief Construct a new Shader object from file.
         * Compiles provided shaders and builds na openGL program.
         * 
         */
        Shader(std::vector<ShaderFile> const& t_files);
        /**
         * @brief Construct a new Shader object from string.
         * Compiles provided shaders and builds na openGL program.
         * 
         */
        Shader(std::vector<ShaderText> const& t_shaders);
        /**
         * @brief Destroy the Shader object.
         * Destroy associated openGL program.
         * 
         */
        ~Shader();

        /**
         * @brief Binds program (with stored id) in the GPU.
         * 
         */
        void bind();
        /**
         * @brief Unbinds program (binds program with id 0) in the GPU.
         * 
         */
        void unbind();

        /**
         * @brief Set uniform value.
         * 
         * @tparam T type of value set
         * @param t_name name of the uniform
         * @param t_value value to be set
         */
        template<typename T>
        void setUniform(std::string const& t_name, T t_value);
        /**
         * @brief Set a vector of uniform values.
         * 
         * @tparam N number of values in vector
         * @tparam T type of values to be set
         * @param t_name name of the uniform
         * @param t_vector values to be set
         */
        template<int N, typename T> 
        void setUniform(std::string const& t_name, glm::vec<N,T> const& t_vector);
        /**
         * @brief Set a (square) matrix uniform.
         * 
         * @tparam N - dimension of matrix
         * @param t_name name of the uniform
         * @param t_matrix matrix to be set
         */
        template<int N> 
        void setUniform(std::string const& t_name, glm::mat<N,N,float> const& t_matrix);
    private:
        unsigned int attachShader(ShaderText const& t_shader);
        void detachShader(unsigned int t_id);
        unsigned int compileShader(std::string const& t_source, unsigned int t_type) const;        
        std::string readFile(std::string const& t_path) const;
        int getUniformLocation(std::string const& t_name);

        std::unordered_map<std::string, int> m_locations;
        unsigned int m_rendererId = 0;
    };
}