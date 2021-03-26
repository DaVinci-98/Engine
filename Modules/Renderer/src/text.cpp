#include "Renderer/text.hpp"
#include "Renderer/triangle2D.hpp"
#include "Helpers/logger.hpp"
#include "tinyxml2.h"

namespace MyEngine::Renderer
{
    unsigned int Text::getTextWidth(std::string&& t_text)
    {
        unsigned glyphNum = t_text.size();
        unsigned int width = 0;
        for(std::size_t i = 0; i < glyphNum; i++)
        {
            auto& glyph = m_glyphs[static_cast<char>(t_text.at(i))];
            width += glyph.m_width;
        }
        return width;
    }

    unsigned int Text::getTextHeight(std::string&& t_text)
    {
        unsigned glyphNum = t_text.size();
        unsigned int height = 0;
        for(std::size_t i = 0; i < glyphNum; i++)
        {
            auto& glyph = m_glyphs[static_cast<char>(t_text.at(i))];
            if(glyph.m_height > height)
                height = glyph.m_height;
        }
        return height;
    }

    bool Text::setFont(std::string&& t_bitmapPath, std::string&& t_fontPath, std::shared_ptr<Shader> t_textureShader)
    {
        m_fontBitmapPath = std::move(t_bitmapPath);
        m_textureShader = t_textureShader;

        if(!makeGlyphMap(std::move(t_fontPath)))
        {
            Helpers::Logger::log<Text>() -> error(
                "[makeGlyphMap()]: could not make glyph map.");
            return false;
        }
        else
        {
            m_fontSet = true;
            return true;
        }
    }

    void Text::setText(std::string&& t_text)
    {
        if(!m_fontSet)
        {
            Helpers::Logger::log<Text>() -> error(
                "[setText]: font hast to be set before calling this function.");
            return;
        }

        unsigned glyphNum = t_text.size();
        unsigned int x = 0;
        if(!material())
        {
            unsigned int width = getTextWidth(std::string(t_text));
            unsigned int height = getTextHeight(std::string(t_text));
            scale(1.0/width, 1.0/height);
        }

        std::vector<Triangle2D> meshTriangles;
        std::vector<Triangle2D> materialTriangles;
        std::shared_ptr<Mesh2D> mesh = std::make_shared<Mesh2D>();
        std::shared_ptr<Material> material = std::make_shared<Material>(m_textureShader);

        for(std::size_t i = 0; i < glyphNum; i++)
        {
            auto& glyph = m_glyphs[static_cast<char>(t_text.at(i))];
            
            Triangle2D materialBottomLeft(
                float(glyph.m_x)/m_bitmapWidth,                 float(glyph.m_x)/m_bitmapWidth,  float(glyph.m_x+glyph.m_width)/m_bitmapWidth, 
                float(glyph.m_y+glyph.m_height)/m_bitmapHeight, float(glyph.m_y)/m_bitmapHeight, float(glyph.m_y)/m_bitmapHeight);
            Triangle2D materialTopRight(
                float(glyph.m_x+glyph.m_width)/m_bitmapWidth, float(glyph.m_x+glyph.m_width)/m_bitmapWidth,   float(glyph.m_x)/m_bitmapWidth, 
                float(glyph.m_y)/m_bitmapHeight,              float(glyph.m_y+glyph.m_height)/m_bitmapHeight, float(glyph.m_y+glyph.m_height)/m_bitmapHeight);
            materialTriangles.push_back(std::move(materialBottomLeft));
            materialTriangles.push_back(std::move(materialTopRight));

            Triangle2D meshBottomLeft(
                x, x, x+glyph.m_width, 
                glyph.m_height, 0, 0);
            Triangle2D meshTopRight(
                x+glyph.m_width, x+glyph.m_width, x, 
                0, glyph.m_height, glyph.m_height);
            meshTriangles.push_back(std::move(meshBottomLeft));
            meshTriangles.push_back(std::move(meshTopRight));
            
            x += glyph.m_width;
        }
        mesh -> setTriangles(std::move(meshTriangles), false);
        material -> setTexture(std::move(materialTriangles), m_fontBitmapPath, false);
        
        setMeshMaterial(mesh, material);
    }

    bool Text::makeGlyphMap(std::string&& t_fontPath)
    {
        tinyxml2::XMLDocument doc;
        if(!doc.LoadFile(t_fontPath.c_str()))
        {
            Helpers::Logger::log<tinyxml2::XMLDocument>() -> error(
                "[loadFile()]: could not load font: " + t_fontPath);
            return false;
        }

        tinyxml2::XMLDocument docHandle(&doc);

        auto common = docHandle.FirstChild() -> FirstChildElement("common");
        common->QueryUnsignedAttribute("scaleW", &m_bitmapWidth);
        common->QueryUnsignedAttribute("scaleH", &m_bitmapHeight);

        auto chars = docHandle.FirstChild() -> FirstChildElement("chars");
        unsigned int charNum = 0;
        chars->QueryUnsignedAttribute("count", &charNum);

        auto charNode = chars -> FirstChild() -> ToElement();
        if(!charNode)
        {
            Helpers::Logger::log<tinyxml2::XMLDocument>() -> error(
                "[makeGlyphMap()]: wrong xml file structure.");
            return false;        
        }
        while(charNode)
        {
            Glyph glyph;
            int id;

            charNode->QueryUnsignedAttribute("x", &glyph.m_x);
            charNode->QueryUnsignedAttribute("y", &glyph.m_y);
            charNode->QueryUnsignedAttribute("width", &glyph.m_width);
            charNode->QueryUnsignedAttribute("height", &glyph.m_height);
            charNode->QueryIntAttribute("id", &id);
            glyph.m_y = m_bitmapHeight - glyph.m_y - glyph.m_height;

            m_glyphs.insert(std::pair<char, Glyph>(static_cast<char>(id), glyph));
            charNode = charNode -> NextSiblingElement();
        }

        if(m_glyphs.size() != charNum)
            Helpers::Logger::log<tinyxml2::XMLDocument>() -> warn(
                "[makeGlyphMap()]: some chars may not have been loaded ({0}/{1}).",
                std::to_string(m_glyphs.size()), std::to_string(charNum));
        return true;
    }
}