#include "base/types.hh"

namespace gem5
{

template <typename T = void>
struct TickStruct
{
    Tick time;
    T value;
};

template <>
struct TickStruct<void>
{
    Tick time;
};

} // namespace gem5
