#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

namespace Helpers
{
    template <typename T>
    class SmartVector
    {
    public:
        inline std::vector<std::shared_ptr<T>> vector()
            { return m_vector; }
        
        inline auto begin()
            { return std::begin(m_vector); }
        inline auto end()
            { return std::end(m_vector); }
        inline void pushBack(std::shared_ptr<T> t_ptr)
            { m_vector.push_back(t_ptr); }
        inline unsigned int& useCount()
            { return m_useCount; }

        void removeLooseReferences()
        {
            auto useCount = m_useCount;
            while(true)
            {
                auto lastFind = std::find_if(begin(), end(), 
                    [useCount](std::shared_ptr<T> t_ptr)
                        { return t_ptr.use_count() <= useCount; });

                if(lastFind == end()) return;
                else m_vector.erase(lastFind);
            }
        }

    private:
        unsigned int m_useCount = 1;
        std::vector<std::shared_ptr<T>> m_vector;
    };
}