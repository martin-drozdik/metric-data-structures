#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <functional>

class Identity
{
public:

    template<typename T>
    constexpr auto operator()(T&& v) const noexcept -> decltype(std::forward<T>(v))
    {
        return std::forward<T>(v);
    }
};

#endif // FUNCTORS_H
