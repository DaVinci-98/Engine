#pragma once

#include "application.hpp"
#include "entryPoint.hpp"

#include "Renderer/renderer.hpp"
#include "Renderer/triangle2D.hpp"
#include "Renderer/mesh2D.hpp"
#include "Renderer/material.hpp"
#include "Renderer/shader.hpp"

#include "Glfw/Events/keyEvent.hpp"
#include "Glfw/Events/mouseKeyEvent.hpp"
#include "Glfw/Events/mouseMoveEvent.hpp"

// In order to start using the engine:
// - Make a class inheriting from  Application
// - Override Application->onLoop
// - Define CreateApplication function, it has to return new obejct of created class
