#pragma once

#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/vertexBufferLayout.hpp"

#include <memory>

namespace MyEngine::OpenGL
{

    /**
     * @brief Abstraction for openGL Vertex Array Object.
     * 
     */
    class VertexArray
    {
    public:
        /**
         * @brief Construct a new Vertex Array object.
         * Creates a openGL vertex array object.
         * 
         */
        VertexArray();
        /**
         * @brief Destroy the Vertex Array object.
         * Destroys an openGL vertex array object (with stored id).
         * 
         */
        ~VertexArray();

        /**
         * @brief Binds vertex array  (with stored id) in the GPU.
         * 
         */
        void bind();
        /**
         * @brief Unbinds vertex array (binds vertex array with id 0) in the GPU.
         * 
         */
        void unbind();

        /**
         * @brief Assign buffer with specified layout
         * 
         * @param t_buffer buffer to be attached to this vertex array
         * @param t_layout layout of the attached buffer
         * @param t_firstPos position at which buffer starts
         * 
         * @return unsigned int next unused position in buffer
         * For example, if layout was [3 floats][4 floats] then the next position returned will be 2
         * 
         */
        unsigned int setBuffer(VertexBuffer& t_buffer, VertexBufferLayout const& t_layout, unsigned int t_firstPos = 0);
    private:
        void addAttrib(VertexBufferElement const& t_element, 
            unsigned int t_pos, unsigned int t_offset, 
            unsigned int t_stride) const;

        unsigned int m_rendererId = 0;
    };
}