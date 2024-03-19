#ifndef VTA_INT_HH
#define VTA_INT_HH

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace vta
{

template <size_t N>
using Signed = typename std::conditional_t<N <= 8, int8_t,
    typename std::conditional_t<N <= 16, int16_t,
        typename std::conditional_t<N <= 32, int32_t,
            typename std::conditional_t<N <= 64, int64_t, void>>>>;

template <size_t N>
using Unsigned = typename std::conditional_t<N <= 8, uint8_t,
    typename std::conditional_t<N <= 16, uint16_t,
        typename std::conditional_t<N <= 32, uint32_t,
            typename std::conditional_t<N <= 64, uint64_t, void>>>>;

} // namespace vta

#endif
