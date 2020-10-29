#pragma once

#include "Renderer/object.hpp"
#include "Renderer/triangle2D.hpp"

#include <memory>

namespace MyEngine::Renderer
{
    // Arbitrary 2D object
    class Object2D : public Object
    {
    public:
        Object2D() : Object() { };

        // Copy a triangle to obejct's triangle list.
        bool pushTriangle(Triangle2D const& t_triangle);
        // Add a texture to the obejct.
        bool mapTexture(std::vector<Triangle2D> const& t_coordinates, std::string const& t_path);

    private:
        void triangleToVAO(std::unique_ptr<Triangle> const& t_triangle) override;
        void saveVertex(std::vector<float> const& t_vertex);
    };
}