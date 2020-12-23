#pragma once

#include <typeinfo>
#include <string>
#include <cxxabi.h>

namespace Helpers
{
    template <typename T>
    std::string getTypeName()
        { return abi::__cxa_demangle(typeid(T).name(), 0, 0, 0); }
}