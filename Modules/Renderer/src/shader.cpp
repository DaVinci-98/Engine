#include "Renderer/shader.hpp"
#include "OpenGL/glException.hpp"

#include <algorithm>

namespace MyEngine::Renderer
{
    const std::string Shader::VIEW_UNIFORM = "u_view";
    const std::string Shader::MODEL_UNIFORM = "u_model";
    const std::string Shader::PROJECTION_UNIFORM = "u_projection";
    const std::string Shader::TEXTURE_UNIFORM = "u_texture";
    const std::string Shader::COLOUR_UNIFORM = "u_colour";

    std::shared_ptr<Shader> Shader::createColourShader()
    {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>();
        shader -> m_shader = shader -> makeShader(
            "#version 450 core\n"
            "layout(location = 0) in vec4 position;\n"
            "uniform mat4 " + MODEL_UNIFORM + ";\n"
            "uniform mat4 " + VIEW_UNIFORM + ";\n"
            "uniform mat4 " + PROJECTION_UNIFORM + ";\n"
            "uniform vec4 " + COLOUR_UNIFORM + ";\n"
            "out vec4 v_colour;\n"
            "void main() {\n"
            "    mat4 MVP = u_projection * u_view * u_model;\n"
            "    gl_Position = MVP * position;\n"
            "    v_colour = u_colour;\n"
            "};",
            "#version 450 core\n"
            "layout(location = 0) out vec4 color;\n"
            "in vec4 v_colour;\n"
            "void main() {\n"
            "    color = v_colour;\n"
            "};\n",
            std::vector<UniformItem>
            {
                UniformItem{
                    .m_name = MODEL_UNIFORM,
                    .m_type = FieldType::MAT4},
                UniformItem{
                    .m_name = VIEW_UNIFORM,
                    .m_type = FieldType::MAT4},
                UniformItem{
                    .m_name = PROJECTION_UNIFORM,
                    .m_type = FieldType::MAT4},
                UniformItem{
                    .m_name = COLOUR_UNIFORM,
                    .m_type = FieldType::VEC4}
            }
        );
        shader -> m_isColour = true;

        return shader;
    }

    std::shared_ptr<Shader> Shader::createTextureShader()
    {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>();
        shader -> m_shader = shader -> makeShader(
            "#version 450 core\n"
            "layout(location = 0) in vec4 position;\n"
            "layout(location = 1) in vec2 texCoord;\n"
            "uniform mat4 " + VIEW_UNIFORM + ";\n"
            "uniform mat4 " + MODEL_UNIFORM + ";\n"
            "uniform mat4 " + PROJECTION_UNIFORM + ";\n"
            "out vec2 v_texCoord;\n"
            "void main() {\n"
            "    mat4 MVP = u_projection * u_view * u_model;\n"
            "    gl_Position = MVP * position;\n"
            "    v_texCoord = texCoord;\n"
            "};\n",
            "#version 450 core\n"
            "layout(location = 0) out vec4 color;\n"
            "uniform sampler2D " + TEXTURE_UNIFORM + ";\n"
            "in vec2 v_texCoord;\n"
            "void main() {\n"
            "    color = texture(u_texture, v_texCoord);\n"
            "};\n",
            std::vector<UniformItem>
            {
                UniformItem{
                    .m_name = MODEL_UNIFORM,
                    .m_type = FieldType::MAT4},
                UniformItem{
                    .m_name = VIEW_UNIFORM,
                    .m_type = FieldType::MAT4},
                UniformItem{
                    .m_name = PROJECTION_UNIFORM,
                    .m_type = FieldType::MAT4},
                UniformItem{
                    .m_name = TEXTURE_UNIFORM,
                    .m_type = FieldType::SAMPLER2D}
            }
        );
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

    std::unique_ptr<OpenGL::Shader> Shader::makeShader(std::string&& t_vertex, std::string&& t_fragment, std::vector<UniformItem>&& t_uniforms)
    {
        std::vector<OpenGL::Shader::ShaderText> shaders
        {
            OpenGL::Shader::ShaderText{ std::move(t_fragment), OpenGL::Shader::ShaderType::FRAGMENT },
            OpenGL::Shader::ShaderText{ std::move(t_vertex), OpenGL::Shader::ShaderType::VERTEX }
        };

        makeUniforms(std::move(t_uniforms));
        return std::make_unique<OpenGL::Shader>(shaders);
    }

    void Shader::makeUniforms(std::vector<UniformItem>&& t_uniforms)
    {
        for(auto& uniform : t_uniforms)
        {
            switch(uniform.m_type)
            {
            case(FieldType::SAMPLER2D):
                m_textureUniforms.insert(std::pair<std::string, unsigned int>(uniform.m_name, 0));
                break;
            case(FieldType::VEC2):
                m_vec2Uniforms.insert(std::pair<std::string, glm::vec2>(uniform.m_name, glm::vec2(1)));
                break;
            case(FieldType::VEC4):
                m_vec4Uniforms.insert(std::pair<std::string, glm::vec4>(uniform.m_name, glm::vec4(1)));
                break;
            case(FieldType::MAT4):
                m_mat4Uniforms.insert(std::pair<std::string, glm::mat4>(uniform.m_name, glm::mat4(1)));
                break;
            }
        }
    }
}