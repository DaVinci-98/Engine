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
    class Shader
    {
    public:
        static std::shared_ptr<Shader> createColourShader();
        static std::shared_ptr<Shader> createTextureShader();

        void bind();
        void unbind();
        
        void setTextureUniform(std::string t_name, int t_id, bool t_noCache = false);
        void setVec2Uniform(std::string t_name, glm::vec2 const& t_value, bool t_noCache = false);
        void setVec4Uniform(std::string t_name, glm::vec4 const& t_value, bool t_noCache = false);
        void setMat4Uniform(std::string t_name, glm::mat4 const& t_value, bool t_noCache = false);

        inline bool usesTexture() const
            { return m_isTexture; }

        static const std::string VIEW_UNIFORM;
        static const std::string MODEL_UNIFORM;
        static const std::string PROJECTION_UNIFORM;
        static const std::string TEXTURE_UNIFORM;
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
