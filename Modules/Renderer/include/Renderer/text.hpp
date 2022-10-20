#pragma once

#include "Renderer/drawable2D.hpp"
#include "Renderer/material.hpp"
#include "Renderer/shader.hpp"

#include <map>
#include <memory>

namespace MyEngine::Renderer
{
    /**
     * @brief Drawable text object.
     * 
     */
    class Text: public Drawable2D
    {
    public:
        /**
         * @brief Load font in AngelCode format. 
         * No drawing can be done until it's set.
         * 
         * @param t_bitmapPath path to bitmap png file
         * @param t_fontPath path to xml file with glyph mapping on bitmap
         * @param t_renderer reference to renderer(necessary to create a material)
         */
        bool setFont(std::string& t_bitmapPath, std::string& t_fontPath, std::shared_ptr<Shader> t_textureShader);

        /**
         * @brief Set drawable to provided text
         * (it will span the provided width and height)
         * 
         * @param t_text text to draw
         */
        void setText(std::string&& t_text);
        
        /**
         * @brief Set drawable to provided number
         * (it will span the provided width and height)
         * 
         * @param t_uint number to draw
         */
        inline void setUint(unsigned int t_uint)
            { setText(std::to_string(t_uint)); }
        
        /**
         * @brief Get width of text calculacted from provided bitmap.
         * 
         * @param t_text text to check
         * @return unsigned int - width of the text
         */
        unsigned int getTextWidth(std::string&& t_text);

        /**
         * @brief Get height of text calculacted from provided bitmap.
         * 
         * @param t_text text to check
         * @return unsigned int - height of the text
         */
        unsigned int getTextHeight(std::string&& t_text);

        /**
         * @brief Get width of number calculacted from provided bitmap.
         * 
         * @param t_uint number to check
         * @return unsigned int - width of the number
         */
        unsigned int getUnitWidth(unsigned int t_uint)
            { return getTextWidth(std::to_string(t_uint)); }

        /**
         * @brief Get height of number calculacted from provided bitmap.
         * 
         * @param t_uint number to check
         * @return unsigned int - height of the number
         */
        unsigned int getUnitHeight(unsigned int t_uint)
            {return getTextHeight(std::to_string(t_uint)); }

    private:
        bool makeGlyphMap(std::string&& t_fontPath);
        struct Glyph
        {
            unsigned int m_x = 0;
            unsigned int m_y = 0;
            unsigned int m_width = 0;
            unsigned int m_height = 0;
        };

        unsigned int m_bitmapHeight;
        unsigned int m_bitmapWidth;
        bool m_fontSet = false;
        std::string m_fontBitmapPath;
        std::shared_ptr<Shader> m_textureShader;

        std::map<char, Glyph> m_glyphs;
    };
}