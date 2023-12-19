#include "base/types.hh"

namespace vta
{

template <typename T = void>
struct TickStruct
{
    gem5::Tick time;
    T value;
};

template <>
struct TickStruct<void>
{
    gem5::Tick time;
};

} // namespace vta
