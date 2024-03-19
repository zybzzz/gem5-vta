#ifndef BUFFER_HH
#define BUFFER_HH

#include <array>
#include <cstddef>

template <typename T, size_t M, size_t N, size_t READ_DELAY,
    size_t WRITE_DELAY>
struct Buffer : public std::array<std::array<T, N>, M>
{};

#endif
