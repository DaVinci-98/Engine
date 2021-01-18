#pragma once

#include <typeinfo>
#include <cxxabi.h>
#include <string>

namespace Helpers
{
    /**
     * @brief Get the name of provided type.
     * 
     * @tparam T type
     * 
     * @return std::string - type name
     */
    template <typename T>
    std::string getTypeName()
        { return abi::__cxa_demangle(typeid(T).name(), 0, 0, 0); }
}