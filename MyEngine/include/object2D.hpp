#pragma once
#include "object.hpp"
#include "triangle2D.hpp"

#include <memory>

namespace MyEngine
{
    // Arbitrary 2D object
    class Object2D : public Object
    {
    public:
        Object2D() : Object() { };
        ~Object2D() { };

        // Copy a triangle to obejct's triangle list.
        bool pushTriangle(Triangle2D const& t_triangle);
        // Add a texture to the obejct.
        bool mapTexture(std::vector<Triangle2D> const& t_coordinates, std::string const& t_path);

    private:
        void triangleToVAO(std::unique_ptr<Triangle> const& t_triangle) override;
        void saveVertex(std::vector<float> const& t_vertex);
    };
}