#ifndef BIT_CAST_HH
#define BIT_CAST_HH

#include <cstring>

template <typename To, typename From>
[[nodiscard]] auto constexpr bit_cast(const From &src) noexcept -> To
{
    To dst;
    std::memcpy(&dst, &src, sizeof(To));
    return dst;
}

#endif
