#pragma once
#include <string>

namespace MyEngine::OpenGL
{
    /**
     * @brief Stores a texture using openGL.
     * 
     */
    class Texture
    {
    public:
        /**
         * @brief Construct a new Texture object.
         * Loads the texture from the provided path.
         * 
         * @param t_filePath path to texture file.
         */
        Texture(std::string const& t_filePath);
        /**
         * @brief Destroy the Texture object.
         * Deletes texture from openGL.
         * 
         */
        ~Texture();

        /**
         * @brief Binds texture (with stored id) in the GPU.
         * 
         * @param t_slot slot in which texture will be binded.
         * Textures are bound to different slots, 
         * to access them a uniform has to be set to their slot.
         * 
         */
        void bind(unsigned int t_slot = 0);
        /**
         * @brief Unbinds texture (binds texture with id 0) in the GPU.
         * 
         */
        void unbind();
        /**
         * @brief Texture's width in pixels.
         * 
         */
        int width() const 
            { return m_width; } 
        /**
         * @brief Texture's height in pixels.
         * 
         */
        int height() const 
            { return m_height; } 
        /**
         * @brief Id of the openGL texture object.
         * 
         */
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