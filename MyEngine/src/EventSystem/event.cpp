#include "EventSystem/event.hpp"
#include "Helpers/logger.hpp"

namespace MyEngine::EventSystem
{
    void logUnhandled(std::string&& t_type)
    { 
        Helpers::Logger::log("MyEngine::EventSystem::Event") -> warn("[Unhandled]: {}", t_type); 
    }
}