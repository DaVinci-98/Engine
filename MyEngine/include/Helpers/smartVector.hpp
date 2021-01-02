#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

namespace Helpers
{
    /**
     * @brief std::vector extension for working with shared pointers 
     * 
     * @tparam T class pointed to by shared pointers
     */
    template <typename T>
    class SmartVector
    {
    public:
        /**
         * @brief Gets a reference to underlying vector
         * 
         * @return std::vector<std::shared_ptr<T>> 
         */
        inline std::vector<std::shared_ptr<T>>& vector()
            { return m_vector; }
        
        /**
         * @brief Gets an iterator to the first element of underlying vector
         * 
         * @return iterator 
         */
        inline auto begin()
            { return std::begin(m_vector); }
        /**
         * @brief Gets an iterator to the last element of underlying vector
         * 
         * @return iterator 
         */
        inline auto end()
            { return std::end(m_vector); }
        /**
         * @brief Push back element to underlying vector
         * 
         * @param t_ptr shared pointer to be pushed
         */
        inline void pushBack(std::shared_ptr<T> t_ptr)
            { m_vector.push_back(t_ptr); }
        /**
         * @brief Remove an element from the underlying vector.
         * 
         * @param t_ptr shared pointer to be removed
         */
        void remove(std::shared_ptr<T> t_ptr)
        {
            auto iterator = std::find(m_vector.begin(), m_vector.end(), t_ptr); 
            if(iterator != m_vector.end())
                m_vector.erase(iterator);
        }
        /**
         * @brief Push back unique element to underlying vector
         * 
         * @param t_ptr shared pointer to be pushed
         */
        void pushBackUnique(std::shared_ptr<T> t_ptr)
        {
            if(std::find(m_vector.begin(), m_vector.end(), t_ptr) == m_vector.end()) 
                m_vector.push_back(t_ptr); 
        }

        // inline unsigned int& useCount()
        //     { return m_useCount; }

        // void removeLooseReferences()
        // {
        //     auto useCount = m_useCount;
        //     while(true)
        //     {
        //         auto lastFind = std::find_if(begin(), end(), 
        //             [useCount](std::shared_ptr<T> t_ptr)
        //                 { return t_ptr.use_count() <= useCount; });

        //         if(lastFind == end()) return;
        //         else 
        //         {
        //             m_vector.erase(lastFind);
        //             std::cout<<"removing"<<std::endl;
        //         }
        //     }
        // }

    private:
        unsigned int m_useCount = 1;
        std::vector<std::shared_ptr<T>> m_vector;
    };
}