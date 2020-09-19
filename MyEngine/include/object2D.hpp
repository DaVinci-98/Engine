#pragma once
#include "object.hpp"
#include "triangle2D.hpp"

#include <memory>

namespace MyEngine
{
    class Object2D : public Object
    {
    public:
        Object2D() : Object() { };
        ~Object2D() { };

        bool pushTriangle(Triangle2D const& t_triangle);
        bool mapTexture(std::vector<Triangle2D> const& t_coordinates, std::string const& t_path);

    private:
        void bakeTriangle(std::unique_ptr<Triangle> const& t_triangle) override;
        void saveVertex(std::vector<float> const& t_vertex);
    };
}