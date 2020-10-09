#pragma once

#include <vector>
#include <functional>

class Zip
{
public:
    
    template <typename T, typename U>
    static auto Zip2(std::vector<T> const& a, std::vector<U>const& b)
    {
        using refT = const std::reference_wrapper<const T>;
        using refU = const std::reference_wrapper<const U>;

        std::vector<std::pair<refT, refU>> zipped;

        size_t size = std::min(a.size(), b.size());
        for(int i = 0; i< size; i++)
        {
            std::pair<refT, refU> tmp_pair(refT(a[i]), refU(b[i]));
            zipped.push_back(tmp_pair);
        }

        return zipped;
    }
};