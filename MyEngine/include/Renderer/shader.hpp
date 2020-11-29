#pragma once

#include "OpenGL/shader.hpp"
#include "OpenGL/vertexBufferLayout.hpp"
#include "ShaderGenerator/block.hpp"
#include "ShaderGenerator/shaderGen.hpp"

#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>

namespace MyEngine::Renderer
{
    class Shader
    {
    public:
        static std::shared_ptr<Shader> createColourShader();
        static std::shared_ptr<Shader> createTextureShader();

        void bind();
        void unbind();
        
        void setTextureUniform(std::string t_name, unsigned int t_id);
        void setVec2Uniform(std::string t_name, glm::vec2 const& t_value);
        void setVec4Uniform(std::string t_name, glm::vec4 const& t_value);
        void setMat4Uniform(std::string t_name, glm::mat4 const& t_value);

        inline bool usesTexture() const
            { return m_isTexture; }
        
        inline OpenGL::VertexBufferLayout& layout()
            { return m_layout; }

        static const std::string VIEW_UNIFORM;
        static const std::string MODEL_UNIFORM;
        static const std::string PROJECTION_UNIFORM;
        static const std::string TEXTURE_UNIFORM;
    private:
        Shader() { }

        std::unique_ptr<OpenGL::Shader> makeShader(ShaderGenerator::Block&& t_materialBlock);
        void makeUniforms(ShaderGenerator::ShaderGen& t_shaderGen);
        void makeLayout(ShaderGenerator::ShaderGen& t_shaderGen);
        void setAllUniforms();

        std::unordered_map<std::string, glm::vec2> m_vec2Uniforms;
        std::unordered_map<std::string, glm::vec4> m_vec4Uniforms;
        std::unordered_map<std::string, glm::mat4> m_mat4Uniforms;
        std::unordered_map<std::string, unsigned int> m_textureUniforms;

        bool m_isTexture = false;
        bool m_isColour = false;
        bool m_bound = false;

        OpenGL::VertexBufferLayout m_layout;
        std::unique_ptr<OpenGL::Shader> m_shader;
    };
}
