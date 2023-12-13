#ifndef STREAM_HH_
#define STREAM_HH_

#include <array>
#include <cstddef>

#include "vta/tick_struct.hh"

namespace gem5
{

template <typename T, size_t N>
class Stream
{
    std::array<T, N> buf{};
    size_t read_ptr{};
    size_t write_ptr{};
    size_t len{};

  public:
    auto
    pop() -> TickStruct<T>
    {
        const T value = buf[read_ptr];
        read_ptr = (read_ptr + 1) % N;
        --len;
        return {{}, value};
    }

    auto
    push(const T &value) -> TickStruct<>
    {
        buf[write_ptr] = value;
        write_ptr = (write_ptr + 1) % N;
        ++len;
        return {{}};
    }

    auto
    empty() const noexcept -> bool
    {
        return len;
    }

    auto
    full() const noexcept -> bool
    {
        return len == N;
    }

    auto
    size() const noexcept -> size_t
    {
        return N;
    }
};

} // namespace gem5

#endif
