#include "vta/data_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
DataQueue::DataQueue(BaseVTA *vta) : vta(vta)
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

} // namespace gem5
