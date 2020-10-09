#pragma once

#include "application.hpp"
#include "entryPoint.hpp"
#include "renderer.hpp"
#include "object2D.hpp"
#include "triangle2D.hpp"

#include "event/keyEvent.hpp"
#include "event/mouseKeyEvent.hpp"
#include "event/mouseMoveEvent.hpp"

// In order to start using the engine:
// - Make a class inheriting from  Appliaction
// - Override Application->onLoop
// - Define CreateApplication function, it has to return new obejct of created class
