#include "vta/data_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
DataQueue::DataQueue(const Params &params) : SimObject(params)
{
    DPRINTF(BaseVTAFlag, "create DataQueue!\n");
}

int
DataQueue::pushBack()
{
    return 0;
}

int
DataQueue::popFront()
{
    return 0;
}

auto
DataQueue::tryPush() -> bool
{
    return false;
}

auto
DataQueue::tryPop() -> bool
{
    return false;
}

} // namespace gem5
