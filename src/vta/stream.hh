#ifndef STREAM_HH_
#define STREAM_HH_

#include <array>
#include <cstddef>

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
    constexpr auto
    pop() noexcept -> T
    {
        const auto ret{buf[read_ptr]};
        read_ptr = (read_ptr + 1) % N;
        --len;
        return ret;
    }

    constexpr auto
    push(const T &value) noexcept -> void
    {
        buf[write_ptr] = value;
        write_ptr = (write_ptr + 1) % N;
        ++len;
    }

    constexpr auto
    empty() const noexcept -> bool
    {
        return len;
    }

    constexpr auto
    full() const noexcept -> bool
    {
        return len == N;
    }

    constexpr auto
    size() const noexcept -> size_t
    {
        return N;
    }
};

} // namespace vta

#endif
