#pragma once

#include <array>
#include <vector>

namespace MyEngine::OpenGL
{
    /**
     * @brief Abstraction for openGL buffer object.
     * Identifies which vertices belong to a triangle, by their indexes in vertex buffer.
     * 
     */
    class IndexBuffer
    {
    public:
        /**
         * @brief Construct a new Index Buffer object. And creates an openGL buffer.
         * 
         * @param t_data vector of uints reprsenting indexes of vertices.
         */
        IndexBuffer(std::vector<unsigned int> const& t_data);
        /**
         * @brief Destroy the Index Buffer object.
         * Destroys associated openGL buffer.
         * 
         */
        ~IndexBuffer();

        /**
         * @brief Binds buffer (with stored id) in the GPU.
         * 
         */
        void bind();
        /**
         * @brief Unbinds buffer (binds buffer with id 0) in the GPU.
         * 
         */
        void unbind();

        /**
         * @brief Number of indexes in the buffer.
         * 
         */
        unsigned int count() 
            const { return m_count; } 
    private:
        unsigned int m_rendererId = 0;
        unsigned int m_count = 0;
    };
}