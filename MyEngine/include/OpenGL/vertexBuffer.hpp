#pragma once

#include <array>
#include <any>
#include <vector>

namespace MyEngine::OpenGL
{

    /**
     * @brief Abstraction for openGL buffer object.
     * Vertex data is stored into GPU memory.
     * 
     */
    class VertexBuffer
    {
    public:
        /**
         * @brief Construct a new Vertex Buffer object. 
         * Creates an openGL buffer of floats. 
         * 
         * @param t_data  data to be copied into the buffer.
         */
        VertexBuffer(std::vector<float> const& t_data);
        /**
         * @brief Construct a new Vertex Buffer object. 
         * Creates an openGL buffer of unsigned ints. 
         * 
         * @param t_data  data to be copied into the buffer.
         */
        VertexBuffer(std::vector<unsigned int> const& t_data);

        /**
         * @brief Destroy the Vertex Buffer object.
         * Destroys associated openGL buffer.
         * 
         */
        ~VertexBuffer();
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
    private:
        unsigned int m_rendererId = 0;
    };
}