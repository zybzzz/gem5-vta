#ifndef STREAM_HH_
#define STREAM_HH_

#include <array>
#include <cstddef>

#include "vta/tick_struct.hh"

namespace vta
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
    peek() const noexcept -> TickStruct<T>
    {
        return {{}, buf[read_ptr]};
    }

    auto
    pop() noexcept -> TickStruct<T>
    {
        const auto ret{peek()};
        read_ptr = (read_ptr + 1) % N;
        --len;
        return ret;
    }

    auto
    push(const T &value) noexcept -> TickStruct<>
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

} // namespace vta

#endif
