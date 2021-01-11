#include "glad/glad.h"

#include "OpenGL/texture.hpp"
#include "OpenGL/glException.hpp"
#include "stb_image.h"
#include "Helpers/logger.hpp"

#include <iostream>

namespace MyEngine::OpenGL
{
    Texture::Texture(std::string const& t_filePath)
        : m_filePath(t_filePath)
    {
        stbi_set_flip_vertically_on_load(1);
        m_localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_BMP, 4);

        GL_CALL(glGenTextures(1, &m_rendererId));
        bind();

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
        unbind();

        if(m_localBuffer) 
        {
            stbi_image_free(m_localBuffer);
            m_localBuffer = nullptr;
        }

        // Helpers::Logger::log<Texture>() -> info("[Load] [" + t_filePath + "] [" + std::to_string(m_rendererId) + "]: Done");
    }

    Texture::~Texture()
    {
        try
        {
            if(m_localBuffer != nullptr) stbi_image_free(m_localBuffer);
            if(m_rendererId != 0) GL_CALL(glDeleteTextures(1, &m_rendererId));
            // Helpers::Logger::log<Texture>() -> info("[Destroy] [" + std::to_string(m_rendererId) + "]: Done");
        }
        catch(GlException const& e)
        {
            e.printErrors();
        } 
    }

    void Texture::bind(unsigned int t_slot)
    {
        GL_CALL(glActiveTexture(GL_TEXTURE0 + t_slot));
        GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));
    }

    void Texture::unbind()
    {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
    }
}