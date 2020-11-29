#pragma once
#include <string>

namespace MyEngine::OpenGL
{
    // Stores a texture
    class Texture
    {
    public:
        Texture(std::string const& t_filePath);
        ~Texture();

        void bind(unsigned int t_slot = 0);
        void unbind();
        int width() const { return m_width; } 
        int height() const { return m_height; } 
        inline unsigned int id() const
            { return m_rendererId; }
    private:
        unsigned int m_rendererId = 0;
        std::string m_filePath;
        unsigned char* m_localBuffer = nullptr;
        int m_width = 0;
        int m_height = 0;
        int m_BMP = 0;
    };    
}