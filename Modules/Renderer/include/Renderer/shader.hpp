#pragma once

#include "OpenGL/shader.hpp"
#include "OpenGL/vertexBufferLayout.hpp"
#include "ShaderGenerator/block.hpp"
#include "ShaderGenerator/shaderGen.hpp"

#include <memory>
#include <map>
#include <glm/glm.hpp>

namespace MyEngine::Renderer
{
    /**
     * @brief Abstractions of openGl shaders used in renderer.
     * 
     */
    class Shader
    {
    public:
        /**
         * @brief Returns a shared pointer to a shader rendering triangles with flat colour.
         * 
         */
        static std::shared_ptr<Shader> createColourShader();
        /**
         * @brief Returns a shared pointer to a shader rendering triangles with a texture.
         * 
         */
        static std::shared_ptr<Shader> createTextureShader();

        /**
         * @brief Binds underlying OpenGl::Shader object.
         * 
         */
        void bind();
        /**
         * @brief Unbinds underlying OpenGL::Shader object.
         * 
         */
        void unbind();
        
        /**
         * @brief Sets a texture uniform in shader with provided value.
         * 
         * @param t_name name of the uniform
         * @param t_id slot in which texture is bound
         * @param t_noCache don't cache the value
         * (normally the value is saved and the uniform will be automatically set
         * when the shader is bound next time)
         */
        void setTextureUniform(std::string t_name, int t_id, bool t_noCache = false);
        /**
         * @brief Set a vec2 uniform in shader with provided value.
         * 
         * @param t_name name of the uniform
         * @param t_value value to be set
         * @param t_noCache don't cache the value
         * (normally the value is saved and the uniform will be automatically set
         * when the shader is bound next time)
         */
        void setVec2Uniform(std::string t_name, glm::vec2 const& t_value, bool t_noCache = false);
        /**
         * @brief Set a vec4 uniform in shader with provided value.
         * 
         * @param t_name name of the uniform
         * @param t_value value to be set
         * @param t_noCache don't cache the value
         * (normally the value is saved and the uniform will be automatically set
         * when the shader is bound next time)
         */
        void setVec4Uniform(std::string t_name, glm::vec4 const& t_value, bool t_noCache = false);
        /**
         * @brief Set a mat4 uniform in shader with provided value.
         * 
         * @param t_name name of the uniform
         * @param t_value value to be set
         * @param t_noCache don't cache the value
         * (normally the value is saved and the uniform will be automatically set
         * when the shader is bound next time)
         */
        void setMat4Uniform(std::string t_name, glm::mat4 const& t_value, bool t_noCache = false);

        /**
         * @brief Returns true if shader renders triangles with a texture.
         * 
         */
        inline bool usesTexture() const
            { return m_isTexture; }

        /**
         * @brief Name of the uniform for view matrix.
         * 
         */
        static const std::string VIEW_UNIFORM;
        /**
         * @brief Name of the uniform for model matrix.
         * 
         */
        static const std::string MODEL_UNIFORM;
        /**
         * @brief Name of the uniform for projection matrix.
         * 
         */
        static const std::string PROJECTION_UNIFORM;
        /**
         * @brief Name of the uniform for texture.
         * 
         */
        static const std::string TEXTURE_UNIFORM;
        /**
         * @brief Name of the uniform for colour.
         * 
         */
        static const std::string COLOUR_UNIFORM;
    private:
        std::unique_ptr<OpenGL::Shader> makeShader(ShaderGenerator::Block&& t_materialBlock);
        void makeUniforms(ShaderGenerator::ShaderGen& t_shaderGen);
        void setAllUniforms();

        std::map<std::string, glm::vec2> m_vec2Uniforms;
        std::map<std::string, glm::vec4> m_vec4Uniforms;
        std::map<std::string, glm::mat4> m_mat4Uniforms;
        std::map<std::string, int> m_textureUniforms;

        bool m_isTexture = false;
        bool m_isColour = false;
        bool m_bound = false;

        std::unique_ptr<OpenGL::Shader> m_shader;
    };
}
