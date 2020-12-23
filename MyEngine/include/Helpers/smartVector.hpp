#pragma once

#include <vector>
#include <memory>
#include <algorithm>

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

        void removeLooseReferences()
        {
            while(true)
            {
                auto lastFind = std::find_if(begin(), end(), SmartVector::isLooseReference);

                if(lastFind == end()) return;
                else m_vector.erase(lastFind);
            }
        }

        static inline bool isLooseReference(std::shared_ptr<T> t_ptr)
            { return t_ptr.use_count() == 1; }

    private:
        std::vector<std::shared_ptr<T>> m_vector;
    };
}