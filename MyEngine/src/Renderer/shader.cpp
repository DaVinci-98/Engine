#include "Renderer/shader.hpp"
#include "ShaderGenerator/block.hpp"
#include "ShaderGenerator/shaderGen.hpp"
#include "ShaderGenerator/positionBlock.hpp"
#include "ShaderGenerator/colourBlock.hpp"
#include "ShaderGenerator/textureBlock.hpp"
#include "OpenGL/glException.hpp"

#include <algorithm>

namespace MyEngine::Renderer
{
    const std::string Shader::VIEW_UNIFORM = "u_view";
    const std::string Shader::MODEL_UNIFORM = "u_model";
    const std::string Shader::PROJECTION_UNIFORM = "u_projection";
    const std::string Shader::TEXTURE_UNIFORM = "u_texture";

    std::shared_ptr<Shader> Shader::createColourShader()
    {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>();
        shader -> m_shader = shader -> makeShader(ShaderGenerator::ColourBlock());
        shader -> m_isColour = true;

        return shader;
    }

    std::shared_ptr<Shader> Shader::createTextureShader()
    {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>();
        shader -> m_shader = shader -> makeShader(ShaderGenerator::TextureBlock(TEXTURE_UNIFORM));
        shader -> m_isTexture = true;

        return shader;
    }

    void Shader::bind()
    {
        if(m_bound) return;
        m_bound = true;
        m_shader -> bind();

        setAllUniforms();
    }

    void Shader::unbind()
    {
        if(!m_bound) return;
        m_bound = false;

        m_shader -> unbind();
    }

    void Shader::setAllUniforms()
    {
        try
        {
            for(auto& [name, value] : m_textureUniforms)
                m_shader -> setUniform(name, value);
            for(auto& [name, value] : m_vec2Uniforms)
                m_shader -> setUniform(name, value);
            for(auto& [name, value] : m_vec4Uniforms)
                m_shader -> setUniform(name, value);
            for(auto& [name, value] : m_mat4Uniforms)
                m_shader -> setUniform(name, value);
        }
        catch(OpenGL::GlException& e)
        {
            e.printErrors();
        }
    }

    void Shader::setTextureUniform(std::string t_name, int t_id, bool t_noCache)
    {
        if(!t_noCache)
            m_textureUniforms[t_name] = t_id;
        if(m_bound)
            m_shader -> setUniform(t_name, t_id);
    }
    void Shader::setVec2Uniform(std::string t_name, glm::vec2 const& t_value, bool t_noCache)
    {
        if(!t_noCache) 
            m_vec2Uniforms[t_name] = t_value;
        if(m_bound)
            m_shader -> setUniform(t_name, t_value);
    }
    void Shader::setVec4Uniform(std::string t_name, glm::vec4 const& t_value, bool t_noCache)
    { 
        if(!t_noCache)
            m_vec4Uniforms[t_name] = t_value;
        if(m_bound)
            m_shader -> setUniform(t_name, t_value);
    }
    void Shader::setMat4Uniform(std::string t_name, glm::mat4 const& t_value, bool t_noCache)
    {
        if(!t_noCache) 
            m_mat4Uniforms[t_name] = t_value;
        if(m_bound)
            m_shader -> setUniform(t_name, t_value);
    }

    std::unique_ptr<OpenGL::Shader> Shader::makeShader(ShaderGenerator::Block&& t_materialBlock)
    {
        ShaderGenerator::ShaderGen generator;
        std::vector<ShaderGenerator::Block> blocks
        {
            ShaderGenerator::PositionBlock(MODEL_UNIFORM, VIEW_UNIFORM, PROJECTION_UNIFORM),
            std::move(t_materialBlock)
        };
        generator.setBlocks(std::move(blocks));

        std::vector<OpenGL::Shader::ShaderText> shaders
        {
            OpenGL::Shader::ShaderText{ generator.makeFragment(), OpenGL::Shader::ShaderType::FRAGMENT },
            OpenGL::Shader::ShaderText{ generator.makeVertex(), OpenGL::Shader::ShaderType::VERTEX }
        };

        makeUniforms(generator);
        return std::make_unique<OpenGL::Shader>(shaders);
    }

    void Shader::makeUniforms(ShaderGenerator::ShaderGen& t_shaderGen)
    {
        for(auto& uniform : t_shaderGen.uniforms())
        {
            switch(uniform.m_type)
            {
            case(ShaderGenerator::Block::FieldType::SAMPLER2D):
                m_textureUniforms.insert(std::pair<std::string, unsigned int>(uniform.m_name, 0));
                break;
            case(ShaderGenerator::Block::FieldType::VEC2):
                m_vec2Uniforms.insert(std::pair<std::string, glm::vec2>(uniform.m_name, glm::vec2(1)));
                break;
            case(ShaderGenerator::Block::FieldType::VEC4):
                m_vec4Uniforms.insert(std::pair<std::string, glm::vec4>(uniform.m_name, glm::vec4(1)));
                break;
            case(ShaderGenerator::Block::FieldType::MAT4):
                m_mat4Uniforms.insert(std::pair<std::string, glm::mat4>(uniform.m_name, glm::mat4(1)));
                break;
            }
        }
    }
}