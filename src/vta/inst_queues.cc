#include "vta/inst_queues.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
LoadQueue::LoadQueue(const Params &params) : BaseInstructionQueue(params)
{
    DPRINTF(BaseVTAFlag, "create LoadQueue!\n");
}
} // namespace gem5

namespace gem5
{
ComputerQueue::ComputerQueue(const Params &params) :
    BaseInstructionQueue(params)
{
    DPRINTF(BaseVTAFlag, "create ComputerQueue!\n");
}
} // namespace gem5

namespace gem5
{
StoreQueue::StoreQueue(const Params &params) : BaseInstructionQueue(params)
{
    DPRINTF(BaseVTAFlag, "create StoreQueue!\n");
}
} // namespace gem5
