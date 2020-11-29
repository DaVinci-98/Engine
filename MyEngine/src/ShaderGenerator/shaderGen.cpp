#include "ShaderGenerator/shaderGen.hpp"

#include <string>
#include <sstream>

namespace MyEngine::ShaderGenerator
{
    std::string ShaderGen::makeVertex()
    {
        std::stringstream locations;
        std::stringstream uniforms;
        std::stringstream outs;
        std::stringstream code;
        int pos = 0;

        for(auto & block : m_blocks)
        {
            for(auto& [type, name] : block.getVertexLocations())
            {
                locations<<"layout(location = "<<pos<<") in "
                         <<Block::getTypeString(type)<<" "<<name
                         <<";"<<std::endl;
                m_vertexLayout.push_back(VertexLayoutItem{ name, pos, Block::getTypeSize(type) });
                pos++;
            }
            for(auto& [type, name] : block.getVertexUniforms())
            {
                uniforms<<"uniform " <<Block::getTypeString(type)<<" "<<name
                        <<";"<<std::endl;
                m_unifroms.push_back(UniformItem{ name, type });
            }
            for(auto& [type, name] : block.getVertexOuts())
                outs<<"out "<<Block::getTypeString(type)<<" "<<name
                    <<";"<<std::endl;
            for(auto& item : block.getVertexCodeLines())
                code<<"\t"<<item<<";"<<std::endl;
        }
        return pieceOutCode(m_version, locations, uniforms, outs, code);
    }

    std::string ShaderGen::makeFragment()
    {
        std::stringstream locations;
        std::stringstream uniforms;
        std::stringstream ins;
        std::stringstream code;
        unsigned int pos = 0;

        for(auto & block : m_blocks)
        {
            for(auto& [type, name] : block.getFragmentLocations())
                locations<<"layout(location = "<<pos++<<") out "
                         <<Block::getTypeString(type)<<" "<<name
                         <<";"<<std::endl;
            for(auto& [type, name] : block.getFragmentUniforms())
            {
                uniforms<<"uniform " <<Block::getTypeString(type)<<" "<<name
                        <<";"<<std::endl;
                m_unifroms.push_back(UniformItem{name, type});
            }
            for(auto& [type, name] : block.getFragmentIns())
                ins<<"in "<<Block::getTypeString(type)<<" "<<name
                    <<";"<<std::endl;
            for(auto& item : block.getFragmentCodeLines())
                code<<"\t"<<item<<";"<<std::endl;
        }
        return pieceOutCode(m_version, locations, uniforms, ins, code);
    }
    
    std::string ShaderGen::pieceOutCode(
        std::string& t_version,
        std::stringstream& t_locations, 
        std::stringstream& t_uniforms,
        std::stringstream& t_inOuts,
        std::stringstream& t_code)
    {
        std::stringstream shader;
        shader<<"#version "<<t_version<<" core"<<std::endl;
        shader<<t_locations.str()<<std::endl;
        shader<<t_uniforms.str()<<std::endl;
        shader<<t_inOuts.str()<<std::endl;
        shader<<"void main() {"<<std::endl;
        shader<<t_code.str()<<std::endl;
        shader<<"};"<<std::endl;
        return shader.str();
    }
}