#pragma once

#include "Physics/shared.hpp"

#include <glm/glm.hpp>
#include <vector>
#include <memory>

namespace MyEngine::Physics
{
    /**
     * @brief Represents a rigid body.
     * 
     */
    class Body2D
    {
    public:
        /**
         * @brief Construct a new Body2D object.
         * 
         * @param t_vertices body's vertices in [x,y] format
         * @param t_isDynamic is body moving 
         * (collisions between 2 static bodies are not checked,
         * in static groups collisions between 2 dynamic bodies are also not checked)
         * 
         */
        Body2D(std::vector<glm::vec2> const& t_vertices, bool t_isDynamic);
        /**
         * @brief Construct a new Body2D object.
         * 
         * @param t_vertices body's vertices but in one vector format,
         * useful for coping vertices from mesh.
         * @param t_isDynamic is body moving 
         * (collisions between 2 static bodies are not checked,
         * in static groups collisions between 2 dynamic bodies are also not checked)
         * 
         */
        Body2D(std::vector<float> const& t_vertices, bool t_isDynamic);
        /**
         * @brief Construct a new Body2D object.
         * 
         * @param t_vertices body's vertices in [x,y] format
         * @param t_isDynamic is body moving 
         * (collisions between 2 static bodies are not checked,
         * in static groups collisions between 2 dynamic bodies are also not checked)
         * 
         */
        Body2D(std::vector<glm::vec2> && t_vertices, bool t_isDynamic);

        /**
         * @brief Move body according to it's velocity and acceleration provided number of seconds forward in time.
         * 
         * @param t_time time in seconds
         * 
         */
        void applyMovementStep(float t_time = 1);
        /**
         * @brief Translate a body.
         * (and associated model if it was attached in setAssociatedModel() function)
         * 
         * @param t_translation vector by which body will be moved.
         */
        void applyTranslation(glm::vec2&& t_translation);
        /**
         * @brief Undo last translation.
         * Not reliable for bodies moving with too high/low speed,
         * or bodies that can hit mulitple other bodies, 
         * or bodies that can get stuck inside other collision targets.
         * Insted set objects velocity to -0.5 of previous value and make sure to apply 
         * some ambient acceleration like gravity, body will be constantly shaking,
         * but with update framerate low enough the movement won't bee visible.
         * 
         * @param t_bounce Value can by multiplied to make sure body gets out of the collision.
         */
        void undoLastTranslation(float t_bounce = 1);

        /**
         * @brief Used by the PhysicsManager to apply group's ambient velocity.
         * 
         */
        inline void addGroupVelocity(glm::vec2& t_groupVelocity)
            { m_groupVelocity += t_groupVelocity; }
        /**
         * @brief Used by the PhysicsManager to apply group's ambient acceleration.
         * 
         */
        inline void addGroupAcceleration(glm::vec2& t_groupAcceleration)
            { m_groupAcceleration += t_groupAcceleration; }
        /**
         * @brief Set a model matrix for mesh assciated with this body.
         * Model will be moved alongside body.
         * 
         * @param t_model model matrix in shared pointer.
         */
        inline void setAssociatedModel(std::shared_ptr<glm::mat4> t_model)
            { m_model = t_model; }
        /**
         * @brief Returns a reference to body's acceleration vector.
         * 
         */
        inline glm::vec2& acceleration()
            { return m_acceleration; }
        /**
         * @brief Returns a reference to body's velocity vector.
         * 
         */
        inline glm::vec2& velocity()
            { return m_velocity; }
        /**
         * @brief Returns a vector by which body was last translated.
         * 
         */
        inline glm::vec2 lastTranslation() const
            { return m_lastTranslation; }
        /**
         * @brief Returns coordinates of the center of the body.
         * 
         */
        inline glm::vec2 center() const
            { return m_center; }

        /**
         * @brief Returns true if this body was constructed as a static body.
         * 
         */
        inline bool isStatic() const
            { return !m_dynamic; }
        /**
         * @brief Returns true if this body was constructed as a dynamic body.
         * 
         */
        inline bool isDynamic() const
            { return m_dynamic; }

        /**
         * @brief Check collision between this and provided body using specified algorithm.
         * 
         * @param t_body body witch which collision is supposed to be detected.
         * @param t_collisionLevel algorithm to use.
         * @return CollisionInfo object with information about the collision.
         */
        CollisionInfo checkCollision(std::shared_ptr<Body2D> t_body, CollisionLevel t_collisionLevel);
        /**
         * @brief Check inclusion of a point in this body.
         * (uses baricentric coordinates of the point in reaaltions to triangles
         * constructed from the center of the object to its edges)
         * 
         * @param t_vertex point which inclusion in the body is checked.
         * @return CollisionInfo object, only the "detected" field is filled in.
         */
        CollisionInfo checkInclusion(glm::vec2&& t_vertex);
        /**
         * @brief Check collision between this and provided body.
         * (Uses bounding circles calculated during creation of bodies)
         * 
         * @param t_body body with which collision is supposed to be detected.
         * @return CollisionInfo object, only the "detected" field is filled in.
         */
        CollisionInfo checkBC(std::shared_ptr<Body2D> t_body);
        /**
         * @brief Check collision between this and provided body.
         * (Uses axis aligned bounding boxes calculated during creation of bodies)
         * Works really well when bodies themselves are axis-aligned boxes,
         * since it allows for fast checking for collisions.
         * 
         * @param t_body body with which collision is supposed to be detected.
         * @return CollisionInfo object, fills in fields: detected, collisionPoints and penetration.
         */
        CollisionInfo checkAABB(std::shared_ptr<Body2D> t_body);
        /**
         * @brief Check if the body went out bounds represented by provided body.
         * (Assumes the bodies are axis-aligned boxes)
         * 
         * @param t_body body with which collision is supposed to be detected.
         * @return CollisionInfo object, fills in fields: detected, collisionPoints and penetration.
         */
        CollisionInfo checkOutOfBounds(std::shared_ptr<Body2D> t_body);
        /**
         * @brief Check collision between this and provided body.
         * (Checks for collisions edge by edge)
         * 
         * @param t_body body with which collision is supposed to be detected.
         * @return CollisionInfo object, only the "detected" field is filled in.
         */
        CollisionInfo checkEdges(std::shared_ptr<Body2D> t_body);
        /**
         * @brief Check collision between this body and provided edge.
         * 
         * @param t_a Point A of the edge
         * @param t_b Point B of the edge
         * @return CollisionInfo object, only the "detected" field is filled in.
         */
        CollisionInfo checkEdge(glm::vec2& t_a, glm::vec2& t_b);
        // CollisionInfo checkEdgeInfluence(glm::vec2& t_center, float radius);
        // CollisionInfo checkEdgeInfluence();

    private:
        void calculateBindingCircle();
        void calculateAABBB();
        void calculateEdgeInfluence();

        std::shared_ptr<glm::mat4> m_model;

        glm::vec2 m_lastTranslation = glm::vec2(0);
        glm::vec2 m_acceleration = glm::vec2(0);
        glm::vec2 m_velocity = glm::vec2(0);
        glm::vec2 m_groupAcceleration = glm::vec2(0);
        glm::vec2 m_groupVelocity = glm::vec2(0);

        bool m_axisAligned;
        bool m_dynamic;

        float m_upperBound;
        float m_lowerBound;
        float m_leftBound;
        float m_rightBound;

        glm::vec2 m_center;
        float m_radius;

        std::vector<glm::vec2> m_vertices;
        // std::vector<glm::mat2> m_edgeInfluenceBases;
        // std::vector<float> m_edgeInfluenceLengths;
    };
}