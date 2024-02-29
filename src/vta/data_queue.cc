#include "vta/data_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
DataQueue::DataQueue(const Params &params) : SimObject(params)
{
    DPRINTF(BaseVTAFlag, "create DataQueue!\n");
}

} // namespace gem5
