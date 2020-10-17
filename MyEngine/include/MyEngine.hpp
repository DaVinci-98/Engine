#pragma once

#include "application.hpp"
#include "entryPoint.hpp"
#include "renderer.hpp"

#include "drawables/object2D.hpp"
#include "drawables/triangle2D.hpp"

#include "keyEvent.hpp"
#include "mouseKeyEvent.hpp"
#include "mouseMoveEvent.hpp"

// In order to start using the engine:
// - Make a class inheriting from  Appliaction
// - Override Application->onLoop
// - Define CreateApplication function, it has to return new obejct of created class
